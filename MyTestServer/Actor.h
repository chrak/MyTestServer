#pragma once
#include "ActorNavi.h"
#include "Define.h"
#include "types.pb.h"

enum E_ACTOR
{
	NONE,
	PC,
	NPC,
	MONSTER
};

enum E_ACTOR_STATE
{
	ACTOR_STAND,
	ACTOR_WALK,
	ACTOR_RUN,
	ACTOR_KNOCKBACK,
	ACTOR_ATTACK,
	ACTOR_DEAD,
	ACTOR_RETURN,
};

class CZone;

///////////////////////////////////////////////////////////
// Actor Ŭ����
// (actor�� Ÿ��)
///////////////////////////////////////////////////////////
class CActor
{
protected:
	Vec3 m_pos;                      ///< actor�� ��ġ
	Vec3 m_spawnPos;                 ///< actor�� ���� ��ġ
	SERIAL_ID m_actorID;             ///< actor�� serialID
	SERIAL_ID m_targetActorID;       ///< actor�� target�� serialID
	int m_speed;                     ///< actor�� �ӵ�
	int m_hp;                        ///< actor�� hp
	bool m_bIsCache;                 ///< actor�� ĳ�� ���������� ����
	E_ACTOR m_actorType;             ///< actor Ÿ��
	E_ACTOR_STATE m_actionState;     ///< actor�� �׼� ����
	dtNavMesh* m_mesh;               ///< naviMesh ��ü ������
	UnitNavi  m_navMesh;             ///< ��ã�� ���� Ŭ����
	CZone*    m_zone;                ///< zone


public:
	/// naviMesh ����
	void SetNavmesh(dtNavMesh* mesh_);

	/// ���õ� naviMesh ��������
	UnitNavi* GetNaviMesh();

	/// actor ��ġ ����
	void SetPosition(Vec3 const& pos_);

	/// actor ��ġ ����(packet��...)
	void SetPosition(packets::Vector3 const& pos);

	/// actor ��ġ ����
	void SetPosition(float x_, float y_, float z_);

	/// actor�� ���� ��ġ ����
	void SetSpawnPosition(float x_, float y_, float z_);

	/// actor�� serialID ����
	void SetActorID(SERIAL_ID id_);

	/// actor�� �ӵ� ����
	void SetSpeed(int speed_);

	/// actor�� �����ִ� zone ����
	void SetZone(CZone* zone);

	/// actor�� hp����
	void SetHP(int hp_);

	/// actor�� target�� ���� serialID ����
	void SetTargetID(SERIAL_ID actorId_);

	/// actor�� actionState ����
	void SetActionState(E_ACTOR_STATE state_);

	/// actor�� ĳ�� ���� ���� ����
	void SetCacheState(bool state_);

	/// actor�� x��ǥ
	inline float GetPosX() const { return m_pos.x; }

	/// actor�� y��ǥ
	inline float GetPosY() const { return m_pos.y; }

	/// actor�� z��ǥ
	inline float GetPosZ() const { return m_pos.z; }

	/// actor�� ��ǥ���� ���� ���۷���
	inline Vec3& GetPosRef() { return m_pos; }

	/// actor�� ��ǥ
	inline Vec3 const& GetPosCRef() const { return m_pos; }

	/// actor�� packet vector ����
	packets::Vector3* GetPos();
	
	/// actor�� ���� x��ǥ
	inline float GetSpawnPosX() const { return m_spawnPos.x; }

	/// actor�� ���� y��ǥ
	inline float GetSpawnPosY() const { return m_spawnPos.y; }

	/// actor�� ���� z��ǥ
	inline float GetSpawnPosZ() const { return m_spawnPos.z; }

	/// actor�� ���� ��ǥ ���۷���
	inline Vec3& GetSpawnPosRef() { return m_spawnPos; }

	/// actor�� �ӵ� ��������
	int GetSpeed() const;

	/// actor�� zone ��������
	inline CZone* GetZone() const { return m_zone; }

	/// actor�� zoneID ��������
	ZONE_ID GetZoneID() const;

	/// actor�� hp ��������
	inline double GetHP() const { return m_hp; }

	/// actor�� Ÿ�� ��������
	inline E_ACTOR GetActorType() const { return m_actorType; }

	/// actor�� target�� serialID ��������
	inline SERIAL_ID GetTargetID() const { return m_targetActorID; }

	/// actor�� serialID ��������
	inline SERIAL_ID GetActorID() { return m_actorID; }

	/// actor�� �׼ǻ��� ��������
	inline E_ACTOR_STATE GetActionState() const { return m_actionState; }

	/// actor�� ĳ��ť�� ���°�
	inline bool IsCacheState() const { return m_bIsCache; }

	/// ������Ʈ
	virtual void Update();

	/// ���� AI���¿� ���� ���� ����
	virtual void SetAIPlayState(bool bIs_);

	/// ��ȿ�� actor�ΰ�
	virtual bool IsValid() const;


public:
	CActor(E_ACTOR type_);
	virtual ~CActor();
};