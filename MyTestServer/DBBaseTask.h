#pragma once
#include "stdafx.h"
#include "Define.h"
#include "msado15.tlh"

struct SConnectionInfo
{
	_ConnectionPtr connection_ptr;
	_RecordsetPtr record_ptr;
	_CommandPtr command_ptr;
};

///////////////////////////////////////////////////////////
// DB Taskó���� ���� Base Ŭ����
///////////////////////////////////////////////////////////
class CDBBaseTask
{
protected:
	_ConnectionPtr m_connection_ptr;
	_RecordsetPtr m_record_ptr;
	_CommandPtr m_command_ptr;

	USER_ID m_userID;                   ///< userID
	THREAD_REGION m_threadRegion;       ///< DBTask�� ����Ǵ� Thread�� ���� ��ȣ

public:
	/// �ʱ�ȭ �Լ�
	virtual void Init(SConnectionInfo* connInfo_);

	/// ����
	virtual bool Execute();

	/// �αױ��
	virtual void WriteLog();

	/// �ش� task�� ȣ���� userID�� ������ �´�
	inline USER_ID GetCallerUserID() const { return m_userID; }

	/// DBTask�� ����Ǵ� Thread�� ������ȣ�� ������ �´�
	inline THREAD_REGION GetThreadRegion() const { return m_threadRegion; }

	/// task�� ȣ���ϴ� User�� userID�� ����
	inline void SetCallerUserID(USER_ID userID_) { m_userID = userID_; }

	/// DBTask�� ����� Thread�� ������ȣ ����
	inline void SetThreadRegion(THREAD_REGION region_) { m_threadRegion = region_; }

public:
	CDBBaseTask();
	virtual ~CDBBaseTask();
};