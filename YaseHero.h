//by 王文政 2019年5月30日
//这个类是亚瑟的类
//是Hero类的子类
//代码嫖后羿类


#ifndef __YASEHERO__
#define __YASEHERO__
#include "cocos2d.h"
#include "Hero.h"

//亚瑟技能属性
#define YaseNormalAttackRange 30.0
#define YaseNormalAttackMoveSpeed 4.0

#define YaseQSkillLastTime 5.0
#define YaseQSkillDefenceAdd 2.0
#define YaseQSkillCD 10.0
#define YaseQSkillAfterShake 1.0

#define YaseWSkillRange 200.0
#define YaseWSkillRollSpeed 3.0
#define YaseWSkillDamage 30
#define YaseWSkillCD 10.0
#define YaseWSkillLastTime 3.0
#define YaseWSkillAfterShake 1.0

#define YaseESkillRange 50.0
#define YaseESkillDamage 100
#define YaseESkillMoveSpeed 20.0
#define YaseESkillCD 10.0
#define YaseESkillAfterShake 1.0

//在此处定义亚瑟初始属性
#define YaseMoveSpeed 60.0
#define YaseAttackSpeed 0.4
#define YaseAttack 100.0
#define YaseDefence 100.0
#define YaseMaxHealth 250.0
#define YaseHealth 250.0
#define YaseMaxMagic 100.0
#define YaseMagic 100.0
#define YaseNormalAttackAfterShake 1.0/YaseAttackSpeed


typedef enum
{
	YaseBuffTag = 2223
} YaseBuff;



class YaseHero : public Hero
{
	//设定英雄的名字
	//亚瑟的名字为'Y'
	char _heroName;

public:

	virtual bool init();

	static YaseHero* create();

	void buffUpdate(float dt);

	void AIcontrol(Hero* hero);

	void AIAction(float dt);
};


#endif // !__YASEHERO__
