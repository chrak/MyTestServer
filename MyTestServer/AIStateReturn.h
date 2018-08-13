#pragma once
#include "AIState.h"


///////////////////////////////////////////////////////////
// AIState ���ư���
// (���� ����)
///////////////////////////////////////////////////////////
class CAIStateReturn :
	public CAIState
{
public:
	/// AI ���� ���ǿ� �´��� üũ
	virtual bool CheckCondition(CActor const* actor_, CAIState* state_) override;

	/// AI ����
	virtual void Enter(CActor* actor_, LIST_FSM_CONDITON const* conditions_) override;

	/// AI ����
	virtual bool Execute(CActor* actor_) override;

	/// AI ���� �� ����
	virtual void Leave(CActor* actor_) override;

public:
	CAIStateReturn(E_STATE nextState_);
	virtual ~CAIStateReturn();
};