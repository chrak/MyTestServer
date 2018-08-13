#pragma once
#include "ServerBase.h"
#include "LoginContext.h"
#include "AttachServerMessage.h"
#include "AdoOleDB.h"
#include <thread>

///////////////////////////////////////////////////////////
// �ӽ� ���� Ŭ����
///////////////////////////////////////////////////////////
class CWrappingServer :
	public CServerBase
{
private:
	CLoginContext m_loginContext;          ///< packetMessage ó�� context
	CAttachServerMessage m_sessionModule;  ///< �޽��� ��� ���� ���(������ ����, ����, �޽��� ������, �޽��� �ޱ�ÿ� ����)
	CAdoOleDB m_db;                        ///< ADB��� DBó�� ��ü
	std::thread m_timerThreadHandle;       ///< Ÿ�̸� ������ �ڵ�

public:
	/// ���� ����
	virtual bool Start() override;

	/// ���� ���� ���� �� �ʱ�ȭ
	virtual void Init(CServerBase::_StInitInfo const& serverInfo_) override;

	/// serverTask�� ���� ó��
	virtual void Process(CServerTask* task_) override;

	/// ������ ������ ���� ó��
	virtual void SessionClose(CSession* session_) override;

	/// thread join ����
	virtual void Join() override;

	/// ��� zone�� �����ϴ� serverTask�� �����
	template<typename T>
	void CreateWorldTask();

	/// Ư�� zoneID�� �����ϴ� serverTask�� �����
	template<typename T>
	void CreateZoneTask(ZONE_ID zoneId_);

	/// Ư�� session�� �����ϴ� serverTask�� �����
	template<typename T>
	void CreateSessionTask(CSession* session_);

public:
	CWrappingServer();
	virtual ~CWrappingServer();
};