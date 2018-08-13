#pragma once

#include <map>
#include "ServerBase.h"
#include "Singleton.h"

///////////////////////////////////////////////////////////////////////////
// Server Manager Class (�ϳ��� ���μ����� �������� ���� �ν��Ͻ��� ���� �� ����)
///////////////////////////////////////////////////////////////////////////
class CServerManager : 
	public CSingleton<CServerManager>
{
public:
	typedef std::map<CServerBase::SERVER_TYPE, CServerBase*> MAP_SERVER;

private:
	MAP_SERVER m_mapServer;      ///< ���� ��
	WSADATA m_wsaData;           ///< wsa �ʱ�ȭ ���� ����ü
	SYSTEM_INFO m_systemInfo;    ///< �ý��� ���� ���� ����ü

public:
	/// �ʱ�ȭ
	void Init();

	/// ���� ���� �� �Ŵ��� ���
	bool CreateServer(CServerBase::_StInitInfo const& serverInfo_);

	/// ���� ����
	bool RemoveServer(CServerBase::SERVER_TYPE const type_);

	/// ��ϵ� ��� ���� ����
	bool Start();

	/// ��ϵ� ��� ���� ���� �� ����
	void Close();

public:
	CServerManager();
	virtual ~CServerManager();
};