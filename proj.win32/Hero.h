//英雄的基类，用来测试移动和技能释放


#ifndef __HERO__
#define __HERO__

#include "cocos2d.h"

//通过枚举类型定义英雄的tag
//英雄的tag
typedef enum
{
	Hero_Tag = 102
} HeroTags;

//英雄进行各种动作时的tag
typedef enum
{
	HeroMove = 10,
	HeroUseSkillQ = 11,
	HeroUseSkillW = 12,
	HeroUseSkillE = 13,
	HeroUseSkillA = 14
} HeroAction;


//定义英雄的状态 活着或者死了
typedef	enum
	{
	dead = 1,
	alive = 2
	} status;


class Hero : public cocos2d::Sprite
{
	//在此处添加英雄的属性数值
	//该版本目的为测试移动和技能释放所以暂不定义英雄属性


	float _moveSpeed;


public:

	//重写SPrite类的init函数
	virtual bool init();
	static Hero* create();


	float getMoveSpeed() { return _moveSpeed; } const
		void changeMoveSpeed(const float equipmentMoveSpeed) { _moveSpeed += equipmentMoveSpeed; }

	
	
};





#endif // !__HERO__

