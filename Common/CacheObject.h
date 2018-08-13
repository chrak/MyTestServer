#pragma once


///////////////////////////////////////////////////////////
// ĳ�� ������Ʈ
///////////////////////////////////////////////////////////
class CCacheObject
{
private:
	__int64 m_key;           ///< ĳ�� Ű
	__int64 m_expireTimer;   ///< ĳ�� ���� �ð�   
	bool    m_bIsCacheWait;      ///< ĳ�� ����

public:
	/// ĳ�� Ű�� ������ �´�.
	inline __int64 GetCacheKey() const { return m_key; }

	/// ĳ�� ����
	inline bool IsWaitCache() const { return m_bIsCacheWait; }

	/// ĳ���� ������Ʈ�� �ʱ�ȭ
	void Init(__int64 key_, __int64 after_);

	/// ĳ�� ���� �ð��� ������ �´�
	inline __int64 GetExpireTimer() const { return m_expireTimer; }

	/// ĳ�� ������ ���� ���� ����
	virtual void SetCacheWaitState(bool is_);

	/// �ð��� ����Ǿ� ĳ�ÿ��� ������ �� �ִ����� ���� ���� �Ǵ�
	virtual bool CheckEnableReleaseCache() const;

public:
	CCacheObject();
	virtual ~CCacheObject();
};