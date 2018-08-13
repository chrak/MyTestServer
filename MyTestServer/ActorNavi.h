#pragma once
#include "stdafx.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "GeometryDef.h"
#include <string>


using namespace TypeVector;

class CActor;

///////////////////////////////////////////////////////////
// ��ã�� ���� Ŭ����
///////////////////////////////////////////////////////////
class UnitNavi
{
public:
	static const int MAX_POLYS = 256;
	static const int MAX_SMOOTH = 2048;

	struct S_PathNodeData {
		Vec3 From;
		Vec3 To;
		float Yaw;
		float Distance;
		void SetDist() {
			Distance = From.Distance(To);
			//Distance = From.Distance2(To);
		}
		float GetDist() {
			return Distance;
		}

		Vec3 Lerp(float dist_) {
			return Vec3::Lerp(From, To, dist_ / Distance);
		}
	} m_PathNode[MAX_POLYS];


private:
	const dtNavMesh* m_navMesh;      ///< �׺�Ž�
	dtNavMeshQuery* m_navQuery;
	dtQueryFilter m_filter;
	S_PathNodeData m_currentPath;     ///< ���� ���õ� ��ã�� ���� 

	int m_straightPathOptions;

	dtPolyRef m_startRef;
	dtPolyRef m_endRef;
	dtPolyRef m_polys[MAX_POLYS];
	//dtPolyRef m_parent[MAX_POLYS];
	int m_npolys;

	unsigned char m_straightPathFlags[MAX_POLYS];
	dtPolyRef m_straightPathPolys[MAX_POLYS];
	int m_nstraightPath;
	float m_polyPickExt[3];

	float m_spos[3];
	float m_epos[3];

	double m_MoveStartTime;           ///< ��ã�� ���� �ð�
	float m_TotalDistance;            ///< ���� ���õ� ��ã�� ����� �� ����
	CActor* m_Owner;                  ///< ��ã�⸦ ������ actor


private:
	/// ��ã�� ó��
	bool Pathfinding(Vec3 startPos_, Vec3 endPos_);

public:
	/// ��ã�⸦ ������ actor ����
	void InitOwner(CActor* actor_);
	
	/// �ʱ�ȭ �Լ�
	void InitMesh(const dtNavMesh* navMesh_);
	
	/// ��ã�� ���� ����
	void Reset();

	/// ������Ʈ
	void Update();

	/// ��ã�� ���� ����
	bool CommandMove(S_PathNodeData const& pos_);

	/// Ư�� ��ǥ�� �� �� �ִ��� üũ(���� �� �� �ִ� �� ��ȯ) 
	bool getNearPos(Vec3 const& start_, Vec3& pos_);

	/// ������Ʈ ���� ���� ��ǥ�� �����´�(�ӵ�, ������ǥ ��ȯ, ���� ��ȯ, ������ ���� ���� ��ȯ)
	bool GetCurPos(float speedPerSec_, Vec3& curPos_, float& direction_, bool& goal_);

	/// �ش� filepath�� �޽� ������ �ε� �� �޽����� ��ȯ
	static dtNavMesh* LoadMeshFromFile(const std::string& filename);

public:
	UnitNavi();
	virtual ~UnitNavi();
};
