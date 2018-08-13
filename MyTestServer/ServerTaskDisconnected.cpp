#include "ServerTaskDisconnected.h"
#include "PC.h"
#include "ZoneManager.h"
#include "Serverbase.h"

THREAD_REGION CServerTaskDisconnected::GetThreadRegion() const
{
	return CZoneManager::GetInstance().GetThreadRegion(m_zoneID);
}


bool CServerTaskDisconnected::Execute(ZONE_MAP const& zoneMap)
{
	CSession* session = CZoneManager::GetInstance().GetServer()->FindSession(m_sessionID);
	if (session == NULL)
	{
		// �α�
		return false;
	}

	CZoneManager::GetInstance().LeaveZone(m_zoneID, session->GetPlayer());
	session->CloseSocket();

	// ���� ���� session�� �ı��� �� �ִ� �ð� : sendQueue�� ������� �ð� + (dbQueue�� ������� �ð�)
	//                                           sendQueue�� �����Ͱ� ���� ������ send Thread���� session�� �����Ͽ� ���� �߻�
	CZoneManager::GetInstance().GetServer()->PushCacheObject(session, session->GetSessionID(), SESSION_CACHE_RELEASE_TIME);

	return true;
}


CServerTaskDisconnected::CServerTaskDisconnected(CSession const* session_)
	: CServerTask(E_TYPE::SESSION_TASK_TYPE, session_)
{
}


CServerTaskDisconnected::~CServerTaskDisconnected()
{
}
