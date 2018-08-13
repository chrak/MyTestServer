#pragma once
#include "Define.h"
#include "Singleton.h"
#include "ServerTask.h"
#include <map>
#include <vector>

class CServerTask;
class CServerBase;
class CActor;
class CZone;

///////////////////////////////////////////////////////////
// Zone ���� Ŭ����
///////////////////////////////////////////////////////////
class CZoneManager
	: public CSingleton<CZoneManager>,
	public CServerTaskExecutor
{
public:
	typedef std::vector<ZONE_MAP> THREAD_REGION_VEC;
	struct _stInit
	{
		int regionCount;           ///< thread�� ���� ���� ���̵�
		CServerBase* server;       ///< zone�� ���� �ִ� ����
	};

private:
	int m_regionCount;				     ///< thread�� ���� ���� ����
	THREAD_REGION_VEC m_vecZoneRegion;   ///< thread�� ���� ������ ���� �ִ� zone�� ���� ����
	CServerBase* m_pServer;              ///< zone�� ���� �ִ� ����

public:
	/// �ʱ�ȭ
	void Init(_stInit const& init_);

	/// �� ���� �ε�
	bool LoadZone();

	/// �ش� zone�� thread ���� ���� ���̵� ���Ѵ�
	inline THREAD_REGION GetThreadRegion(ZONE_ID id_) const { return id_ % m_regionCount; }

	/// zone�� ���� �ִ� ������ ������ �´�
	inline CServerBase* GetServer() { return m_pServer; }

	/// zoneID�� ���� zone�� ������ �´�
	CZone* FindZone(ZONE_ID id_);

	/// zoneID�� �´� zone�� �����Ѵ�
	bool DeleteZone(ZONE_ID id_);

	/// �ش� zoneID�� zone�� actor�� ���Խ�Ų��
	bool EnterZone(ZONE_ID id_, CActor* actor_);

	/// �ش� zoneID�� zone���� actor�� �����Ų��
	bool LeaveZone(ZONE_ID id_, CActor* actor_);

	/// ���� task�� �����Ѵ�
	virtual void ExecuteTask(THREAD_REGION region_, CServerTask* task) override;

private:
	/// �� ������ �����Ѵ�
	bool AddZone(CZone* zone_);

public:
	CZoneManager();
	~CZoneManager();
};