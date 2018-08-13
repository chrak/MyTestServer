#pragma once

#include <tbb/atomic.h>

///////////////////////////////////////////////////////////////////////////////
// ������ ����ִ� ���� �ش� ���μ����� ����ũ�� �ø��� ���� Ŭ����
// (���� �ø��� ���̵�)
///////////////////////////////////////////////////////////////////////////////
class CSerialGenerator 
{
private:
	tbb::atomic<unsigned __int32> m_currentSerialID;   ///< ������� �߱޵� �ø��� ���̵�

public:
	/// �ø����� �߱��Ѵ�
	unsigned __int32 GenerateSerialID();

public:
	CSerialGenerator(unsigned __int32 init_ = 1);
	~CSerialGenerator();
};


///////////////////////////////////////////////////////////////////////////////
// �� ������ ����ũ�� �ø��� ���� Ŭ����
// (�ش� ���μ����� ����ũ ���̵�(�������̵�))
///////////////////////////////////////////////////////////////////////////////
class CExternalSerialGenerator 
{
private:
	tbb::atomic<unsigned short> m_currentNumber;   ///< �ø��� ���տ� ī��Ʈ
	const __int64 m_uniqueAppID;                   ///< �ش� ���μ����� ����ũ�� ���̵�(�������̵�)


public:
	/// �ø����� �����Ѵ�.
	unsigned __int64 GenerateSerialID();


public:
	CExternalSerialGenerator(unsigned short uniqueAppId_ = 1);
	~CExternalSerialGenerator();
};

