#pragma once
#include <thread>
#include <winsock2.h>

class CMessageContext;
class CSession;


///////////////////////////////////////////////////////////
// CReceiver Ŭ����
///////////////////////////////////////////////////////////
class CReceiver
{
private:
	CSession* m_pSession;         ///< connector�� ���� ��ü ������
	CMessageContext* m_pContext;  ///< recv �޽����� ó���� context
	volatile bool m_bRunning;	  ///< recv �������� ���� ����
	std::thread m_hThread;        ///< ������ ��ü �ڵ�


public:
	/// recv ������ ����
	bool Start(CSession* session_);

	/// recv �޽����� ó���� context ���
	void SetWorkHandler(CMessageContext* const context_);

	/// ���� �޽����� ó���ϴ� context�� ������ �´�
	CMessageContext const* GetWorkHandler();

	/// �ش� ��ü�� �����Ѵ�
	void Close();

	/// ������� ��ϵǴ� �Լ�
	unsigned CALLBACK RecvProc();

public:
	CReceiver();
	~CReceiver();
};
