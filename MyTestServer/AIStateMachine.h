#pragma once
#include "AIState.h"
#include <queue>


class CActor;
class CAIState;

///////////////////////////////////////////////////////////
// FSM Ŭ����
// (������ ����)
///////////////////////////////////////////////////////////
class CAIStateMachine
{
public:
	struct _StAIStateEvent {
		E_STATE           state;
		E_STATE_CONDITION condition;
	};
	typedef std::queue<_StAIStateEvent> QUEUE_AI_EVENT;

private:
	MAP_FSM m_stateMachine;        ///< ���º� ���ǵ鿡 ���� ��
	CAIState* m_pCurrentState;     ///< ���� ������ AIState
	CActor* m_pActor;              ///< ���� actor
	QUEUE_AI_EVENT m_eventQueue;   ///< �ܺο����� ���� ���¿����� AI ���� ���� ť

public:
	/// AI ���� �� ���� ���(����, ����, AIState)
	bool RegistState(E_STATE state_, E_STATE_CONDITION condiiton_, CAIState* stateMachine_);

	/// ��ϵ� ���� �߿��� ������ AIState�� ���� ���·� �����Ѵ�(����, ����)
	bool SetCurrentState(E_STATE state_, E_STATE_CONDITION condition_);

	/// ���� ���¸� ������ AIState�� ���� ���·� ����
	bool SetNextState(CAIState* state_);

	/// ��ϵ� ���� �߿��� �ش� AIState�� �����Ѵ�(����, ����)
	bool RemoveState(E_STATE state_, E_STATE_CONDITION condition_);

	/// ���� AI�� �÷��� ������ ����
	void SetCurrentPlayState(bool bIs_);

	/// �ܺο��� �ش� ������ Ư�� ������ ������ �����ϱ� ���� �̺�Ʈ�� ����
	void PushEvent(_StAIStateEvent const& condition_);

	/// ������Ʈ
	void Update();

public:
	CAIStateMachine(CActor* actor_);
	~CAIStateMachine();
};