#pragma once
#include "Define.h"
#include <map>


class CZone;

///////////////////////////////////////////////////////////
// Session Class
// (Session�� �����ִ� Zone)
///////////////////////////////////////////////////////////
class CSession
{
public:
	enum E_DIR
	{
		LEFT,
		LEFTUP,
		UP,
		RIGHTUP,
		RIGHT,
		RIGHTDOWN,
		DOWN,
		LEFTDOWN,
		MAX_DIR
	};

	typedef std::map<E_DIR, CSession*> MAP_SESSION;

private:
	SECTOR_ID m_sectorId;        ///< ������ ���� ���̵�
	__int32   m_indexX;          ///< ������ ���� x �ε���
	__int32   m_indexY;          ///< ������ ���� y �ε���
	
	MAP_SESSION m_mapAdjSector;  ///< �ֺ��� ��ũ�Ǿ� �ִ� ����
	CZone* m_zone;               ///< ���� ���Ͱ� ���ӵǾ� �ִ� ��

public:
	bool MakeSector();

public:
	CSession(CZone* zone_);
	~CSession();
};



