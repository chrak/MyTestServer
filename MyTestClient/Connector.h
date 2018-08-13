#pragma once

#include "Common/ThreadRegister.h"
#include "Define.h"
#include "Session.h"
#include "Receiver.h"
#include "Sender.h"


class CMessageContext;

///////////////////////////////////////////////////////////
// CConnector Ŭ����
///////////////////////////////////////////////////////////
class CConnector
{
public:
	struct _StInit
	{
		std::string strConnectionAddr;
		unsigned short nPort;

		_StInit& operator=(const _StInit& rhs_) {
			strConnectionAddr = rhs_.strConnectionAddr;
			nPort = rhs_.nPort;
			return *this;
		}

		explicit _StInit(const _StInit& rhs_)
		{
			this->operator=(rhs_);
		}

		_StInit()
		{
		}
	};

private:
	_StInit m_conInfo;	   ///< Ŀ�ؼ��� �� ������ ����
	CSession* m_pSession;  ///< Ŀ������ ���� ������
	CReceiver m_receiver;  ///< Ŀ���Ϳ� �����ϴ� receiver
	CSender m_sender;      ///< Ŀ���Ϳ� �����ϴ� sender
	std::string m_name;    ///< Ŀ�ؼ��� ������ ���� �̸�(�׽�Ʈ�� ���̵�)


public:
	/// recv �޽����� �޾� �ö� �ش��ϴ� context�� ����Ͽ� �ʱ�ȭ�Ѵ�
	void Init(CMessageContext* workerHander_);

	/// �ش� Ŀ�ؼ��� ������ �Ǿ��°�
	bool IsConnected() const;

	/// ��ϵǾ� �ִ� Ŀ�ؼ� ������ ������ ���� �� recv, send ���� �����Ѵ�
	bool Start(_StInit const& init_);

	/// Ŀ�ؼ��� �ݰ� ���� ������ �����Ѵ�
	void Close();

	/// �ش� Ŀ�ؼ��� receiver�� ������ �´�
	CReceiver* GetReceiver();

	/// �ش� Ŀ�ؼ��� sender�� ������ �´�
	CSender* GetSender();

	/// �ش� Ŀ�ؼ��� ������ ������ �´�
	CSession* GetSession();


public:
	CConnector();
	~CConnector();
};

// ������.
extern CConnector Connector;