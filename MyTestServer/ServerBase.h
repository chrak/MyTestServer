#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>

#include "vector"
#include "Listener.h"
#include "Transfer.h"
#include "Sender.h"
#include "Receiver.h"
#include "SessionManager.h"
#include "ThreadRegister.h"
#include "PacketHeder.h"
#include "ServerTask.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

///////////////////////////////////////////////////////////////////////////
// ���� �⺻ class
///////////////////////////////////////////////////////////////////////////
class CServerBase :
	public CSessionManager,
	public CTaskThreadRegister<CServerBase, CServerTask>
{
public:
	typedef enum SERVER_TYPE_
	{
		LOGIN_SERVER = 0,
		GAME_SERVER,
	} SERVER_TYPE;

	struct _StInitInfo {
		int nRecvThreadCount;
		int nSendThreadCount;
		int nTransferThreadCount;
		int nListenPortNumber;
		SERVER_TYPE serverType;
	};

private:
	SOCKADDR_IN m_servAddr;										///< ���� �ּ� ����ü
	SOCKET m_hServSock;											///< listen ����
	HANDLE m_hListenIOPort;										///< listen ����IOCP �ڵ�
	VEC_IOCP_HANDER m_vecRecvIOPort;							///< recv ���� IOCP �ڵ� ����
	VEC_IOCP_HANDER m_vecSendIOPort;							///< send ���� IOCP �ڵ� ����

protected:
	_StInitInfo m_serverInfo;           ///< ���� ���� ����ü
	CListener m_listen;                 ///< listen Ŭ����
	CTransfer m_transfer;               ///< transfer Ŭ����
	CSender   m_sender;                 ///< send Ŭ����
	CReceiver m_receiver;               ///< recv Ŭ����
	bool      m_bInit;                  ///< �ʱ�ȭ �Ϸ� ����
	bool      m_bIsRunning;             ///< ������ ������ ����

public:
	/// send Ŭ������ ���۷����� ������ �´�
	inline CSender& GetSenderRef() { return m_sender; }

	/// recv �������� IOCP �ڵ� ���͸� ������ �´�
	inline VEC_IOCP_HANDER const& GetRecvIOPortHandler() { return m_vecRecvIOPort; }

	/// send �������� IOCP �ڵ� ���͸� ������ �´�
	inline VEC_IOCP_HANDER const& GetSendIOPortHandler() { return m_vecSendIOPort; }

	/// serverTask Thread ��� �� ����
	virtual bool Start();

	/// �ʱ�ȭ
	virtual void Init(_StInitInfo const& serverInfo_);

	/// ������ ����
	void Close();

	/// ������ ������ ���� ó��
	virtual void SessionClose(CSession* session_);

	/// serverTask ó��
	virtual void Process(CServerTask* task_);

	/// serverTask�� ��� flush��
	virtual void FlushAllMessage() override;

	/// serverTask �߰�
	void PushTask(CServerTask* task_);

	/// serverTask ó�� ���μ���
	static unsigned CALLBACK MessageProc(void* data_);
	
public:
	CServerBase();
	virtual ~CServerBase();
};