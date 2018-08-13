#pragma once
#include "ServerTask.h"
#include "Define.h"
#include "PacketHeder.h"


///////////////////////////////////////////////////////////
// �޽��� ��ü ������ ���� �½�ũ
// (����Ǵ� �������� ����, ��Ŷ���̵�, �޽���)
///////////////////////////////////////////////////////////
class CServerTaskSendAll
	: public CServerTask
{
private:
	packetdef::PacketID m_packetId;  ///< ��Ŷ ���̵�
	protobuf::Message* m_pMessage;   ///< ��Ŷ �޽���

public:
	/// ����
	virtual bool Execute(ZONE_MAP const& zoneMap) override;

public:
	CServerTaskSendAll(size_t executeCnt_, packetdef::PacketID id_, protobuf::Message* message_);
	virtual ~CServerTaskSendAll();
};
