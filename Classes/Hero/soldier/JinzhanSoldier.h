#ifndef __JINZHANSOLDIER__
#define __JINZHANSOLDIER__
#include "cocos2d.h"
#include "Soldier.h"
#include "Hero.h"

#define JinzhanNormalAttackRange 40.0
#define JinzhanNormalAttackMoveSpeed 5.0




//在此处定义近战初始属性
#define JinzhanMoveSpeed 50.0
#define JinzhanAttackSpeed 0.4
#define JinzhanAttack 20.0
#define JinzhanDefence 20.0
#define JinzhanNormalAttackAfterShake 1.0/JinzhanAttackSpeed 
#define JinzhanHealthPoint 100.0
#define JinzhanMaxHealthPoint 100

class JinzhanSoldier : public Hero
{
	//设定小兵的名字
	//近战的名字为'J'
	char _soldierName;
	PlayerFlag _flag;

public:

	void setSoldierFlag(PlayerFlag flag) { _flag = flag; }
	int getSoldierFlag() const { return _flag; }

	virtual bool init();

	static JinzhanSoldier* create(PlayerFlag flag);

	virtual void update(float dt);

	void AIcontrol(Hero* soldier);

	void AIAction(float dt);

	void takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
};


#endif // !__JINZHANSOLDIER__