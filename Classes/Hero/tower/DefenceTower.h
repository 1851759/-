#ifndef __DEFENCETOWER__
#define __DEFENCETOWER__
#include "cocos2d.h"
#include"Hero.h"


#define DefenceNormalAttackRange 200.0
#define DefenceNormalAttackMoveSpeed 3.5



//在此处定义防御塔初始属性
#define DefenceAttackSpeed 0.3
#define DefenceAttack 150.0
#define DefenceDefence 100.0


class DefenceTower : public Hero
{
	//设定塔的名字
	//防御塔的名字为'F'
	char _towerName;
	PlayerFlag _flag;


public:
	void setTowerFlag(PlayerFlag flag) { _flag = flag; }
	int getTowerFlag() const { return _flag; }

	virtual bool init();

	static DefenceTower* create(PlayerFlag flag);

	virtual void update(float dt);

	void AIcontrol(Hero* tower);

	void AIAction(float dt);

	void takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
};


#endif // !__DEFENCETOWER__