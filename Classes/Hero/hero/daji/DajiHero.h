#ifndef __DAJIHERO__
#define __DAJIHERO__
#include "cocos2d.h"
#include "Hero.h"


//妲己技能属性
#define DajiNormalAttackRange 100.0
#define DajiNormalAttackMoveSpeed 3.0


#define DajiQSkillRange 350.0
#define DajiQSkillMoveSpeed 3.0
#define DajiQSkillDamage 120
#define DajiQSkillCD 7.0
#define DajiQSkillAfterShake 0.5

#define DajiWSkillRange 300.0
#define DajiWSkillMoveSpeed 2.0
#define DajiWSkillDamage 200
#define DajiWSkillCD 8.0
#define DajiWSkillAfterShake 0.5

#define DajiESkillRange 200.0
#define DajiESkillArrowNumber 6
#define DajiESkillMoveSpeed 3.0
#define DajiESkillDamage 80
#define DajiESkillCD 10.0
#define DajiESkillAfterShake 0.5
#define DajiESkillArrowNumber 6
#define DajiESkillArrowInterval 50

//在此处定义妲己初始属性
#define DajiMoveSpeed 70.0
#define DajiAttackSpeed 0.4
#define DajiAttack 80.0
#define DajiMaxHealth 500.0
#define DajiHealth 500.0
#define DajiMaxMagic 200.0
#define DajiMagic 100.0
#define DajiDefence 100.0
#define DajiNormalAttackAfterShake 0.5/ DajiAttackSpeed


class DajiHero : public Hero
{
	//设定英雄的名字
	//妲己的名字为'D'
	char _heroName;


public:

	virtual bool init();

	static DajiHero* create();

	void AIcontrol(Hero* hero);

	void AIAction(float dt);
};


#endif // !__DAJIHERO__
