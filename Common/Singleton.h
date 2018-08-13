#pragma once

///////////////////////////////////////////////////////////////////////////////
// �̱��� ��ӿ� Ŭ����
// <Derived Class>
///////////////////////////////////////////////////////////////////////////////
template<typename T>
class CSingleton
{	
public:
	/// �ش� �Ļ� Ŭ������ ���� �ν��Ͻ��� ������ �´�
	static T& GetInstance()
	{
		static T instance;    
		return instance;
	}
	
private:
	CSingleton(const CSingleton& val_) {}
	const CSingleton& operator=(const CSingleton& val_) {}

protected:
	CSingleton() {}
	virtual ~CSingleton() {}
};

