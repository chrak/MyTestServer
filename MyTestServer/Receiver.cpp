#include "stdafx.h"
#include "Receiver.h"
#include "ServerBase.h"
#include "Define.h"
#include "PacketHeder.h"
#include "ThreadRegister.hpp"
#include "ScopePoolObj.h"
#include "MessageContext.h"
#include "AttachModule.h"
#include "ServerTask.h"
#include <google/protobuf/io/coded_stream.h>

using namespace google;
using namespace packetdef;


inline bool CReceiver::RunWorkerHandler(CSession* session_, packetdef::PacketID id_, protobuf::io::ArrayInputStream& io_)
{
	/// ��Ŷ���� �� �޽��� ����
	unsigned short region = 0xff00 & id_;
	CONTEXT_HANDLER_MAP::iterator it = m_workerHandlerMap.find(static_cast<packetdef::PacketRegion>(region));
	if (it == m_workerHandlerMap.end())
		return false;

	(*it).second->MessageProc(session_, id_, io_);
	return true;
}


inline void CReceiver::RunCloseHandler(CSession* session_, int reason_)
{
	/// Close �ڵ鷯�� ��ϵǾ� �ִ� ��� �Լ��� ����
	for (ATTACH_MODULE_LIST::iterator it = m_attachModuleList.begin(); it != m_attachModuleList.end(); ++it)
	{
		(*it)->SessionClose(session_, reason_);
	}

	m_pServer->SessionClose(session_);
}


inline void CReceiver::ExecuteTask(THREAD_REGION region_, CServerTask* task)
{
	if (m_pTaskExecutor == NULL)
	{
		// �α�
		return;
	}
	m_pTaskExecutor->ExecuteTask(region_, task);
}


inline bool CReceiver::CopyToRemainBuffer(CSession* session_, const void* buffer_, int size_)
{
	if (session_->RecvInfo->remain.len + size_ > PACKET_SIZE)
		return false;

	::memcpy_s(
		session_->RecvInfo->remain.buf + session_->RecvInfo->remain.len,
		size_,
		buffer_,
		size_
	);
	session_->RecvInfo->remain.len += size_;

	return true;
}


bool CReceiver::TranslatePacket(CSession* session_, protobuf::io::CodedInputStream& cs_, int totalsize_)
{
	const void* rawData = NULL;
	int translatedSize = 0;
	int remainSize = 0;
	int expectedSize = 0;
	PACKET_QUEUE& recvQueue = session_->RecvInfo->queue;
	packetdef::PacketHeader packetHeader;

	if (session_->RecvInfo->available)
	{
		/// recv ť�� �����Ͱ� ������ ��� �����Ų��
		/// ��ǥ�� �ϴ� �����忡�� ���۵� �� �ְ� �ϱ� ���� ����
		//Concurrency::critical_section::scoped_lock(&m_recvQueueLock);
		while (!recvQueue.empty())
		{
			CPacketTransInfoBase* obj;
			if (recvQueue.try_pop(obj))
			{
				protobuf::io::ArrayInputStream pis(obj->message, obj->header.dataSize);
				RunWorkerHandler(session_, obj->header.id, pis);
			}
			
			SPacketTransInfo* releaseObj = DYNAMIC_CAST(SPacketTransInfo*)(obj);
			session_->BackPoolObject(releaseObj);
		}
	}

	while (cs_.ReadRaw(&packetHeader, packetdef::HeaderSize))
	{
		expectedSize = packetHeader.dataSize;
		int packetSize = expectedSize + packetdef::HeaderSize;
		if (translatedSize + packetSize > totalsize_)
		{
			break;
		}

		cs_.GetDirectBufferPointer(&rawData, &remainSize);
		if (remainSize < expectedSize)
		{
			expectedSize = -packetdef::HeaderSize;
			break;
		}

		cs_.Skip(expectedSize);

		if (session_->RecvInfo->available)
		{
			/// �޽����� ó���� �� �ִ� ���¶�� �޽��� ó��
			protobuf::io::ArrayInputStream pis(rawData, expectedSize);
			RunWorkerHandler(session_, packetHeader.id, pis);
		}
		else
		{
			/// �޽����� ó���� �� ���� ���¶�� recvť�� �־�д�
			SPacketTransInfo* obj;
			SPacketTransInfo::_StInit param(packetHeader.id, expectedSize, session_);
			if (!session_->GetPoolObject(obj, &param))
			{
				// �α�
				return false;
			}
			protobuf::io::ArrayOutputStream output_array_stream(obj->message, expectedSize);
			protobuf::io::CodedOutputStream os(&output_array_stream);
			os.WriteRaw(rawData, expectedSize);

			recvQueue.push(obj);
		}
		translatedSize += packetSize;
	}

	/// �޽��� ó���� ��� �Ǿ����� �ش� �������� ó���� ���� �����̱� ������ recv ���¸� true�� �����Ѵ�.
	/// enableRecv�� false�� ���º��� ť�� �����Ͱ� �׿� �ְ� ��
	/// session_->SetTranslateMessageState(true);

	/// �޽��� ��ü�� ó������ �ʾҴٸ� ó�� �ȵ� ���۸� remain ���ۿ� ����
	if (translatedSize < totalsize_)
	{
		const void* prevData = static_cast<const char*>(rawData) + expectedSize;

		if (!CopyToRemainBuffer(session_, prevData, totalsize_ - translatedSize))
			return false;
	}

	return true;
}


bool CReceiver::Start(VEC_IOCP_HANDER& hWorkerHanders_)
{
	int nWorkThreadCount = static_cast<int>(hWorkerHanders_.size());
	if (nWorkThreadCount <= 0)
	{
		// �α�
		return false;
	}

	m_vecWorkerHandle = hWorkerHanders_;
	m_nWorkThreadCount = nWorkThreadCount;
	__super::RegisterThreadFunc(m_vecWorkerHandle, &CReceiver::RecvProc);

	return true;
}


