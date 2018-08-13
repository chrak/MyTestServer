#pragma once

#include <winsock2.h>
#include <map>
#include <string>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_hash_map.h>
#include "CacheManager.h"
#include "Session.h"
#include "VirtualMemoryPool.h"
#include "Singleton.h"
#include "SerialGenerator.h"
#include "ServerCore/SessionManagerBase.h"


class CSreverBase;

///////////////////////////////////////////////////////////////////////////
// Session Manager Class
// (session�� ���� ���� �޸�Ǯ ������, Ǯ�� �þ�� ������, ���� ����)
///////////////////////////////////////////////////////////////////////////
class CSessionManager : 
	public CSessionManagerBase,
	public CVirtualMemmoryPool<CSession>,
	public CCacheManager<CSession>
{
public:

	typedef tbb::concurrent_hash_map<SESSION_ID, CSession*> SESSION_MAP;          
	typedef tbb::concurrent_unordered_map<std::string, SESSION_ID> CERTIFICATION_MAP;
	
private:
	SESSION_MAP m_mapSession;       ///< ���� ��
	CERTIFICATION_MAP m_mapCertify; ///< �������� ��

	CServerBase* m_pServer;      ///< �����ϴ� ����
	CSerialGenerator m_serialGen;    ///< �ø��� ������

private:
	/// ���� ������ �ٲ�ġ�� �Ѵ�(ĳ�õ� ���ǰ� ��� ������ ������ ����)
	void ExechangeSession(CSession*& __out lhs_, CSession* rhs_);

public:
	inline SESSION_ID GenerateSerialID() { return m_serialGen.GenerateSerialID(); }

	/// ������ �����
	virtual CSession* CreateSession(SOCKET const& socket_);  

	/// ������ �Ŵ����� ����Ѵ�
	/// (recv Thread���� �����ؾ� session ������ ����������)
	SESSION_ID RegistSession(CSession*& __out session_, SESSION_ID sessionid_, std::string const& id_, std::string const& pass_);

	/// sessionID�� �´� ������ ã�´�
	CSession* FindSession(SESSION_ID sessionID_);

	/// ������ �ı��Ѵ�
	void DestroySession(SESSION_ID sessionID_);

	/// ��� ���ǿ��� �޽����� ������
	void SendAll(packetdef::PacketID id_, protobuf::Message* message_);

	/// ĳ�� ���¿��� �����Ѵ�
	virtual void ReleaseCache(CCacheObject* obj_) override;

public:
	CSessionManager();
	CSessionManager(int poolSize_, int poolInterval_, CServerBase* server_);
	virtual ~CSessionManager();
};