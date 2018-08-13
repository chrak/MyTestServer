#pragma once
#include "Define.h"
#include "GeometryDef.h"
#include "PacketHeder.h"
#include "VirtualMemoryPool.h"
#include "PoolObjectStruct.h"
#include "tbb/scalable_allocator.h"
#include <map>

using namespace TypeVector;

class CPC;
class CNPC;
class CActor;
class dtNavMesh;
class CServerBase;

///////////////////////////////////////////////////////////
// Zone Class
// (zone�� �����ִ� ����)
///////////////////////////////////////////////////////////
class CZone : 
	public CVirtualMemmoryPool<SPacketTransBroadCastInfo>
{
public:
	typedef std::map<SERIAL_ID, CPC*, std::less<SERIAL_ID>, tbb::tbb_allocator<std::pair<const SERIAL_ID, CPC>>> MAP_PC;
	typedef std::map<SERIAL_ID, CNPC*, std::less<SERIAL_ID>, tbb::scalable_allocator<std::pair<const SERIAL_ID, CNPC>>> MAP_NPC;

	//typedef std::map<SERIAL_ID, CPC*> MAP_PC;
	//typedef std::map<SERIAL_ID, CNPC*> MAP_NPC;

private:
	ZONE_ID m_zoneId;         ///< zoneID
	MAP_PC  m_mapPC;          ///< ��ϵ� PC ��
	MAP_NPC m_mapNPC;         ///< ��ϵ� NPC ��
	dtNavMesh* m_navMesh;     ///< �ش� zone�� navmesh
	CServerBase* m_pServer;   ///< zone�� �����ִ� ����


public:
	__int32  MaxSectorX;      ///< ������ �ִ� x ũ��
	__int32  MaxSectorY;      ///< ������ �ִ� y ũ��


public:
	/// zoneID�� ������ �´�
	inline ZONE_ID GetZoneID() const { return m_zoneId; }

	/// zone�� ���� �ִ� Ư�� �Ÿ� �ȿ� �ִ� PC�� �ϳ��� ������ �´�
	CPC* FindInDistPC(Vec3 const& pos_, float dist_);

	/// zone�� ���� �ִ� Ư�� �Ÿ� �ȿ� �ִ� NPC�� �ϳ��� ������ �´�
	CNPC* FindInDistNPC(Vec3 const& pos_, float dist_);

	/// zone�� ���� �ִ� Ư�� serialID�� PC�� ������ �´�
	CPC* FindPC(SERIAL_ID id_);

	/// zone�� ���� �ִ� Ư�� serialID�� NPC�� ������ �´�
	CNPC* FindNPC(SERIAL_ID id_);

	/// �ش� ���� �ִ� PC�鿡�� ��Ŷ �޽����� ������.
	void SendZone(packetdef::PacketID id_, protobuf::Message* message_, bool bIsImmediatly_ = true);

	/// zone�� actor ����
	virtual bool Enter(CActor* actor_);

	/// zone���� actor ����
	virtual bool Leave(CActor* actor_);

	/// ������Ʈ
	virtual void Upate();

private:	
	/// ������ �ε�
	bool Load(std::string const& fileName_);

	/// ���� ����
	bool MakeSector();

public:
	CZone(CServerBase* server_, std::string const fileName_);
	virtual ~CZone();
};
