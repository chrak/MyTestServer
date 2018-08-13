#pragma once
#include <string>
#include "DBBaseTask.h"
#include "ThreadRegister.h"

///////////////////////////////////////////////////////////
// DBó�� Ŭ����
// <Derive class, DBTask>
///////////////////////////////////////////////////////////
class CAdoOleDB :
	public CTaskThreadRegister<CAdoOleDB, CDBBaseTask>
{
public:
	enum DB_TYPE
	{
		ACCOUNT_DB,
		GAME_DB,
		LOG_DB,
	};

	struct _StInitInfo
	{
		tstring userID;             ///< userID
		tstring pass;			    ///< password
		tstring ipAddress;          ///< �����ּ�
		tstring dbName;             ///< DB ��Ű�� �̸�
		DWORD port;                 ///< ��Ʈ
		DB_TYPE dbType;             ///< DB Ÿ��
		int nSessionThreadCount;    ///< �ش� �ּҿ� ���� ���� ���� ��
	};
	typedef std::vector<SConnectionInfo*> VEC_CONNECTION_INFO;

private:
	VEC_CONNECTION_INFO m_vecConnInfo;                                 ///< DB���� ���� ����
	_StInitInfo m_dbInfo;                                              ///< DB����
	bool m_bInit;                                                      ///< �ʱ�ȭ ����

public:
	/// �ʱ�ȭ �Լ�
	void Init(_StInitInfo const& info_);

	/// theread ����
	bool Start();

	/// ���� ���� ����
	void ReleaseDB();

	/// DBTask �߰�
	void PushTask(CDBBaseTask* task_);

	/// ��� DBTask�� ���� flush ó��
	virtual void FlushAllMessage() override;

	/// �޽��� ó�� ������
	static unsigned CALLBACK MessageProc(void* data_);

public:
	CAdoOleDB();
	virtual ~CAdoOleDB();
};