#pragma once
#include "VirtualPoolObject.h"
#include "PacketHeder.h"
#ifdef __TBB_malloc_proxy
#include "tbb/tbbmalloc_proxy.h"
#else
#include "tcmalloc.h"
#endif
#include <WinSock2.h>
#include <tbb/atomic.h>
#include "Define.h"
#include "VirtualMemoryPool.h"


///////////////////////////////////////////////////////////////////////////
// ��Ŷ �̼����� ���̽�
///////////////////////////////////////////////////////////////////////////
class CPacketTransInfoBase :
	public OVERLAPPED,
	public CVirtualPoolObject
{
public:
	enum TYPE_OP 
	{
		TYPE_NONE,
		TYPE_SEND,
		TYPE_RECV,
	};

	static const int MAX_PACKET_SIZE = PACKET_SIZE * 2; ///< ���۰� PACKET_SIZE �� ���¿��� �ƹ��� ���� ���͵� �ִ� PACKET_SIZE * 2

	packetdef::PacketHeader header;                    ///< ��Ŷ �ش�
	void* message;                                     ///< ��Ŷ �޽���

	virtual bool Leave(void* initParam_) { return false; }
	virtual bool Enter() { return false; }
	virtual bool BackPoolObject() { return false; }
	virtual TYPE_OP GetType() { return TYPE_RECV; }

	CPacketTransInfoBase()
	{
		hEvent = 0;
	}

	virtual ~CPacketTransInfoBase()
	{
	}
};


///////////////////////////////////////////////////////////////////////////
// ��Ŷ �̼����� Ŭ����
///////////////////////////////////////////////////////////////////////////
class SPacketTransInfo :
	public CPacketTransInfoBase
{
public:
	CVirtualMemmoryPool<SPacketTransInfo>* owner;  ///< �޸�Ǯ ������
	struct _StInit
	{
		packetdef::PacketHeader header;
		CVirtualMemmoryPool<SPacketTransInfo>* owner;
		_StInit(packetdef::PacketID id_, protobuf::uint16 size_, CVirtualMemmoryPool<SPacketTransInfo>* owner_)
		{
			header.id = id_;
			header.dataSize = size_;
			owner = owner_;
		}
	};

	/// �޸� Ǯ���� ������ ��
	virtual bool Leave(void* initParam_) override
	{
		if (initParam_ == NULL)
		{
			// �α�
			return false;
		}

		_StInit* init = reinterpret_cast<_StInit*>(initParam_);
		if (init->owner == NULL)
		{
			// �α�
			return false;
		}

		header.id = init->header.id;
		header.dataSize = init->header.dataSize;
		owner = init->owner;
		message = ALLOCATE_POOL_MALLOC(void, MAX_PACKET_SIZE);
		return true;
	}

	/// �޸� Ǯ�� �� ��
	virtual bool Enter() override
	{
		SAFE_POOL_FREE(message);
		return true;
	}

	/// owner�� ���� �޸� Ǯ�� ��ȯ
	virtual bool BackPoolObject() override
	{
		return owner->BackPoolObject(this);
	}

	/// �ش� ��Ŷ������ Ÿ��
	virtual TYPE_OP GetType() override
	{
		return TYPE_SEND;
	}

	SPacketTransInfo()
	{
		//message = ALLOCATE_POOL_MALLOC(void, MAX_PACKET_SIZE);
	}

	virtual ~SPacketTransInfo()
	{
		//SAFE_POOL_FREE(message);
	}
};


///////////////////////////////////////////////////////////////////////////
// ��Ŷ �̼����� Ŭ���� (��ε� �ɽ�Ʈ��)
///////////////////////////////////////////////////////////////////////////
class SPacketTransBroadCastInfo :
	public CPacketTransInfoBase
{
public:
	tbb::atomic<size_t> expireCount;                        ///< ���� ī��Ʈ(0�� �Ǹ� ����)
	CVirtualMemmoryPool<SPacketTransBroadCastInfo>* owner;  ///< �޸�Ǯ ������

	struct _StInit
	{
		packetdef::PacketHeader header;
		CVirtualMemmoryPool<SPacketTransBroadCastInfo>* owner;
		size_t expireCount;

		_StInit(packetdef::PacketID id_, protobuf::uint16 size_, size_t expireCount_, CVirtualMemmoryPool<SPacketTransBroadCastInfo>* owner_)
		{
			header.id = id_;
			header.dataSize = size_;
			expireCount = expireCount_;
			owner = owner_;
		}
	};

	/// �޸� Ǯ���� ������ ��
	virtual bool Leave(void* initParam_) override
	{
		if (initParam_ == NULL)
		{
			// �α�
			return false;
		}
			
		_StInit* init = reinterpret_cast<_StInit*>(initParam_);
		if (init->owner == NULL)
		{
			// �α�
			return false;
		}

		if (init->expireCount < 1)
		{
			// �α�
			return false;
		}

		header.id = init->header.id;
		header.dataSize = init->header.dataSize;
		expireCount = init->expireCount;
		owner = init->owner;
		message = ALLOCATE_POOL_MALLOC(void, MAX_PACKET_SIZE);
		return true;
	}

	/// �޸� Ǯ�� �� ��
	virtual bool Enter() override
	{
		if (expireCount.fetch_and_decrement() <= 1)
		{
			SAFE_POOL_FREE(message);
			return true;
		}
		
		return false;
	}

	/// owner�� ���� �޸� Ǯ�� ��ȯ
	virtual bool BackPoolObject() override
	{
		return owner->BackPoolObject(this);
	}

	/// �ش� ��Ŷ������ Ÿ��
	virtual TYPE_OP GetType() override
	{
		return TYPE_SEND;
	}


	SPacketTransBroadCastInfo()
	{
		//message = ALLOCATE_POOL_MALLOC(void, MAX_PACKET_SIZE);
	}

	virtual ~SPacketTransBroadCastInfo()
	{
		//SAFE_POOL_FREE(message);
	}

};





