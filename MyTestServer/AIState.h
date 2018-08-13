#pragma once
#include <map>
#include <list>

enum E_STATE
{
	IDLE,
	FOLLOW,
	ATTACK,
	RETURN,
	HEAL
};


enum E_STATE_CONDITION
{
	HIT,
	ENCOUNTER,
	ARRIVE,
	DYING,
	WANDER,
	PATROL,
	DEFAULT,
	END,
};


class CAIState;
class CActor;
class CAIStateMachine;
typedef std::list<CAIState*> LIST_FSM_CONDITON;
typedef std::map<E_STATE, LIST_FSM_CONDITON*> MAP_FSM;

///////////////////////////////////////////////////////////
// AIState BaseClass
// (���� ����)
///////////////////////////////////////////////////////////
class CAIState
{
protected:
	CAIStateMachine* m_pFSM;                           ///< FSM Ŭ����
	E_STATE m_nextState;                               ///< ���� ����
	E_STATE_CONDITION m_currentConState;               ///< ���� ����
	LIST_FSM_CONDITON* m_pCurrentStateConditions;      ///< ���� ���¿� ���� ���Ǻ� aiState ��
	bool m_bIsPlaying;                                 ///< ���� ������ AI�� �÷��� ������ ����

public:
	/// FSM ��ü ������ ����
	void SetFSM(CAIStateMachine* fsm_);

	/// ���� AI �÷��� ���� ����
	void SetPlayState(bool bIs_);

	/// �ش� ��ü�� ������ ����
	void SetCurrentCondition(E_STATE_CONDITION condition_);

	/// ������ AI �÷��� ���� ��������
	inline bool IsPlaying() { return m_bIsPlaying; }

	/// ���� ���¸� �����´�
	inline E_STATE GetNextState() { return m_nextState; }

	/// �ش� ������Ʈ�� ������ �����´�
	inline E_STATE_CONDITION GetStateCondition() { return m_currentConState; }

	/// ���� ���¿� ���� ���Ǻ� aiState ���� �����´�
	LIST_FSM_CONDITON const* GetConditions();
	
	/// AI ���� ���ǿ� �´��� üũ
	virtual bool CheckCondition(CActor const* actor_, CAIState* state_);

	/// AI ����
	virtual void Enter(CActor* actor_, LIST_FSM_CONDITON const* conditions_);

	/// AI ����
	virtual bool Execute(CActor* actor_);

	/// AI ���� �� ����
	virtual void Leave(CActor* actor_);

public:
	CAIState(E_STATE nextState_);
	virtual ~CAIState();
};