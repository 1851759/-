//by 王文政 2019年5月27日
#include "cocos2d.h"
#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"


HouyiHero* HouyiHero::create()
{
	HouyiHero* houyi = new HouyiHero();
	if (houyi->init())
	{
		
		houyi->autorelease();

		//在下边初始化后羿的属性值////////////////////////////////////////////
		houyi->setHeroName('H');
		//基础移动速度
		houyi->changeMoveSpeed(HouyiMoveSpeed);
		
		//基础攻击速度，每秒攻击多少次
		houyi->changeAttackSpeed(HouyiAttackSpeed);
		houyi->setAttackWaitTime(0);

		//基础攻击力

		//基础防御力

		//基础等级

		//基础金币

		//基础经验值

		//q技能
		houyi->qSkillLevelUp();//此处默认技能一级用于测试////////////////////////////////////
		houyi->setQSkillCdTime(HouyiQSkillCD);
		houyi->setBuff(false);

		//w技能
		houyi->wSkillLevelUp();
		houyi->setWSkillCdTime(HouyiWSkillCD);

		//e技能
		houyi->eSkillLevelUp();
		houyi->setESkillCdTime(HouyiESkillCD);
	}
	else
	{
		delete houyi;
		houyi = NULL;
		return NULL;
	}


	return houyi;
}

bool HouyiHero::init()
{
	//下边的if里搞出了英雄的图片
	if (!Sprite::initWithFile("HouyiHero.png"))
	{
		
		return false;
	}
	this->setScale(0.5);
	return true;
}





void HouyiHero::update(float dt)
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
			this->changeMoveSpeed(-this->getQSkillLevel() * HouyiQSkillMoveSpeedAdd);
			this->changeAttackSpeed(-this->getQSkillLevel() * HouyiQSkillAttackSpeedAdd);
		}
	}
	//获得buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//此处为获得的buff属性
		this->changeMoveSpeed(this->getQSkillLevel() * HouyiQSkillMoveSpeedAdd);
		this->changeAttackSpeed(this->getQSkillLevel() * HouyiQSkillAttackSpeedAdd);
	}

}

//实现AI
void HouyiHero::AIcontrol(Hero* hero)
{
	/*
	this->setHeroPoint(this->getPosition());
	this->setOtherHeroPoint(hero->getPosition());
	*/
	this->setOtherHero(hero);
	this->schedule(schedule_selector(HouyiHero::AIAction),1.0/60.0f);
}
	
void HouyiHero::AIAction(float dt)
{
//	cocos2d::log("%f  %f\n",this->getOtherHero()->getPosition().x, this->getOtherHero()->getPosition().y);
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//移动AI
	cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
	float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	cocos2d::Vec2 standardDistance = distance / length;
	this->setPosition(this->getPosition() + standardDistance);
	
	

}





