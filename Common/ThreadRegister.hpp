#include "stdafx.h"
#include "ThreadRegister.h"

template<typename T>
bool CIOCPThreadRegister<T>::RegisterThreadFunc(int nThreadCount_, HANDLE hCompletionPort_, _beginthreadex_proc_type threadFunc_)
{
	m_registedThreadCount = nThreadCount_;
	m_bIsRunning = true;

	HANDLE *pEvents = new HANDLE[nThreadCount_];
	_StWaitingEvent* waitingEvent = new _StWaitingEvent[nThreadCount_];

	for (int i = 0; i < nThreadCount_; ++i)
	{
		/// ������ ����
		waitingEvent[i].hIOCompltePort = hCompletionPort_;
		waitingEvent[i].hWaitingEvent = ::WSACreateEvent();
		waitingEvent[i].hThread = (HANDLE)_beginthreadex(NULL, 0, threadFunc_, reinterpret_cast<LPVOID>(&waitingEvent[i]), 0, &waitingEvent[i].threadID);
		waitingEvent[i].pCaller = static_cast<T*>(this);
		pEvents[i] = waitingEvent[i].hWaitingEvent;

		// �α�
	}

	/// ������ �����尡 ��� ����� �� ������ ���
	::WSAWaitForMultipleEvents(nThreadCount_, pEvents, TRUE, INFINITE, FALSE);
	return true;
}


template<typename T>
bool CIOCPThreadRegister<T>::RegisterThreadFunc(VEC_IOCP_HANDER& hCompletionPorts_, _beginthreadex_proc_type threadFunc_)
{
	int nThreadCount = static_cast<int>(hCompletionPorts_.size());
	if (nThreadCount <= 0)
	{
		// �α�
		return false;
	}

	m_registedThreadCount = nThreadCount;
	m_bIsRunning = true;

	HANDLE *pEvents = new HANDLE[nThreadCount];
	_StWaitingEvent* waitingEvent = new _StWaitingEvent[nThreadCount];

	for (int i = 0; i < nThreadCount; ++i)
	{
		/// ������ ����
		waitingEvent[i].hIOCompltePort = hCompletionPorts_[i];
		waitingEvent[i].hWaitingEvent = ::WSACreateEvent();
		waitingEvent[i].hThread = (HANDLE)_beginthreadex(NULL, 0, threadFunc_, reinterpret_cast<LPVOID>(&waitingEvent[i]), 0, &waitingEvent[i].threadID);
		waitingEvent[i].threadRegion = i;
		waitingEvent[i].pCaller = static_cast<T*>(this);
		pEvents[i] = waitingEvent[i].hWaitingEvent;

		// �α�
	}

	/// ������ �����尡 ��� ����� �� ������ ���
	::WSAWaitForMultipleEvents(nThreadCount, pEvents, TRUE, INFINITE, FALSE);
	return true;
}


template<typename T>
bool CIOCPThreadRegister<T>::IsRunning() const
{
	return m_bIsRunning;
}


template <typename T>
CIOCPThreadRegister<T>::CIOCPThreadRegister()
{
}


template <typename T>
CIOCPThreadRegister<T>::~CIOCPThreadRegister()
{
	m_bIsRunning = false;
}



template <typename T_DERIVED, typename T_BASETASK>
bool CTaskThreadRegister<T_DERIVED, T_BASETASK>::RegisterThreadFunc(VEC_THREAD_MESSAGE& messages_, _beginthreadex_proc_type threadFunc_)
{
	int nThreadCount = static_cast<int>(messages_.size());
	if (nThreadCount <= 0)
	{
		// �α�
		return false;
	}

	m_registedThreadCount = nThreadCount;
	m_bIsRunning = true;

	HANDLE *pEvents = new HANDLE[nThreadCount];
	_StWaitingEvent* waitingEvent = new _StWaitingEvent[nThreadCount];

	for (int i = 0; i < nThreadCount; ++i)
	{
		/// ������ ����
		waitingEvent[i].hWaitingEvent = ::WSACreateEvent();
		waitingEvent[i].message = messages_[i];
		waitingEvent[i].hThread = (HANDLE)_beginthreadex(NULL, 0, threadFunc_, reinterpret_cast<LPVOID>(&waitingEvent[i]), 0, &waitingEvent[i].threadID);
		waitingEvent[i].pCaller = static_cast<T_DERIVED*>(this);
		pEvents[i] = waitingEvent[i].hWaitingEvent;

		// �α�
	}

	/// ������ �����尡 ��� ����� �� ������ ���
	::WSAWaitForMultipleEvents(nThreadCount, pEvents, TRUE, INFINITE, FALSE);

	return true;
}


template <typename T_DERIVED, typename T_BASETASK>
void CTaskThreadRegister<T_DERIVED, T_BASETASK>::PushTask(int index_, T_BASETASK* task_)
{
	if (task_ == NULL)
	{
		// �α�
		return;
	}

	/// �ش� �ε����� �´� queue�� ���� ����
	SThreadMessage<T_BASETASK>* message = m_vecThreadMessage[index_];
	message->queue.push(task_);
	::WSASetEvent(message->waitingEvent);
}


template <typename T_DERIVED, typename T_BASETASK>
void CTaskThreadRegister<T_DERIVED, T_BASETASK>::FlushAllMessage()
{
	// don't call this
}


template <typename T_DERIVED, typename T_BASETASK>
bool CTaskThreadRegister<T_DERIVED, T_BASETASK>::IsRunning() const
{
	return m_bIsRunning;
}


template <typename T_DERIVED, typename T_BASETASK>
CTaskThreadRegister<T_DERIVED, T_BASETASK>::CTaskThreadRegister()
{
}


template <typename T_DERIVED, typename T_BASETASK>
CTaskThreadRegister<T_DERIVED, T_BASETASK>::~CTaskThreadRegister()
{
}

