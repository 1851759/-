//by 王文政 2019年5月30日
#include "cocos2d.h"
#include "YaseHero.h"


YaseHero* YaseHero::create()
{
	YaseHero* yase = new YaseHero();
	if (yase->init())
	{

		yase->autorelease();

		//在下边初始化后羿的属性值////////////////////////////////////////////
		yase->setHeroName('Y');
		//基础移动速度
		yase->changeMoveSpeed(60);

		//基础攻击速度，每秒攻击多少次
		yase->changeAttackSpeed(0.5);
		yase->setAttackWaitTime(0);

		//q技能
		yase->qSkillLevelUp();//此处默认技能一级用于测试////////////////////////////////////
		yase->setQSkillCdTime(10);
		yase->setBuff(false);

		//w技能
		yase->wSkillLevelUp();
		yase->setWSkillCdTime(5);

		//e技能
		yase->eSkillLevelUp();
		yase->setESkillCdTime(2);
	}
	else
	{
		delete yase;
		yase = NULL;
		return NULL;
	}


	return yase;
}

bool YaseHero::init()
{
	//下边的if里搞出了英雄的图片
	if (!Sprite::initWithFile("YaseHero.png"))
	{
		return false;
	}

	return true;
}

void YaseHero::update(float dt)
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
	//buff持续时间
	if (this->getBuffTime() >= 0.01)
	{
		this->cutBuffTime(cuttime);
		//在此处取消buff
		if (this->getBuffTime() <= 0.01)
		{
			//此处为应减去的属性
			this->changeMoveSpeed(-this->getQSkillLevel() * 200);
			this->changeAttackSpeed(-this->getQSkillLevel() * 20);
		}
	}
	//获得buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//此处为获得的buff属性
		this->changeMoveSpeed(this->getQSkillLevel() * 200);
		this->changeAttackSpeed(this->getQSkillLevel() * 20);
	}
}