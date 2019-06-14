#ifndef __PAOCHESOLDIER__
#define __PAOCHESOLDIER__
#include "cocos2d.h"
#include "Soldier.h"
#include "Hero.h"

#define PaocheNormalAttackRange 100.0
#define PaocheNormalAttackMoveSpeed 5.0




//在此处定义近战初始属性
#define PaocheMoveSpeed 50.0
#define PaocheAttackSpeed 0.4
#define PaocheAttack 20.0
#define PaocheDefence 20.0
#define PaocheNormalAttackAfterShake 1.0/PaocheAttackSpeed 
#define PaocheHealthPoint 100.0
#define PaocheMaxHealthPoint 100

class PaocheSoldier : public Hero
{
	//设定小兵的名字
	//炮车的名字为'P'
	char _soldierName;
	PlayerFlag _flag;

public:

	void setSoldierFlag(PlayerFlag flag) { _flag = flag; }
	int getSoldierFlag() const { return _flag; }

	virtual bool init();

	static PaocheSoldier* create(PlayerFlag flag);

	virtual void update(float dt);

	void AIcontrol(Hero* soldier);

	void AIAction(float dt);

	void takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
};


#endif // !__PAOCHESOLDIER__
