#pragma once
#include <stdlib.h>


///////////////////////////////////////////////////////////////////////////////
// ������Ʈ Ǯ�� ������ �������� 1ȸ������ ����ϱ� ���� Ŭ����
///////////////////////////////////////////////////////////////////////////////
class CScopePoolObj
{
private:
	void* m_buffer;     ///< ������Ʈ Ǯ���� ������ ����    
	size_t m_size;      ///< ���� ������

public:
	/// ���۸� ������ �´�.
	inline void* GetBuffer() { return m_buffer; }

public:
	CScopePoolObj(size_t size_);
	~CScopePoolObj();
};