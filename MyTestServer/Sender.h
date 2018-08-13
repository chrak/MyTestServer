#pragma once

#include <google/protobuf/message.h>
#include "Session.h"
#include "ThreadRegister.h"
#include "PacketHeder.h"
#include "Define.h"

using namespace google;
using namespace packetdef;

///////////////////////////////////////////////////////////
// Send Class
///////////////////////////////////////////////////////////
class CSender : 
	public CIOCPThreadRegister<CSender>
{
private:
	VEC_IOCP_HANDER m_vecWorkerHandle;  ///< send ���� IOCP �ڵ� ����
	int m_nWorkThreadCount;             ///< ��ũ ������ ����(Send Thread ����)
	
public:
	/// send�� �ʿ��� session�� push �Ѵ�(�ݵ�� recv �����忡�� ȣ���ؾ� �Ѵ�)
	bool Push(CSession* session);

	/// sessionID�� ���� send�� Workthread �ڵ鷯�� ������ �´�
	HANDLE GetWorkThreadHandle(SESSION_ID sessionId_);

	/// Send Thread ��� �� ����
	bool Start(VEC_IOCP_HANDER& hWorkerHanders_);

	/// session�� sendQueue �� ù��°�� send�Ѵ�
	bool SendPacketUnit(CSession *session_);

	/// session�� sendQueue�� MAX_PACKETSIZE ũ�� ��ŭ ��Ƽ� send�Ѵ� 
	/// (������ ��Ŷ�� �����ϴ� �߿� �ִ� MAX_PACKETSIZE * 2�� �� �� �ִ�)
	bool SendPacketUnits(CSession *session_);

	/// ������ ����
	void Close();
	
	/// ��Ŷ send ó�� ���� ���ν���
	static unsigned CALLBACK SendProc(void* data_);

public:
	CSender();
	virtual ~CSender();
};