#pragma once


///////////////////////////////////////////////////////////
// CSessionBase Class
// Session class�� �ݵ�� �ش� Ŭ������ ��ӹ޾ƾ� ��
///////////////////////////////////////////////////////////
class CSessionBase
{
public:
	/// �޽��� �ؼ� ���� ����
	virtual void  SetTranslateMessageState(bool state_) = 0;    
};