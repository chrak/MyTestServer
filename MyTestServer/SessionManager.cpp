#include "stdafx.h"
#include "SessionManager.h"
#include "Session.h"
#include "ServerBase.h"
#include "VirtualMemoryPool.hpp"
#include "Singleton.hpp"
#include "Define.h"
#include "ServerTaskSendAll.h"
#include "CacheManager.hpp"


CSession* CSessionManager::CreateSession(SOCKET const& socket)
{
	/// listen Thread������ �����̳ʿ� �������� �ʰ� ��ü�� ����.
	CSession* newSession;
	CSession::_StInit param;
	param.socket = socket;
	param.server = m_pServer;

	if (!GetPoolObject(newSession, &param))
	{
		// �α�
		return NULL;
	}
	
	// ����� �α�
	return newSession;
}


SESSION_ID CSessionManager::RegistSession(CSession*& __out session_, SESSION_ID sessionid_, std::string const& id_, std::string const& pass_)
{
	SESSION_ID sessionId = INVALID_SESSION_ID;

	/// recv Thread���� �����̳� ���� 
	if (session_->GetState() != CSession::STATE_INIT)
	{
		// �α�
		return INVALID_SESSION_ID;
	}

	SESSION_MAP::accessor accessor;
	
	CERTIFICATION_MAP::iterator it_certiry = m_mapCertify.find(id_);
	if (it_certiry != m_mapCertify.end())
	{
		sessionId = (*it_certiry).second;
		if (m_mapSession.find(accessor, sessionId))
		{
			/// ĳ�� �� ������ ������ ������ �湮�ߴ����� �ִ� ���� �˻�
			CSession* prevSession = static_cast<CSession*>(FindCacheObject(sessionId));
			if (prevSession != NULL)
			{
				ExechangeSession(session_, prevSession);
			}
			else
			{
				/// ĳ�ð� �ƴ� ���Ǹ��� ������ ����
				prevSession = accessor->second;
				if (prevSession)
				{
					if (prevSession->IsConnected())
					{
						/// �̹� �������̶� ĳ�� ���� �����Ϳ� ���� ������ ���� �����
						ExechangeSession(session_, prevSession);
					}
					else
					{
						// �α�
						/// ���� �ʿ��� ��ϵǾ� �ִµ� ĳ�ÿ� ��ϵ��� �ʰ� ���ӵ� �̷�� ���� ���� ���
						BackPoolObject(session_);
						return INVALID_SESSION_ID;
					}
				}
			}
		}
		else
		{
			/// ��ϵ� ���� ���̵� ĳ�� Ÿ���� ���� ���� �ʿ� �������� ���� ���
			sessionId = GenerateSerialID();
			(*it_certiry).second = sessionId;
		}
	}
	else 
	{
		/// ������ ����� ���� ���� ����
		sessionId = GenerateSerialID();
		m_mapCertify.insert(std::pair<std::string, SESSION_ID>(id_, sessionId));
	}

	
	if (!m_mapSession.insert(accessor, sessionId))
	{
		/// ĳ�̵Ǿ� �ִ� �����Ͱ� ������ ������ ������ �´��� ��
		if ((*accessor).second->GetPassword() != pass_)
		{
			return INVALID_SESSION_ID;
		}
	}

	(*accessor).second = session_;
	
	session_->SetSessionID(sessionId);
	session_->SetPassword(pass_);
	session_->SetState(CSession::STATE_REGISTED);
	return sessionId;
}


void CSessionManager::ExechangeSession(CSession*& __out lhs_, CSession* rhs_)
{
	lhs_->MakeClone(rhs_);
	rhs_->CloseSocket();
	BackPoolObject(rhs_);
}


CSession* CSessionManager::FindSession(SESSION_ID sessionID_)
{
	SESSION_MAP::accessor accessor;
	if (m_mapSession.find(accessor, sessionID_))
	{
		// �α�
		return accessor->second;
	}
	return NULL;
}


void CSessionManager::DestroySession(SESSION_ID sessionID_)
{
	SESSION_MAP::accessor accessor;
	if (!m_mapSession.find(accessor, sessionID_))
	{
		// �α�
		return;
	}
	BackPoolObject(accessor->second);
	m_mapSession.erase(accessor);
}


void CSessionManager::SendAll(packetdef::PacketID id_, protobuf::Message* message_)
{
	CServerTaskSendAll* task = ALLOCATE_POOL_MALLOC(CServerTaskSendAll, sizeof(CServerTaskSendAll));
	new(task) CServerTaskSendAll(m_pServer->GetRecvIOPortHandler().size(), id_, message_);
	m_pServer->PushTask(task);
}


void CSessionManager::ReleaseCache(CCacheObject* obj_)
{
	CSession* session = static_cast<CSession*>(obj_);
	obj_->SetCacheWaitState(false);

	DestroySession(session->GetSessionID());
}


CSessionManager::CSessionManager()
{
}

CSessionManager::CSessionManager(int poolSize_, int poolInterval_, CServerBase* server_) :
	CVirtualMemmoryPool<CSession>(poolSize_, poolInterval_),
	m_pServer(server_),
	m_serialGen(100000)
{
}

CSessionManager::~CSessionManager()
{
}
