#ifndef __TOWER_H__
#define __TOWER_H__
#include "cocos2d.h"


USING_NS_CC;

class Tower :public Sprite
{
	float _attackSpeed;
	float _attackForce;
	float _defenceForce;
	float _healthPoint;
	float _attackWaitTime;


public:
	virtual bool init();
	static Tower* create();
	//��ú͸ı�ȴ�ʱ��
	float getAttackWaitTime() { return _attackWaitTime; }
	void cutAttackWaitTime(float waittime) { _attackWaitTime -= waittime; }
	void setAttackWaitTime(float waittime) { _attackWaitTime = waittime; }

	//��ú͸ı乥���ٶ�
	float getAttackSpeed() const { return _attackSpeed; }
	void changeAttackSpeed(const float equipmentAttackSpeed) { _attackSpeed += equipmentAttackSpeed; }

	//��ú͸ı乥����
	float getAttackForce() const { return _attackForce; }
	void changeAttackForce(const float equipmentAttackForce) { _attackForce += equipmentAttackForce; }

	//��ú͸ı������
	float getDefenceForce() const { return _defenceForce; }
	void changeDefenceForce(const float equipmentDefenceForce) { _defenceForce += equipmentDefenceForce; }

	//��ú͸ı�����ֵ
	float getHealthPoint() const { return _healthPoint; }
	void changeHealthPoint(const float equipmentHealthPoint) { _healthPoint += equipmentHealthPoint; }
};
#endif // __TOWER_H__