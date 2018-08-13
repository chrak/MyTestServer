#pragma once
#include "stdafx.h"
#include "Define.h"

class CSession;

///////////////////////////////////////////////////////////////////////////
// Server�� attach module �⺻ ���̽�
// (��� Ÿ��)
///////////////////////////////////////////////////////////////////////////
class CAttachModule
{
public:
	enum ModulerType 
	{
		Module_ServerMessage,
	};

private:
	ModulerType m_moduleType;  ///< ����� Ÿ��

public:
	/// ������ ���� �Ǿ��� �� ó��
	virtual void SessionClose(CSession* session_, int reason_);

	/// ������ ���� �Ǿ��� �� ó��
	virtual void Accept(SESSION_ID id_, CSession* session_);

	/// ������ �޽����� �޾��� �� ó��
	virtual void Recv(SESSION_ID id_, CSession* session_, int dwBytes_);

	/// ������ �޽����� ���� �� ó��
	virtual void Send(SESSION_ID id_, CSession* session_, int dwBytes_);

public:
	CAttachModule(ModulerType module_);
	virtual ~CAttachModule();
};