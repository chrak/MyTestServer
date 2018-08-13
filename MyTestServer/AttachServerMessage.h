#pragma once
#include "AttachModule.h"

class CSession;


///////////////////////////////////////////////////////////////////////////
// Server�� attach module - �޽��� ���
///////////////////////////////////////////////////////////////////////////
class CAttachServerMessage :
	public CAttachModule
{
public:
	/// ������ ���� �Ǿ��� �� ó��
	virtual void SessionClose(CSession* session_, int reason_) override;

	/// ������ ���� �Ǿ��� �� ó��
	virtual void Accept(SESSION_ID id_, CSession* session_) override;

	/// ������ �޽����� �޾��� �� ó��
	virtual void Recv(SESSION_ID id_, CSession* session_, int dwBytes_) override;

	/// ������ �޽����� ���� �� ó��
	virtual void Send(SESSION_ID id_, CSession* session_, int dwBytes_) override;

public:
	CAttachServerMessage();
	virtual ~CAttachServerMessage();
};