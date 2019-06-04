#include "cocos2d.h"
#include "Hero.h"


bool Hero::init()
{
	//下边的if里搞出了英雄的图片
	if (!Sprite::initWithFile("qqhero.png"))
	{
		return false;
	}

	return true;
}

Hero* Hero::create()
{
	Hero* sprite = new Hero();
	if (sprite->init())
	{
		sprite->autorelease();

	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}


	return sprite;
}


//以60帧计算冷却时间
//调用colddown函数减少冷却时间
//具体内容在update函数中
//重置冷却时间在gamescece函数监听部分实现


void Hero::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//平A冷却
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}
	//q技能冷却
	if (this->getQSkillWaitTime() >= 0.01)
	{
		this->cutQSkillWaitTime(cuttime);
	}
	//w技能冷却
	if (this->getWSkillWaitTime() >= 0.01)
	{
		this->cutWSkillWaitTime(cuttime);
	}
	//e技能冷却
	if (this->getESkillWaitTime() >= 0.01)
	{
		this->cutESkillWaitTime(cuttime);
	}
}








