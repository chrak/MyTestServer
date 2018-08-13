#pragma once

#include "list"
#include "map"
#include "ThreadRegister.h"
#include "PacketHeder.h"
#include "Session.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

class CMessageContext;
class CAttachModule;
class CServerTask;
class CServerTaskExecutor;

///////////////////////////////////////////////////////////
// Recv Class
// (���� ����)
///////////////////////////////////////////////////////////
class CReceiver : 
	public CIOCPThreadRegister<CReceiver>
{
public:
	typedef std::map<packetdef::PacketRegion, CMessageContext*> CONTEXT_HANDLER_MAP;
	typedef std::list<CAttachModule*> ATTACH_MODULE_LIST;

private:
	CONTEXT_HANDLER_MAP m_workerHandlerMap;    ///< packet�޽��� ó���� ���� �ڵ鷯 ��
	ATTACH_MODULE_LIST m_attachModuleList;     ///< ���� ��� ����Ʈ(������ ����, ����, �޽��� ������, �޽��� �ޱ�ÿ� ���۵Ǵ� ���)
	VEC_IOCP_HANDER  m_vecWorkerHandle;        ///< recv ���� IOCP �ڵ� ����
	CServerBase* m_pServer;                    ///< ���� ����
	CServerTaskExecutor* m_pTaskExecutor;      ///< ServerTask ���� Ŭ���� ������
	int m_nWorkThreadCount;                    ///< ��ũ ������ ����(Recv Thread ����)

private:
	/// ���۸� remain���ۿ� �����Ѵ�
	bool CopyToRemainBuffer(CSession* session_, const void* buffer_, int size_);

	/// transfer Thread���� pqcs���� ���ƿ� ��Ŷ �޽����� �ؼ��Ѵ�
	bool TranslatePacket(CSession* session_, protobuf::io::CodedInputStream& cs_, int totalsize_);

	/// workerHandler�� ��ϵ� �Լ��� ���� �޽����� �����Ѵ�
	bool RunWorkerHandler(CSession* session_, packetdef::PacketID id_, protobuf::io::ArrayInputStream& io_);

	/// attach�� ��� �� sessionClose�� ���õ� �͵��� ��� �����Ѵ�
	void RunCloseHandler(CSession* session_, int reason_);

	/// serverTask�� thread ������ȣ�� ���߾� �����Ѵ�
	void ExecuteTask(THREAD_REGION region_, CServerTask* task);

public:
	/// Recv Thread ��� �� ����
	bool Start(VEC_IOCP_HANDER& hWorkerHanders_);

	/// packet �޽��� ó���� ���� workerHandler�� ������ �ϴ� messageContext ���
	bool AttachWorkerHandler(packetdef::PacketRegion region_, CMessageContext* message_);

	/// ����, ��������, ������, �ޱ� ���� �Ͼ�� ���� ���� ����� ���
	bool AttachModule(CAttachModule* attach_);

	/// ���� �׽�ũ�� ó���ϱ� ���� taskExecutor ���
	bool AttachTaskExecutor(CServerTaskExecutor* attach_);

	/// ������ ����
	void Close();

	/// ��Ŷ recv ó�� ���� ���ν��� (�̰��� thread�� ���� ������ work thread�� ����)
	static unsigned CALLBACK RecvProc(void* data_);

	/// ������, �Ҹ���
public:
	CReceiver(CServerBase* server_);
	virtual ~CReceiver();
};