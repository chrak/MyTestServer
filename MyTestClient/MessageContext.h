#pragma once
#include "PacketHeder.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

class CSession;

///////////////////////////////////////////////////////////
// packet�޽��� ó�� Ŭ����
///////////////////////////////////////////////////////////
class CMessageContext
{
private:
	int m_prevTick;          ///< ���� tick(�׽�Ʈ��)
	int m_testCount;		 ///< Ư�� ��Ŷ�� ���� ī��Ʈ(�׽�Ʈ��)
	std::string m_name;      ///< �ش� connector�� �̸�, Ŀ���ʹ� recv �����尡 �������(�׽�Ʈ��)
	
public:
	static int RTTCount;        ///< ��Ŷ�� �պ� ī��Ʈ(�׽�Ʈ��)

public:
	/// �޽��� ó��
	virtual bool MessageProc(packetdef::PacketID id_, protobuf::io::ArrayInputStream& io_);

public:
	/// ��Ŷ deserialize
	template<typename T>
	bool Deserialize(__out T& req, protobuf::io::ArrayInputStream& io_)
	{
		bool ret = req.ParseFromZeroCopyStream(&io_);
		return ret;
	}

	/// connector�� �̸��� ����Ѵ�
	void SetName(std::string const& name_);

	/// connector�� �̸��� ������ �´�
	inline std::string GetName() { return m_name; }

public:
	CMessageContext();
	virtual ~CMessageContext();
};