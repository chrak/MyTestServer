#pragma once

#include <process.h>
#include <winsock2.h>
#include "tbb/concurrent_queue.h"
#include "vector"
#include "VirtualPoolObject.h"
#include "Define.h"


typedef std::vector<HANDLE> VEC_IOCP_HANDER;
template <typename T>
struct SThreadMessage
{
	typedef tbb::concurrent_queue<T*> THREAD_QUEUE;       
	THREAD_QUEUE queue;            ///< Task Thread�� taskQueue
	HANDLE       waitingEvent;     ///< taskThread�� ���� �۾��� ��ٸ��� ���� �ڵ�

	SThreadMessage()
	{
		waitingEvent = ::WSACreateEvent();
	}
};


///////////////////////////////////////////////////////////
// IOCP ������ ���
// <Derived class>
///////////////////////////////////////////////////////////
template <typename T>
class CIOCPThreadRegister
{
protected:
	struct _StWaitingEvent
	{
		HANDLE hWaitingEvent;      ///< thread�� �ʱ�ȭ�� �Ϸ�� ������ ��ٸ��� ���� �ڵ�
		HANDLE hIOCompltePort;     ///< IOCP�ڵ�
		HANDLE hThread;            ///< thread�� �ڵ�
		unsigned threadID;         ///< thread�� ID
		unsigned threadRegion;     ///< ������ �� ó���� ���� ���� ��ȣ
		T* pCaller;                ///< �����尡 ��������� ���������� this������
	};

protected:
	volatile bool m_bIsRunning;    ///< �������� ���� ����
	int  m_registedThreadCount;    ///< ��ϵ� ������ ��

public:
	/// �ϳ��� iocp �ڵ鿡 ���� �������� ������ ó�� ��� �Լ�
	/// ������ �Լ� ���(�ϳ��� iocp�� ���� ������ ��, iocp�ڵ�, ����Լ�)
	virtual bool RegisterThreadFunc(int nThreadCount_, HANDLE hCompletionPort_, _beginthreadex_proc_type threadFunc_);

	/// �������� iocp �ڵ鿡 ���� ���� ���� ������ ó�� ��� �Լ�
	/// ������ �Լ� ���(�������� ioco �ڵ�, ����Լ�)
	virtual bool RegisterThreadFunc(VEC_IOCP_HANDER& hCompletionPorts_, _beginthreadex_proc_type threadFunc_);

	/// ��ϵ� �������� ���� ����
	virtual bool IsRunning() const;

public:
	CIOCPThreadRegister();
	virtual ~CIOCPThreadRegister();
};


///////////////////////////////////////////////////////////
// �½�ũ ������ ���
// <Derived class, TaskQueue Object>
///////////////////////////////////////////////////////////
template <typename T_DERIVED, typename T_BASETASK>
class CTaskThreadRegister
{
protected:
	typedef std::vector<SThreadMessage<T_BASETASK>*> VEC_THREAD_MESSAGE;

	struct _StWaitingEvent
	{
		HANDLE hWaitingEvent;				  ///< thread�� �ʱ�ȭ�� �Ϸ�� ������ ��ٸ��� ���� �ڵ�
		HANDLE hThread;						  ///< thread�� �ڵ�
		unsigned threadID;                    ///< thread�� ID
		SThreadMessage<T_BASETASK>* message;  ///< task �޽��� ť
		T_DERIVED* pCaller;                   ///< �����尡 ��������� ���������� this������
	};

protected:
	volatile bool m_bIsRunning;		        ///< �������� ���� ����
	int  m_registedThreadCount;		        ///< ��ϵ� ������ ��
	VEC_THREAD_MESSAGE m_vecThreadMessage;  ///< �� �����忡 ���� task �޽��� ����

public:
	/// ������ ��� �Լ�(������ �� task ť, ��� �Լ�)
	virtual bool RegisterThreadFunc(VEC_THREAD_MESSAGE& messages_, _beginthreadex_proc_type threadFunc_);

	/// task �߰�
	void PushTask(int index_, T_BASETASK* task_);

	/// ��� task�� ���� flushó��
	virtual void FlushAllMessage();

	/// ��ϵ� �������� ���� ����
	virtual bool IsRunning() const;

public:
	CTaskThreadRegister();
	virtual ~CTaskThreadRegister();
};


