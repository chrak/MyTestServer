#include "stdafx.h"
#include "ServerBase.h"
#include "Define.h"
#include "PacketHeder.h"
#include "ThreadRegister.hpp"
#include "ScopePoolObj.h"

#include <chrono>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>


using namespace google;
using namespace packetdef;


bool CServerBase::Start()
{	
	if (!m_bInit)
	{
		// �α�
		return false;
	}

	/// IO �ڵ� ����
	m_hListenIOPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	m_vecRecvIOPort.resize(m_serverInfo.nRecvThreadCount);
	m_vecSendIOPort.resize(m_serverInfo.nSendThreadCount);

	for (int i = 0; i < m_serverInfo.nRecvThreadCount; ++i)
	{
		m_vecRecvIOPort[i] = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	}

	for (int i = 0; i < m_serverInfo.nSendThreadCount; ++i)
	{
		m_vecSendIOPort[i] = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	}

	/// receive
	if (!m_receiver.Start(m_vecRecvIOPort))
	{
		// �α�
		return false;
	}

	/// sender
	if (!m_sender.Start(m_vecSendIOPort))
	{
		// �α�
		return false;
	}

	/// listen
	m_hServSock = m_listen.Start(m_hListenIOPort, m_serverInfo.nListenPortNumber);
	if (m_hServSock == NULL) 
	{
		// �α�
		return false;
	}

	/// transfer
	if (!m_transfer.Start(m_hListenIOPort, m_serverInfo.nTransferThreadCount, m_vecRecvIOPort))
	{
		// �α�
		return false;
	}

	/// recv io �����忡 ���� �޽��� ť �ʱ�ȭ
	SThreadMessage<CServerTask>* message = new SThreadMessage<CServerTask>;
	if (message != NULL)
	{
		m_vecThreadMessage.push_back(message);
	}
	else
	{
		// �α�
		return false;
	}
	

	if (!__super::RegisterThreadFunc(m_vecThreadMessage, &CServerBase::MessageProc))
	{
		// �α�
		return false;
	}

	m_bIsRunning = true;

	return true;
}


void CServerBase::PushTask(CServerTask* task_)
{
	CTaskThreadRegister::PushTask(0, task_);
}


void CServerBase::FlushAllMessage()
{
	for (auto it : m_vecThreadMessage)
	{
		SThreadMessage<CServerTask>* message = it;
		::WSASetEvent(message->waitingEvent);
	}
}



void CServerBase::Init(_StInitInfo const& serverInfo_)
{
	m_serverInfo = serverInfo_;
	m_bInit = true;
}


void CServerBase::Close()
{
	m_bIsRunning = false;
	m_bInit = false;
	m_vecRecvIOPort.clear();
	m_vecSendIOPort.clear();
}


void CServerBase::SessionClose(CSession* session_)
{
	// Don't call this
}


void CServerBase::Process(CServerTask* task_)
{
	// Don't call this
}


unsigned CALLBACK CServerBase::MessageProc(void* data_)
{
	CServerBase::_StWaitingEvent* waitingInfo = reinterpret_cast<CServerBase::_StWaitingEvent*>(data_);
	if (waitingInfo == NULL)
	{
		// �α�
		return 0;
	}

	CServerBase* caller_ptr = waitingInfo->pCaller;
	if (caller_ptr == NULL)
	{
		// �α�
		::CloseHandle(waitingInfo->hThread);
		return 0;
	}

	/// �����尡 ����� �����Ƿ� hWaitingEvent �ڵ鿡 ���� signal���� ����
	::WSASetEvent(waitingInfo->hWaitingEvent);

	SThreadMessage<CServerTask>* message = waitingInfo->message;
	if (message == NULL)
	{
		// �α�
		return 0;
	}

	while (caller_ptr->IsRunning())
	{
		while (!message->queue.empty())
		{
			CServerTask* obj;
			if (message->queue.try_pop(obj))
			{
				caller_ptr->Process(obj);
			}
		}
		::WSAResetEvent(message->waitingEvent);
		::WaitForSingleObject(message->waitingEvent, INFINITE);
	}
	::CloseHandle(waitingInfo->hThread);
	::WSACloseEvent(waitingInfo->hWaitingEvent);

	return 0;
}


CServerBase::CServerBase() :
	CSessionManager(POOL_SIZE, POOL_INTERVAL, this),
	m_listen(this),
	m_receiver(this),
	m_transfer(&m_sender, this),
	m_bInit(false)
{
}

CServerBase::~CServerBase()
{
	Close();
}