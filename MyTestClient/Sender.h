#pragma once
#include <thread>
#include <winsock2.h>
#include "Common/PacketHeder.h"
#include "Common/PoolObjectStruct.h"
#include "Common/VirtualMemoryPool.h"
#include "tbb/concurrent_queue.h"
#include "define.h"

class CSession;

///////////////////////////////////////////////////////////
// CSender Ŭ����
///////////////////////////////////////////////////////////
class CSender : 
	public CVirtualMemmoryPool<SPacketTransInfo>
{
public:
	typedef tbb::concurrent_queue<SPacketTransInfo*> PACKET_QUEUE;

private:
	PACKET_QUEUE m_queue;            ///< Task Thread�� taskQueue
	HANDLE       m_waitingEvent;     ///< taskThread�� ���� �۾��� ��ٸ��� ���� �ڵ�

	CSession*     m_pSession;        ///< connector�� ���� ��ü ������
	volatile bool m_bRunning;        ///< send �������� ���� ����
	std::thread   m_hThread;         ///< ������ ��ü �ڵ�

public:
	/// send ������ ����
	bool Start(CSession* session_);

	/// ������ ��Ŷ�� ť�� ���� �ִ´�
	bool Push(packetdef::PacketID id_, protobuf::Message* message_);

	/// �ش� ��ü�� �����Ѵ�
	void Close();

	/// ������� ��ϵǴ� �Լ�
	unsigned CALLBACK SendProc();

public:
	CSender();
	~CSender();
};
