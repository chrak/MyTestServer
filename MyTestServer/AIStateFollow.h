#pragma once
#include "AIState.h"


///////////////////////////////////////////////////////////
// AIState ���󰡱�
// (���� ����)
///////////////////////////////////////////////////////////
class CAIStateFollow :
	public CAIState
{
private:
	Vec3 m_targetPos;   ///< target�� ��ǥ
	double m_tickCount; ///<  ��ǥ ������ ���� ƽ

private:
	/// AI ���� ���ǿ� �´��� üũ
	bool _CheckCondition(CActor const* actor_);

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
	CAIStateFollow(E_STATE nextState_);
	virtual ~CAIStateFollow();
};