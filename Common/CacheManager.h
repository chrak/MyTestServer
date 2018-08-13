#pragma once

#include <list>
#include <process.h>
#include <winsock2.h>
#include <tbb/atomic.h>
#include <tbb/scalable_allocator.h>
//#include <tbb/concurrent_queue.h>
#include "concrt.h"
#include <thread>

class CCacheObject;

///////////////////////////////////////////////////////////
// ĳ�� �Ŵ���
///////////////////////////////////////////////////////////
template<typename T_OBJ>
class CCacheManager
{
public:
	//typedef tbb::concurrent_queue<CCacheObject*> CACHE_QUEUE;  //< ������ ����� ����...
	typedef std::list<CCacheObject*, tbb::scalable_allocator<T_OBJ>> CACHE_QUEUE;
	
private:
	volatile bool m_bRunning;						///< �������� ���� ����
	HANDLE m_hWaitNextObject;						///< ĳ�õǾ� �ִ� ť���� ���� ���ʸ� ��ٸ��� ���� �ڵ鷯
	tbb::atomic<CCacheObject*> m_pCurrentObject;    ///< ���������� ť���� �о�� ������
	Concurrency::critical_section m_cacheQueueLock; ///< ĳ�� ť ���� lock��ü
	std::thread m_joinHandle;


protected:
	CACHE_QUEUE m_queueObj;     ///< ĳ�� ť(ťó�� ���������� �˻��ؼ� ���� �κ��� �־ list)

private:
	/// ������ ����ִ� ����
	inline bool _IsRunning() const { return m_bRunning; }

	/// ���� ������Ʈ ����
	void SetCurrectObject(CCacheObject* obj_);

	/// �и������� ���� ���
	void WaitForSignal(DWORD milliseconds_);
	
	/// ��� ���� ����
	void SetSignal();

	/// ĳ��ť�� ������ ��� flush
	void FlushAllObejct();

	/// ĳ���� ������Ʈ �߰�
	void PushInList(CCacheObject const* obj_);

	/// ĳ���� ������Ʈ ������
	bool PopInList(CCacheObject*& __out obj_);

	/// ĳ��Ű�� �´� ĳ�� ������Ʈ ������
	CCacheObject* TakeInList(__int64 key);

	/// ���������� ĳ��ť���� �о�� ������
	CCacheObject* GetCurrentObject();

public:
	/// ĳ���� ������Ʈ �߰�
	/// (ĳ�� ������Ʈ, ĳ�� Ű, �������� ��ٸ��� �ð�)
	virtual void PushCacheObject(CCacheObject* obj_, __int64 key_, __int64 milliseconds_);
	
	/// ĳ�� Ű�� �´� ������Ʈ�� ã�ƿ´�
	virtual CCacheObject* FindCacheObject(__int64 key);
	
	/// ĳ�� ������Ʈ ���� ����
	virtual void ReleaseCache(CCacheObject* obj_);

	/// thread join ���� ����
	virtual void Join();

	/// ĳ�� ���� ó�� ���ν���
	unsigned CALLBACK CacheProc();

public:
	CCacheManager();
	virtual ~CCacheManager();
};
