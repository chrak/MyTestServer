#pragma once
#include <winsock2.h>
#include <tbb/concurrent_queue.h>
#include <tbb/atomic.h>
#include "VirtualPoolObject.h"
#include "VirtualMemoryPool.h"
#include "PacketHeder.h"
#include "Define.h"
#include "PoolObjectStruct.h"
#include "Actor.h"
#include "CacheObject.h"
#include "ServerCore/SessionBase.h"
#include "ATLComTime.h"
#include <atomic>


typedef tbb::concurrent_queue<CPacketTransInfoBase*> PACKET_QUEUE;

struct SSendInfo
{
	PACKET_QUEUE   queue;
	std::atomic<BOOL> available;
};

struct SRecvInfo
{
	_WSABUF        wsa;
	_WSABUF        remain;           ///< recvó���� ���� ���ϰ� ���� ����
	CPacketTransInfoBase*  overlapped;
	PACKET_QUEUE   queue;
	std::atomic<BOOL> available;
};


class CPC;
class CServerBase;

///////////////////////////////////////////////////////////
// Session Class
///////////////////////////////////////////////////////////
class CSession : 
	public CSessionBase,
	public CVirtualPoolObject, 
	public CVirtualMemmoryPool<SPacketTransInfo>,
	public CCacheObject
{
public:
	enum E_STATE
	{
		STATE_INIT,
		STATE_REGISTED,
		STATE_DISCONNECTED,
		STATE_DESTROY,
	};

	struct _StInit
	{
		SOCKET socket;
		CServerBase* server;
		ULONG  addressNumber;
	};

private:
	SESSION_ID m_sessionID;          ///< sessionID
	SOCKET     m_socket;             ///< Socket
	DATE       m_createTimer;        ///< ������ ������� �ð�
	THREAD_REGION m_threadRegion;    ///< ������ �湮�ϴ� recv thread�� ���� ��ȣ
	CServerBase*  m_pServer;         ///< �����ϴ� ����
	ULONG         m_addressNumber;   ///< IP address�� DWORD��
	E_STATE       m_state;           ///< ������ ����
	bool          m_bIsConnected;    ///< ���� ����
	CActor*       m_pActor;          ///< ���ӵ� ����
	std::string   m_pass;            ///< ���� ĳ�ø� ���� �н�����

public:
	SSendInfo*      SendInfo;        ///< Send�� ����
	SRecvInfo*      RecvInfo;        ///< Recv�� ����
	
public:
	/// ���� ���̵� ������ �´�
	inline SESSION_ID GetSessionID() const { return m_sessionID; }

	/// ���� ���̵� �����Ѵ�.
	void SetSessionID(SESSION_ID sessionId_);

	/// ��Ĺ�� ������ �´�
	inline SOCKET     GetSocket() { return m_socket; }

	/// ������ ���� �ִ� recv thread�� ���� ���̵� ������ �´�
	inline THREAD_REGION GetThreadRegion() { return m_threadRegion; }

	/// IP�� DWORD ������ �ּҰ��� ������ �´�
	inline ULONG      GetAddressNumber() const { return m_addressNumber; }

	/// ������ ���¸� ������ �´�
	inline E_STATE    GetState() const { return m_state; }

	/// ���� ���θ� ������ �´�
	inline bool       IsConnected() const { return m_bIsConnected; }

	/// �н����带 ������ �´�
	inline std::string GetPassword() const { return m_pass; }

	/// �н����带 �����Ѵ�.
	void SetPassword(std::string const& pass_);

	/// ���� ���̵� ������ �´�
	USER_ID    GetUserID() const;

	/// ���Ͱ� ���� zoneID�� ������ �´�
	ZONE_ID    GetZoneID() const;

	/// ��Ŷ�� sendQueue�� �ִ´� (recv thread ������ ����ؾ� �Ѵ�)
	bool       Send(packetdef::PacketID id_, protobuf::Message* message_);

	/// ��Ŷ�� ��ٷ� �����Ѵ� (recv thread ������ ����ؾ� �Ѵ�)
	bool       SendImmediately(packetdef::PacketID id_, protobuf::Message* message_);

	/// ��Ŷ�� broadcast�ϱ� ���� sendQueue�� �ִ´� (recv thread ������ ����ؾ� �Ѵ�)
	bool	   BroadCast(SPacketTransBroadCastInfo* packetInfo_, bool bIsImmediatly_);

	/// sendQueue�� �׿��ִ� ��Ŷ�� flush�Ѵ�.
	void       FlushAllSend();

	/// ������ �湮�ϰ� �� thread�� ���� ���̵� �����Ѵ�.
	void       SetThreadRegion(int criteria_);

	/// ������ ���¸� �����Ѵ�
	void       SetState(E_STATE const state_);


	/// ������ �������� �����Ѵ�
	void       Reset(_StInit* initParam_);

	/// �ڽ��� �Էµ� ������ ���纻ȭ �Ѵ�
	void	   MakeClone(CSession const* session_);

	/// ������ ����
	void       CloseSocket();

	/// Recv �������� �޽��� �ؼ� ���� ����
	virtual void  SetTranslateMessageState(bool state_);

///////////////////////////////////////////////////////////////////////////////////

	/// ������ �ø��� ���̵� ������ �´�
	SERIAL_ID  GetActorID() const;

	/// ������ ���͸� �����Ѵ�
	void       SetActor(CActor const* actor_);

	/// PC�� ����� 
	CPC*       CreatePlayer(SERIAL_ID serialId_);

	/// PC�� ������ �´�
	CPC*       GetPlayer();


private:
	/// �޸� Ǯ���� ������ �����´�
	virtual bool Leave(void* initParam_) override;

	/// �޸� Ǯ�� ������ ����ִ´�
	virtual bool Enter() override;

	/// ĳ�� ���¸� �����Ѵ�
	virtual void SetCacheWaitState(bool state_) override;

	/// ĳ�ÿ��� ������ �� �ִ� �������� üũ�Ѵ�
	virtual bool CheckEnableReleaseCache() const override;

public:
	CSession();
	virtual ~CSession();
};