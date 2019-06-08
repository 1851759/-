#ifndef __DAJIHERO__
#define __DAJIHERO__
#include "cocos2d.h"
#include "Hero.h"


//妲己技能属性
#define DajiNormalAttackRange 100.0
#define DajiNormalAttackMoveSpeed 3.0


#define DajiQSkillRange 5.0
#define DajiQSkillMoveSpeed 3.0
#define DajiQSkillDamage 120
#define DajiQSkillCD 1.0
#define DajiQSkillAfterShake 1.0

#define DajiWSkillRange 200.0
#define DajiWSkillMoveSpeed 3.0
#define DajiWSkillDamage 150
#define DajiWSkillCD 10.0
#define DajiWSkillAfterShake 1.0

#define DajiESkillRange 200.0
#define DajiESkillArrowNumber 6
#define DajiESkillMoveSpeed 5.0
#define DajiESkillDamage 80
#define DajiESkillCD 10.0
#define DajiESkillAfterShake 1.0

//在此处定义妲己初始属性
#define DajiMoveSpeed 60.0
#define DajiAttackSpeed 0.4
#define DajiAttack 80.0
#define DajiMaxHealth 200.0
#define DajiHealth 200.0
#define DajiMaxMagic 200.0
#define DajiMagic 100.0
#define DajiDefence 100.0
#define DajiNormalAttackAfterShake 1.0/ DajiAttackSpeed


class DajiHero : public Hero
{
	//设定英雄的名字
	//妲己的名字为'D'
	char _heroName;


public:

	virtual bool init();

	static DajiHero* create();

	virtual void update(float dt);

	void AIcontrol(Hero* hero);

	void AIAction(float dt);
};


#endif // !__DAJIHERO__
