#pragma once

#include "ServerTask.h"
#include "Define.h"


///////////////////////////////////////////////////////////
// ���� ���� ���� �½�ũ
// (����)
///////////////////////////////////////////////////////////
class CServerTaskDisconnected
	: public CServerTask
{
public:
	/// ����� thread�� ���� ���̵��� �о�´�
	virtual THREAD_REGION GetThreadRegion() const override;

	/// ����
	virtual bool Execute(ZONE_MAP const& zoneMap) override;

public:
	CServerTaskDisconnected(CSession const* session_);
	virtual ~CServerTaskDisconnected();
};
