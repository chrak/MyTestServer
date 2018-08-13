#include "stdafx.h"
#include "AdoOleDB.h"
#include "define.h"
#include "fmt\format.h"
#include "fmt\format.cc"
#include "ThreadRegister.hpp"
#ifdef __TBB_malloc_proxy
#include "tbb/tbbmalloc_proxy.h"
#else
#include "tcmalloc.h"
#endif


void CAdoOleDB::Init(_StInitInfo const& info_)
{
	m_dbInfo = info_;
	m_bInit = true;
}


bool CAdoOleDB::Start()
{
	if (!m_bInit)
	{
		// �α�
		return false;
	}

	int nThreadCount = m_dbInfo.nSessionThreadCount;
	if (nThreadCount <= 1)
	{
		// �α�
		return false;
	}

	m_vecThreadMessage.reserve(nThreadCount);
	m_vecConnInfo.resize(nThreadCount);

	for (int i = 0; i < nThreadCount; ++i)
	{
		SThreadMessage<CDBBaseTask>* message = new SThreadMessage<CDBBaseTask>;
		if (message != NULL)
		{
			m_vecThreadMessage.push_back(message);
		}
		else
		{
			// �α�
			return false;
		}
	}

	if (!__super::RegisterThreadFunc(m_vecThreadMessage, &CAdoOleDB::MessageProc))
	{
		// �α�
		return false;
	}

#if _USE_ADO_DB_MYSQL
	tstring strConn = fmt::format(L"{};SERVER={};DATABASE={};UID={};PWD={}", "DRIVER={MySQL ODBC 5.3 Unicode Driver}",
		m_dbInfo.ipAddress, m_dbInfo.dbName, m_dbInfo.userID, m_dbInfo.pass);
#else if _USE_ADO_DB_MSSQL
	tstring strConn = fmt::format(L"Provider=SQLOLEDB; Data Source={0},{1};Initial Catalog={2};User ID={3};Password={4};Network Library=dbmssocn",
		m_dbInfo.ipAddress, m_dbInfo.port, m_dbInfo.dbName, m_dbInfo.userID, m_dbInfo.pass);
#endif

	for (int i = 0; i < nThreadCount; ++i)
	{
		SConnectionInfo* connInfo = new SConnectionInfo;
		if (connInfo == NULL)
		{
			// �α�
			return false;
		}

		connInfo->connection_ptr.CreateInstance("ADODB.Connection");
		connInfo->record_ptr.CreateInstance("ADODB.Recordset");
		connInfo->record_ptr->CursorType = adOpenDynamic;
		connInfo->record_ptr->CursorLocation = adUseClient;
		connInfo->command_ptr = NULL;
		connInfo->connection_ptr->ConnectionString = strConn.c_str();

		try
		{
			connInfo->connection_ptr->Open(strConn.c_str(), "", "", adConnectUnspecified);
		}
		catch (...)
		{
			// �α�
			return false;
		}

		connInfo->command_ptr.CreateInstance(__uuidof(Command));
		connInfo->command_ptr->ActiveConnection = connInfo->connection_ptr;
		m_vecConnInfo[i] = connInfo;
	}

	return true;
}


void CAdoOleDB::ReleaseDB()
{
	VEC_CONNECTION_INFO::iterator it = m_vecConnInfo.begin();
	for (; it != m_vecConnInfo.end(); ++it)
	{
		SConnectionInfo* connInfo = *it;
		connInfo->connection_ptr->Close();
		connInfo->connection_ptr->Release();
	}
}


void CAdoOleDB::PushTask(CDBBaseTask* task_)
{
	/// �ʱ� ������ ������ select ���� db thread�� �Ҵ�
	int hashIndex = 0;
	if (task_->GetThreadRegion() != INIT_REGION_ID)
	{
		hashIndex = (task_->GetThreadRegion() % (m_registedThreadCount - 1)) + 1;
	} 

	/// �ش� �ε����� �´� queue�� connection ������ �Ҵ�
	task_->Init(m_vecConnInfo[hashIndex]);
	CTaskThreadRegister::PushTask(hashIndex, task_);
}


void CAdoOleDB::FlushAllMessage()
{
	VEC_THREAD_MESSAGE::iterator it = m_vecThreadMessage.begin();
	for (; it != m_vecThreadMessage.end(); ++it)
	{
		SThreadMessage<CDBBaseTask>* message = *it;
		::WSASetEvent(message->waitingEvent);
	}
}


unsigned CALLBACK CAdoOleDB::MessageProc(void* data_)
{
	CAdoOleDB::_StWaitingEvent* waitingInfo = reinterpret_cast<CAdoOleDB::_StWaitingEvent*>(data_);
	if (waitingInfo == NULL)
	{
		// �α�
		return 0;
	}

	CAdoOleDB* caller_ptr = waitingInfo->pCaller;
	if (caller_ptr == NULL)
	{
		// �α�
		::CloseHandle(waitingInfo->hThread);
		return 0;
	}

	/// �����尡 ����� �����Ƿ� hWaitingEvent �ڵ鿡 ���� signal���� ����
	::WSASetEvent(waitingInfo->hWaitingEvent);

	SThreadMessage<CDBBaseTask>* message = waitingInfo->message;
	if (message == NULL)
	{
		// �α�
		return 0;
	}

	while (caller_ptr->IsRunning())
	{
		while(!message->queue.empty())
		{
			CDBBaseTask* obj;
			if (message->queue.try_pop(obj))
			{
				// ó��
				if (obj->Execute())
				{

				}
				else
				{
					// ���� ���� ó��
				}
				SAFE_POOL_FREE(obj);
			}
			else
			{
				// �α�
			}
			
		}
		::WSAResetEvent(message->waitingEvent);
		::WaitForSingleObject(message->waitingEvent, INFINITE);
	}
	::CloseHandle(waitingInfo->hThread);
	::WSACloseEvent(waitingInfo->hWaitingEvent);

	return 0;
}


CAdoOleDB::CAdoOleDB()
	: m_bInit(false)

{
	::CoInitialize(0);
}


CAdoOleDB::~CAdoOleDB()
{
	FlushAllMessage();
	
	CTaskThreadRegister::VEC_THREAD_MESSAGE::iterator it = m_vecThreadMessage.begin();
	bool isEmpty;
	do
	{
		isEmpty = true;
		for (; it != m_vecThreadMessage.end(); ++it)
		{
			if (!(*it)->queue.empty())
			{
				isEmpty = false;
			}
		}
		::Sleep(100);
	} while (!isEmpty);

	ReleaseDB();
	::CoUninitialize();
}