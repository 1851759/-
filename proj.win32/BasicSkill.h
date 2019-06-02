//by ������ 2019��6��3��
//���м��ܵĻ���

#ifndef __BASICSKILL__
#define __BASICSKILL__

#include "cocos2d.h"

class BasicSkill : public cocos2d::Sprite
{
	bool _canTakeDamage;
	bool _removeWhenDamage;
	//��ɵ��˺���ֵ
	float _damagePoint;

public:
	float getDamagePoint() const { return _damagePoint; }
	void setDamagePoint(float damagePoint) { _damagePoint = damagePoint; }

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
