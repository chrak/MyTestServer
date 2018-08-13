#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include "list"
#include "SessionManager.h"
#include "ThreadRegister.h"


class CAttachModule;
class CSender;

///////////////////////////////////////////////////////////////////////////
// Transfer Class
// (Send Class, ���� ����)
///////////////////////////////////////////////////////////////////////////
class CTransfer :
	public CIOCPThreadRegister<CTransfer>
{
public:
	typedef std::list<CAttachModule*> ATTACH_MODULE_LIST;

private:
	ATTACH_MODULE_LIST m_moduleList;     ///< ���� ��� ����Ʈ(������ ����, ����, �޽��� ������, �޽��� �ޱ�ÿ� ���۵Ǵ� ���)
	VEC_IOCP_HANDER m_vecWorkerHandle;   ///< transfer ���� IOCP �ڵ� ����
	CServerBase* m_pServer;              ///< ���ӵǴ� ����
	CSender*  m_pSender;                 ///< send class ������
	int m_nRecvThreadCount;              ///< ��ũ ������ ����(Recv Thread ����)

private:
	/// attach�� ��� �� recv�� ���õ� �͵��� ��� �����Ѵ�
	void RunRecvHandler(CSession* session_, DWORD bytes_);

	/// attach�� ��� �� send�� ���õ� �͵��� ��� �����Ѵ�
	void RunSendHandler(CSession* session_, DWORD bytes_);

	/// attach�� ��� �� sessionClose�� ���õ� �͵��� ��� �����Ѵ�
	void RunCloseHandler(CSession* session_, int reason_);

public:
	/// Transfer Thread ��� �� ����
	bool Start(HANDLE hCompletionPort_, int nTransperThreadCount_, VEC_IOCP_HANDER& hWorkerHanders_);

	/// ����, ��������, ������, �ޱ� ���� �Ͼ�� ���� ���� ����� ���
	bool AttachModule(CAttachModule* module_);

	/// ������ ����
	void Close();

	/// ������ ���� ���̵� ���� IOCP �ڵ��� ���´�
	HANDLE GetWorkThreadHandle(THREAD_REGION threadRegion_);

	/// send class�� ���´�
	CSender* GetSender() const;

	/// ���ӵǴ� ������ �����´�
	CServerBase* GetServer();

	/// ��Ŷ recv, send�� ��Ŷ transfer�� ó�� ���μ���
	static unsigned CALLBACK TransferProc(void* data_);

public:
	CTransfer(CSender* sender_, CServerBase* server_);
	virtual ~CTransfer();
};