bool CReceiver::AttachWorkerHandler(packetdef::PacketRegion region_, CMessageContext* message_)
{
	if (message_ == NULL)
	{
		// �α�
		return false;
	}

	std::pair<CONTEXT_HANDLER_MAP::iterator, bool> ret = m_workerHandlerMap.insert(std::make_pair(region_, message_));
	if (!ret.second)
	{
		// �α�
		return false;
	}
	return true;
}


bool CReceiver::AttachModule(CAttachModule* attach_)
{
	m_attachModuleList.push_back(attach_);
	return true;
}


bool CReceiver::AttachTaskExecutor(CServerTaskExecutor* attach_)
{
	m_pTaskExecutor = attach_;
	return true;
}


void CReceiver::Close()
{
	m_bIsRunning = false;
	m_attachModuleList.clear();
}


unsigned CALLBACK CReceiver::RecvProc(void* data_)
{
	CReceiver::_StWaitingEvent* waitingInfo = reinterpret_cast<CReceiver::_StWaitingEvent*>(data_);
	if (waitingInfo == NULL)
	{
		// �α�
		return 0;
	}

	CReceiver* caller_ptr = waitingInfo->pCaller;
	if (caller_ptr == NULL)
	{
		// �α�
		::CloseHandle(waitingInfo->hThread);
		::WSACloseEvent(waitingInfo->hWaitingEvent);
		return 0;
	}

	/// �����尡 ����� �����Ƿ� hWaitingEvent �ڵ鿡 ���� signal���� ����
	::WSASetEvent(waitingInfo->hWaitingEvent);

	char workBuf[SPacketTransInfo::MAX_PACKET_SIZE];

	while (caller_ptr->IsRunning())
	{
		CSession*   session;
		OVERLAPPED* overlapped;
		DWORD		dwBytesRecvd;

		if (::GetQueuedCompletionStatus(waitingInfo->hIOCompltePort, &dwBytesRecvd, (PULONG_PTR)&session, &overlapped, INFINITE))
		{
			if (overlapped != NULL)
			{
				CServerTask* task = reinterpret_cast<CServerTask*>(overlapped);
				caller_ptr->ExecuteTask(waitingInfo->threadRegion, task);
				if (task->CheckExepired())
				{	
					SAFE_POOL_DELETE(task, CServerTask);
				}
				continue;
			}

			char* recvBuffer = reinterpret_cast<char*>(session->RecvInfo->wsa.buf);

			if (session->RecvInfo->remain.len > 0)
			{
				int size = session->RecvInfo->remain.len + dwBytesRecvd;

				/// �����ִ� ������� ��Ŷ ����� ��ģ ���� ��� ������ ���� ������
				if (size < packetdef::HeaderSize)
				{
					if (!caller_ptr->CopyToRemainBuffer(session, recvBuffer, dwBytesRecvd))
					{
						/// PACKET_SIZE�� �Ѿ������ remain�� �׿� ������ ���з� ������
						// ó��(��������)
						caller_ptr->RunCloseHandler(session, 0);
					}
					continue;
				}

				/// �����ִ� ���۰� ������ �� ���۸� ��ģ��ŭ ���� ���۸� �Ҵ��ؼ� ó����
				protobuf::io::ArrayOutputStream os(workBuf, size);
				protobuf::io::CodedOutputStream cos(&os);
				cos.WriteRaw(session->RecvInfo->remain.buf, session->RecvInfo->remain.len);
				cos.WriteRaw(recvBuffer, dwBytesRecvd);

				session->RecvInfo->remain.len = 0;

				protobuf::io::ArrayInputStream is(workBuf, size);
				protobuf::io::CodedInputStream ics(&is);
				if (!caller_ptr->TranslatePacket(session, ics, size))
				{
					// ó��(��������)
					caller_ptr->RunCloseHandler(session, 0);
				}				
			}
			else
			{
				/// ��� ������ ���� �� ���� ��Ŷ�� �Դٸ�
				if (dwBytesRecvd < packetdef::HeaderSize)
				{
					if (!caller_ptr->CopyToRemainBuffer(session, recvBuffer, dwBytesRecvd))
					{
						/// PACKET_SIZE�� �Ѿ������ remain�� �׿� ������ ���з� ������
						// ó��(��������)
						caller_ptr->RunCloseHandler(session, 0);
					}
					continue;
				}

				/// �����ִ� ���۰� ������ �ش� ���۷� ó����
				protobuf::io::ArrayInputStream is(recvBuffer, dwBytesRecvd);
				protobuf::io::CodedInputStream ics(&is);
				if (!caller_ptr->TranslatePacket(session, ics, dwBytesRecvd))
				{
					// ó��(��������)
					caller_ptr->RunCloseHandler(session, 0);
				}
			}

			DWORD dwFlag = 0;
			do
			{
				if (::WSARecv(session->GetSocket(),
					&(session->RecvInfo->wsa),
					1,
					NULL,
					&dwFlag,
					session->RecvInfo->overlapped,
					NULL
				) == SOCKET_ERROR)
				{
					int err = WSAGetLastError();
					if (err != WSA_IO_PENDING)
					{
						if (err == WSAEWOULDBLOCK)
						{
							continue;
						}
						/// ó��..
					}
				}
				break;
			} while (true);

		}
	}
	::CloseHandle(waitingInfo->hThread);
	::WSACloseEvent(waitingInfo->hWaitingEvent);

	return 0;
}


CReceiver::CReceiver(CServerBase* server_)
	: m_pServer(server_)
{
}


CReceiver::~CReceiver()
{
	Close();
}