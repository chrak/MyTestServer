#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>

#include "string"
#include "list"
#include "SessionManager.h"
#include "ThreadRegister.h"


class CAttachModule;

///////////////////////////////////////////////////////////
// Listner Class
// (session manager)
///////////////////////////////////////////////////////////
class CListener : 
	public CIOCPThreadRegister<CListener>
{
private:
	typedef std::list<CAttachModule*> ATTACH_MODULE_LIST;

	ATTACH_MODULE_LIST m_moduleList;   ///< ������ �����ϴ� ����Ʈ
	CSessionManagerBase* m_sessionMgr; ///< �ش� serverBase�� ��ϵǾ� �ִ� sessionManager
	SOCKET m_listenSocket;             ///< Listen ����

public: 
	/// Listner Thread ��� �� ����
	SOCKET Start(HANDLE hCompletionPort_, u_short nPortNum_);

	/// ����, ��������, ������, �ޱ� ���� �Ͼ�� ���� ���� ����� ���
	bool AttachModule(CAttachModule* module_);

	/// Thread ����
	void Close();

	/// Accept�� �Ͼ�� ���� ���� ���ν��� 
	static unsigned CALLBACK AcceptProc(void* data_);
	
public:
	CListener(CSessionManager* sessionMgr);
	virtual ~CListener();
};
