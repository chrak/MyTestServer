#include "stdafx.h"
#include "Actor.h"
#include "AIStateHit.h"
#include "PCManager.h"


bool CAIStateHit::CheckCondition(CActor const* actor_, CAIState* state_)
{
	CActor* target = CPCManager::GetInstance().FindPC(actor_->GetTargetID());
	if (target && target->IsValid())
	{

	}
	else
	{
		/// �ٸ� Ÿ���� ã��
	}
	return false;
}


void CAIStateHit::Enter(CActor* actor_, LIST_FSM_CONDITON const* conditions_)
{
	m_pCurrentStateConditions = const_cast<LIST_FSM_CONDITON*>(conditions_);
	m_bIsPlaying = true;
	// ���Ͱ� �ɸ� ������ ���� actionState ����
	actor_->SetActionState(E_ACTOR_STATE::ACTOR_KNOCKBACK);

}


bool CAIStateHit::Execute(CActor* actor_)
{
	return __super::Execute(actor_);

}


void CAIStateHit::Leave(CActor* actor_)
{
	m_bIsPlaying = false;
}


CAIStateHit::CAIStateHit(E_STATE nextState_)
	: CAIState(nextState_)
{

}


CAIStateHit::~CAIStateHit()
{

}