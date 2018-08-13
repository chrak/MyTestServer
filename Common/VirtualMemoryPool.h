#pragma once

#include <tbb/concurrent_queue.h>

class CVirtualPoolObject;

///////////////////////////////////////////////////////////////////////////////
// ��ӿ� Ư�� Ÿ���� ������Ʈ Ǯ
// <������Ʈ Ÿ��>
// (�ּ� ���� ����, �þ�� ����)
///////////////////////////////////////////////////////////////////////////////
template<typename T>
class CVirtualMemmoryPool 
{
public:
	typedef tbb::concurrent_queue<CVirtualPoolObject*> OBJECT_POOL_QUEUE;

private:
	OBJECT_POOL_QUEUE m_pool;       ///< ������Ʈ Ǯ ť
	int m_intervalSize;             ///< ������Ʈ ť�� ���� á�� ��� ���� �����Ǵ� ������
	int m_totalPoolSize;            ///< ������ Ǯ �� ������

public:
	/// ������Ʈ Ǯ���� ��ü�� ȹ��
	bool GetPoolObject(__out T*& out_, void* initParam_ = NULL);

	/// ������Ʈ Ǯ���� ��ü�� ��ȯ
	bool BackPoolObject(__in T* obj_);

	/// ť�� ���� á�� ��� ���� �����Ǵ� ������ ����
	bool SetIntervalSize(const int length_);

	/// ����ִ� ������Ʈ���� �ش� ũ�⸸ŭ ������Ʈ Ǯ�� �Ҵ�
	int AllocateEmptyObject(const int length_);

	/// Ǯ�� �ִ� �޸� ����
	void ReleasePool();

public:
	CVirtualMemmoryPool();
	CVirtualMemmoryPool(const int length_, const int intervalSize_);
	virtual ~CVirtualMemmoryPool();
};
