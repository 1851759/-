#ifndef __YUANCHENGSOLDIER__
#define __YUANCHENGSOLDIER__
#include "cocos2d.h"
#include "Soldier.h"
#include "Hero.h"

#define YuanchengNormalAttackRange 1000.0
#define YuanchengNormalAttackMoveSpeed 5.0




//在此处定义近战初始属性
#define YuanchengMoveSpeed 50.0
#define YuanchengAttackSpeed 0.4
#define YuanchengAttack 200.0
#define YuanchengDefence 20.0
#define YuanchengNormalAttackAfterShake 1.0/YuanchengAttackSpeed 
#define YuanchengHealthPoint 100.0
#define YuanchengMaxHealthPoint 100

class YuanchengSoldier : public Hero
{
	//设定小兵的名字
	//远程的名字为'C'
	char _soldierName;
	SoldierFlag _flag;

public:

	void setSoldierFlag(SoldierFlag flag) { _flag = flag; }
	int getSoldierFlag() const { return _flag; }

	virtual bool init();

	static YuanchengSoldier* create(SoldierFlag flag);

	virtual void update(float dt);

	void AIcontrol(Hero* soldier);

	void AIAction(float dt);

	void takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
};


#endif // !__YUANCHENGSOLDIER__
