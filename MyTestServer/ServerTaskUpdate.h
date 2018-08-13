#pragma once
#include "ServerTask.h"
#include "Define.h"


///////////////////////////////////////////////////////////
// ������Ʈ ���� �½�ũ
// (����Ǵ� �������� ����)
///////////////////////////////////////////////////////////
class CServerTaskUpdate
	: public CServerTask
{
public:
	/// ����
	virtual bool Execute(ZONE_MAP const& zoneMap) override;

public:
	CServerTaskUpdate(size_t executeCnt_);
	virtual ~CServerTaskUpdate();
};
