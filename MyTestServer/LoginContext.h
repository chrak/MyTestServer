#pragma once
#include "MessageContext.h"

#include "NPC.h"
#include <vector>

class CSession;
class CServerBase;

///////////////////////////////////////////////////////////
// �޽��� ó���� ���� ��ӹ��� �ӽ� Ŭ����
///////////////////////////////////////////////////////////
class CLoginContext : 
	public CMessageContext
{
private:
	CServerBase* m_pServer;   ///< ���ӵ� ����

public:
	/// �޽����� �����Ѵ�.
	virtual bool MessageProc(CSession* session_, packetdef::PacketID id_, protobuf::io::ArrayInputStream& io_) override;

public:
	CLoginContext(CServerBase * server_);
	virtual ~CLoginContext();
};