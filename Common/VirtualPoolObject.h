#pragma once

#include "tbb/atomic.h"

///////////////////////////////////////////////////////////////////////////////
// ��ӿ� Ư�� Ÿ���� ������Ʈ ���̽�
///////////////////////////////////////////////////////////////////////////////
class CVirtualPoolObject
{
private:
	//tbb::atomic<bool> m_bUsed;   ///< �Ŵ����� ���� �����忡�� ���� �ȴٸ� ����� �κ�...
	bool m_bUsed;                  ///< ��� ����(������Ʈ Ǯ���� �����Դ°��� ����)

public:
	/// ������Ʈ�� Ǯ���� �������� ������̶� �̿��� �� �������� ����
	virtual bool SetUnAvailableState();

	/// ������Ʈ�� Ǯ�� �־ �̿��� �� �ִ� ���·� ����
	virtual bool SetAvailableState();

	/// ������Ʈ�� ��� ����
	virtual bool IsUsed() const;

	/// ������Ʈ Ǯ���� ���� ���� �� ����
	virtual bool Leave(void* initParam_);

	/// ������Ʈ Ǯ�� ������ �� ����
	virtual bool Enter();

public:
	CVirtualPoolObject();
	virtual ~CVirtualPoolObject();
};
