#pragma once
#include "ServerTask.h"
#include "Define.h"


///////////////////////////////////////////////////////////
// �� �̵� ���� �½�ũ
// (����)
///////////////////////////////////////////////////////////
class CServerTaskZoneMove
	: public CServerTask
{
public:
	/// ����� thread�� ���� ���̵��� �о�´�
	virtual THREAD_REGION GetThreadRegion() const override;

	/// ����
	virtual bool Execute(ZONE_MAP const& zoneMap) override;

public:
	CServerTaskZoneMove(CSession const* session_, ZONE_ID zoneid_);
	virtual ~CServerTaskZoneMove();
};
