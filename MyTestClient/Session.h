#pragma once
#include <winsock2.h>


class CConnector;

///////////////////////////////////////////////////////////
// CSession Ŭ����
// (session�� �ش��ϴ� connector������)
///////////////////////////////////////////////////////////
class CSession
{
private:
	SOCKET m_hSock;                  ///< ���� �ڵ�
	const CConnector* m_pConnector;  ///< session�� �ش��ϴ� connector������
	bool m_bIsConnect;               ///< connect�� �ش��ϴ� ���� ���� ����

public:
	/// ���� connector�� ������ �´�
	CConnector const* GetConnector();

	/// ���� ����
	bool IsConnected() const;

	/// ���� ���� ����
	void SetConnectionState(bool is_);

	/// ���� �ڵ��� ������ �´�
	SOCKET GetSocket() const;

	/// ������ �ݴ´�
	void CloseSocket();

public:
	explicit CSession(CConnector const* connector_);
	~CSession();
};
