#pragma once
#include <winsock2.h>

///////////////////////////////////////////////////////////
// CSessionManagerBase Class
// CSessionManagerBase class�� �ݵ�� �ش� Ŭ������ ��ӹ޾ƾ� ��
///////////////////////////////////////////////////////////
class CSession;
class CSessionManagerBase
{
public:
	/// ������ �����
	virtual CSession* CreateSession(SOCKET const& socket_) = 0;
};
