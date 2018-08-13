#pragma once

#include "Actor.h"
#include "AIState.h"
#include <map>


class CAIStateMachine;

///////////////////////////////////////////////////////////
// NPC Ŭ����
///////////////////////////////////////////////////////////
class CNPC :
	public CActor
{
private:
	CAIStateMachine* m_stateMachine;    ///< FSM Ŭ����


public:
	///  AI ������Ʈ
	virtual void Update() override;

	/// ���� AI���¿� ���� ���� ����
	virtual void SetAIPlayState(bool bIs_) override;

	/// ��ȿ�� actor�ΰ�
	virtual bool IsValid() const override;
	

public:
	CNPC();
	virtual ~CNPC();
};