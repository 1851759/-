#ifndef __BASICSPRITE__
#define __BASICSPRITE__

#include "cocos2d.h"

class BasicSprite : public cocos2d::Sprite
{
	//��ɵ��˺���ֵ
	int _damagePoint;
	//Ѫ��
	int _healthPoint;
	//����ֵ
	int _experiencePoint;
	//���
	int _money;

public:
	int getDamagePoint() const { return _damagePoint; }
	void setDamagePoint(int point) { _damagePoint = point; }

	int getHealthPoint() const { return _healthPoint; }
	void setHealthPoint(int point) { _healthPoint = point; }
	void sufferDamage(int damage) { _healthPoint -= damage; }

	int getExpPoint() const { return _experiencePoint; }
	void setExpPoint(int point) { _experiencePoint = point; }

	int showMeTheMoney() const { return _money; }
	void setMoney(int point) { _money = point; }
};


#endif // !__BASICSPRITE__

