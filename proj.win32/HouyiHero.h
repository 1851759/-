//by 王文政 2019年5月26日
//这个类是后羿的类
//是Hero类的子类


#ifndef __HOUYIHERO__
#define __HOUYIHERO__
#include "cocos2d.h"
#include "Hero.h"

#define HouyiNormalAttackRange 100.0
#define HouyiNormalAttackMoveSpeed 3.0


#define HouyiQSkillLastTime 5.0
#define HouyiQSkillAttackSpeedAdd 2.0
#define HouyiQSkillMoveSpeedAdd 20.0
#define HouyiQSkillCD 10.0

#define HouyiWSkillRange 200.0
#define HouyiWSkillArrowNumber 13
#define HouyiWSkillMoveSpeed 3.0
#define HouyiWSkillCD 10

#define HouyiESkillRange 1000.0
#define HouyiESkillMoveSpeed 5.0
#define HouyiESkillCD 10.0

//在此处定义后羿初始属性
#define HouyiMoveSpeed 60.0
#define HouyiAttackSpeed 0.5
#define HouyiAttack 100.0
#define HouyiDefence 100.0

class HouyiHero : public Hero
{
	//设定英雄的名字
	//后羿的名字为'H'
	char _heroName;


public:

	virtual bool init();

	static HouyiHero* create();

	virtual void update(float dt);

	void AIcontrol(Hero* hero);

	void AIAction(float dt);
};


#endif // !__HOUYIHERO__
