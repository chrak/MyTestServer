#pragma once
#include "AIState.h"


///////////////////////////////////////////////////////////
// AIState ���ƴٴϱ�
// (���� ����)
///////////////////////////////////////////////////////////
class CAIStateWander :
	public CAIState
{
private:
	float TargetX;  ///< ��ǥ�� x ��ǥ
	float TargetY;  ///< ��ǥ�� y ��ǥ

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
	CAIStateWander(E_STATE nextState_);
	virtual ~CAIStateWander();
};