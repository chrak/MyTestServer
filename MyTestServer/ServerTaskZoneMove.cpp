#include "ServerTaskZoneMove.h"
#include "ZoneManager.h"
#include "PC.h"
#include "Serverbase.h"
#include "sample.pb.h"

THREAD_REGION CServerTaskZoneMove::GetThreadRegion() const
{
	return CZoneManager::GetInstance().GetThreadRegion(m_zoneID);
}


bool CServerTaskZoneMove::Execute(ZONE_MAP const& zoneMap)
{
	CSession* session = CZoneManager::GetInstance().GetServer()->FindSession(m_sessionID);
	if (session == NULL)
	{
		// �α�
		return false;
	}

	/// ���� �ִ� ��Ŷ���� �ٽ� ó��
	session->SetTranslateMessageState(true);

	if (!CZoneManager::GetInstance().EnterZone(m_zoneID, session->GetPlayer()))
	{
		// �α�
		return false;
	}
	return true;
}


CServerTaskZoneMove::CServerTaskZoneMove(CSession const* session_, ZONE_ID zoneid_)
	: CServerTask(E_TYPE::SESSION_TASK_TYPE, session_)
{
	CSession* session = const_cast<CSession*>(session_);
	if (session == NULL)
	{
		// �α�
		return;
	}

	if (!CZoneManager::GetInstance().LeaveZone(session->GetZoneID(), session->GetPlayer()))
	{
		// �α�
		return;
	}

	m_zoneID = zoneid_;

	/// zone �̵� ���Ŀ� ���ļ� ���� �޽����� ���� zone���� ó������ �ʵ��� �� (�� : ���̵� + �����ŷ� ��Ŷ�� ���Ŀ��� ��)
	session->SetTranslateMessageState(false);

	/// ������ recv�� ���� ������ ���� ����
	session->SetThreadRegion(CZoneManager::GetInstance().GetThreadRegion(zoneid_));
}


CServerTaskZoneMove::~CServerTaskZoneMove()
{
}
