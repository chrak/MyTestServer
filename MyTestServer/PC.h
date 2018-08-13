#pragma once

#include <map>
#include "Actor.h"
#include "AIState.h"
#include "Define.h"
#include "PacketHeder.h"
#include "VirtualPoolObject.h"


class CSession;

///////////////////////////////////////////////////////////
// PC Ŭ����
///////////////////////////////////////////////////////////
class CPC :
	public CVirtualPoolObject,
	public CActor
{
public:
	struct _StInit
	{
		USER_ID userID;       ///< userID
		SERIAL_ID serialID;   ///< user�� serialID
	};

private:
	CSession* m_pSession;     ///< session
	USER_ID   m_userID;       ///< userID

public:
	/// userID�� ������ �´�
	inline USER_ID GetUserID() const { return m_userID; }

	/// session�� ������ �´�
	inline CSession* GetSession() { return m_pSession; }

	/// session�� ����Ѵ�.
	void SetSession(CSession* session_);

	/// ������Ʈ Ǯ���� ������ �� ȣ��
	virtual bool Leave(void* initParam_) override;

	/// ������Ʈ Ǯ�� �� �� ȣ��
	virtual bool Enter() override;

	/// ������Ʈ
	virtual void Update() override;

	/// ���� AI���¿� ���� ���� ����
	virtual void SetAIPlayState(bool bIs_) override;

	/// ��ȿ�� actor�ΰ�
	virtual bool IsValid() const override;


public:
	CPC();
	virtual ~CPC();
};