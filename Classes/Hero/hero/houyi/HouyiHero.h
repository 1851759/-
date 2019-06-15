#ifndef __HOUYIHERO__
#define __HOUYIHERO__
#include "cocos2d.h"
#include "Hero.h"


//后羿技能属性
#define HouyiNormalAttackRange 100.0
#define HouyiNormalAttackMoveSpeed 3.0


#define HouyiQSkillLastTime 5.0
#define HouyiQSkillAttackSpeedAdd 0.1
#define HouyiQSkillMoveSpeedAdd 1.0
#define HouyiQSkillCD 10.0
#define HouyiQSkillAfterShake 0.5

#define HouyiWSkillRange 300.0
#define HouyiWSkillDamage 100
#define HouyiWSkillArrowNumber 5
#define HouyiWSkillMoveSpeed 2.0
#define HouyiWSkillCD 8.0
#define HouyiWSkillAfterShake 0.5

#define HouyiESkillRange 1000.0
#define HouyiESkillDamage 100
#define HouyiESkillMoveSpeed 2.5
#define HouyiESkillCD 10.0
#define HouyiESkillAfterShake 0.5

//在此处定义后羿初始属性
#define HouyiMoveSpeed 70.0
#define HouyiAttackSpeed 0.6
#define HouyiAttack 100.0
#define HouyiDefence 60.0
#define HoyyiMaxHealth 500.0
#define HouyiHealth 500.0
#define HouyiMaxMagic 100.0
#define HouyiMagic 100.0
#define HouyiNormalAttackAfterShake 0.5/ HouyiAttackSpeed

typedef enum
{
	HouyiBuffTag = 2222,
} HouyiBuff;


class HouyiHero : public Hero
{
	//设定英雄的名字
	//后羿的名字为'H'
	char _heroName;

public:

	virtual bool init();

	static HouyiHero* create();

	void buffUpdate(float dt);

	void AIcontrol(Hero* hero);

	void AIAction(float dt);

};


#endif // !__HOUYIHERO__
