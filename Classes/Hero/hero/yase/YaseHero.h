#ifndef __YASEHERO__
#define __YASEHERO__
#include "cocos2d.h"
#include "Hero.h"

//亚瑟技能属性
#define YaseNormalAttackRange 30.0
#define YaseNormalAttackMoveSpeed 4.0

#define YaseQSkillLastTime 6.0
#define YaseQSkillDefenceAdd 2.0
#define YaseQSkillCD 10.0
#define YaseQSkillAfterShake 0.5

#define YaseWSkillRange 75.0
#define YaseWSkillRollSpeed 1.0//3.0
#define YaseWSkillDamage 30
#define YaseWSkillCD 8.0
#define YaseWSkillLastTime 5.0//3.0
#define YaseWSkillRollNumber 10//20
#define YaseWSkillAfterShake 0.5

#define YaseESkillRange 300.0
#define YaseESkillDamage 150
#define YaseESkillMoveSpeed 15.0
#define YaseESkillCD 10.0
#define YaseESkillAfterShake 0.5

//在此处定义亚瑟初始属性
#define YaseMoveSpeed 80.0
#define YaseAttackSpeed 0.5
#define YaseAttack 100.0
#define YaseDefence 80.0
#define YaseMaxHealth 600.0.0
#define YaseHealth 600.0
#define YaseMaxMagic 100.0
#define YaseMagic 100.0
#define YaseNormalAttackAfterShake 0.5//YaseAttackSpeed


typedef enum
{
	YaseBuffTag = 2223
} YaseBuff;



class YaseHero : public Hero
{
	//设定英雄的名字
	//亚瑟的名字为'Y'
	char _heroName;
	int bloodbar;

public:

	virtual bool init();

	static YaseHero* create();

	void buffUpdate(float dt);

	void AIcontrol(Hero* hero);

	void AIAction(float dt);
};


#endif // !__YASEHERO__
