#pragma once
#include "Define.h"
#include <winsock2.h>
#include <atomic.h>


class CSession;

///////////////////////////////////////////////////////////////////////////
// ServerTask�� �⺻ Ŭ����
// *���� ���� ������(����� Ÿ��, thread ������ȣ�� �� ����)
// *�� ���� ������(����� Ÿ��, �����̵�)
// *���� ���� ������(�����Ÿ��, ����)
///////////////////////////////////////////////////////////////////////////
class CServerTask
{
public:
	enum E_TYPE
	{
		WORLD_TASK_TYPE,
		ZONE_TASK_TYPE,
		SESSION_TASK_TYPE,
	};

protected:
	tbb::atomic<size_t> m_expireCount;    ///< threadRegion ����ŭ �����Ͽ� 0�� �Ǹ� �����Ǵ� ī��Ʈ
	ZONE_ID m_zoneID;                     ///< zoneID
	SESSION_ID m_sessionID;               ///< sessionID
	E_TYPE m_type;                        ///< task�� Ÿ��

public:
	/// ����
	virtual bool Execute(ZONE_MAP const& zoneMap);

	/// ����� thread ���� ��ȣ�� ���´�
	virtual THREAD_REGION GetThreadRegion() const;
	
	/// ����� zoneID ���� ���´�
	inline ZONE_ID GetZoneID() const { return m_zoneID; }

	/// ����� sessionID ���� ������ �´�
	inline SESSION_ID GetSessionID() const { return m_sessionID; }

	/// �ش� �½�ũ�� Ÿ�԰��� ���´�
	inline E_TYPE GetTaskType() const { return m_type; }

	/// �����ؾ� �� thread ������ ��� �湮�Ͽ� ���ᰡ �Ǿ����� üũ�Ѵ�
	inline bool CheckExepired() { return m_expireCount.fetch_and_decrement() <= 1; }

public:
	explicit CServerTask(E_TYPE type_, size_t executeCnt_);
	explicit CServerTask(E_TYPE type_, ZONE_ID id_);
	explicit CServerTask(E_TYPE type_, CSession const* session_);
	virtual ~CServerTask();
};



///////////////////////////////////////////////////////////////////////////
// ServerTaskExecutor Ŭ���� (���� �����Լ�)
///////////////////////////////////////////////////////////////////////////
class CServerTaskExecutor
{
public:
	virtual void ExecuteTask(THREAD_REGION region_, CServerTask* task) = 0;
};