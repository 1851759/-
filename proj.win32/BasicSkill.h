//by ������ 2019��6��3��
//���м��ܵĻ���

#ifndef __BASICSKILL__
#define __BASICSKILL__

#include "cocos2d.h"
#include "BasicSprite.h"

class BasicSkill : public BasicSprite
{
	bool _canTakeDamage;
	bool _removeWhenDamage;

public:
	
	//�ж��ܷ�����˺�
	//Ϊtrueʱ��������˺�
	//Ϊfalseʱ������ײ
	bool canTakeDamage() const { return _canTakeDamage; }
	void setCanTakeDamage(bool can) { _canTakeDamage = can; }

	//�жϼ�������˺����Ƿ�remove
	//Ϊtrueʱ ����˺���ɾ��
	//Ϊfalseʱ ����˺���ɾ��
	bool shouldRemove() const { return _removeWhenDamage; }
	void setIfRemoveWhenDamage(bool can) { _removeWhenDamage = can; }

};

#endif // !__BASICSKILL__
