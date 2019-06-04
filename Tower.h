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
	//获得和改变等待时间
	float getAttackWaitTime() { return _attackWaitTime; }
	void cutAttackWaitTime(float waittime) { _attackWaitTime -= waittime; }
	void setAttackWaitTime(float waittime) { _attackWaitTime = waittime; }

	//获得和改变攻击速度
	float getAttackSpeed() const { return _attackSpeed; }
	void changeAttackSpeed(const float equipmentAttackSpeed) { _attackSpeed += equipmentAttackSpeed; }

	//获得和改变攻击力
	float getAttackForce() const { return _attackForce; }
	void changeAttackForce(const float equipmentAttackForce) { _attackForce += equipmentAttackForce; }

	//获得和改变防御力
	float getDefenceForce() const { return _defenceForce; }
	void changeDefenceForce(const float equipmentDefenceForce) { _defenceForce += equipmentDefenceForce; }

	//获得和改变生命值
	float getHealthPoint() const { return _healthPoint; }
	void changeHealthPoint(const float equipmentHealthPoint) { _healthPoint += equipmentHealthPoint; }
	void update(float dt);
};

#endif // __TOWER_H__
