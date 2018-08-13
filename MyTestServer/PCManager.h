#pragma once

#include <tbb/concurrent_hash_map.h>
#include "Define.h"
#include "PC.h"
#include "Singleton.h"
#include "VirtualMemoryPool.h"

class CSession;

///////////////////////////////////////////////////////////
// PC ���� Ŭ����
///////////////////////////////////////////////////////////
class CPCManager :
	public CSingleton<CPCManager>,
	public CVirtualMemmoryPool<CPC>	
{
public:
	typedef tbb::concurrent_hash_map<SERIAL_ID, CPC*> MAP_PC;

private:
	MAP_PC m_mapPC;  ///< PC ��

public:
	// 1. ������ �����Ͱ� ���� ������ ������ ó���Ǹ� ������. 
	// 2. �̰��� �ܺο��� �����ͷ� ������ �ִ� ������ ����� ��(��: npc target�� �ش� �����ͷ� �δ� ���)
	// 3. 2���� ��쿡�� shared_ptr�� dangle pointer�� ���� �κ� ���� �� ������, ���ɻ� ����
	/// PC ��ü�� �����Ѵ�
	CPC* CreatePC(SERIAL_ID serialId_);

	/// �ش� serialID�� ���� PC��ü�� ã�´�
	CPC* FindPC(SERIAL_ID actorid_);  

	/// �ش� PC ����
	bool DestroyPC(CPC const* pc_);

	/// �ش� PC ����
	bool DestroyPC(SERIAL_ID actorid_);

public:
	CPCManager();
	~CPCManager();
};
