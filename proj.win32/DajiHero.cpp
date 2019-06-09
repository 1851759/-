#include "cocos2d.h"
#include "DajiHero.h"
#include "DajiNormalAttack.h"
#include "DajiESkill.h"


DajiHero* DajiHero::create()
{
	DajiHero* daji = new DajiHero();
	if (daji->init())
	{

		daji->autorelease();

		//在下边初始化妲己的属性值////////////////////////////////////////////
		daji->setHeroName('D');
		//基础移动速度
		daji->changeMoveSpeed(DajiMoveSpeed * cocos2d::Vec2(1.0, 0).x);

		//基础攻击速度，每秒攻击多少次
		daji->changeAttackSpeed(DajiAttackSpeed);
		daji->setAttackWaitTime(0);
		daji->setNormalAttackAfterShake(DajiNormalAttackAfterShake);
		daji->setHeroInSkake(false);

		//基础生命值
		daji->setHealthPoint(DajiHealth);
		daji->changeMaxHealthPoint(DajiHealth);
		//基础攻击力
		daji->changeAttackPoint(DajiAttack);
        //基础防御力
		daji->changeDefensePoint(DajiDefence);
		//基础等级
		daji->levelUp();
		//基础金币
		daji->setMoney(0);
		//基础经验值
		daji->setExpPoint(0);
		//q技能
		daji->qSkillLevelUp();//此处默认技能一级用于测试////////////////////////////////////
		daji->setQSkillCdTime(DajiQSkillCD);
		daji->setQSkillAfterShake(DajiQSkillAfterShake);

		//w技能
		daji->wSkillLevelUp();
		daji->setWSkillCdTime(DajiWSkillCD);
		daji->setWSkillAfterShake(DajiWSkillAfterShake);

		//e技能
		daji->eSkillLevelUp();
		daji->setESkillCdTime(DajiESkillCD);
		daji->setESkillAfterShake(DajiESkillAfterShake);
	}
	else
	{
		delete daji;
		daji = NULL;
		return NULL;
	}


	return daji;
}

bool DajiHero::init()
{
	//下边的if里搞出了英雄的图片
	if (!Sprite::initWithFile("DajiHero.png"))
	{

		return false;
	}
	this->setScale(0.2);
	return true;
}




//实现AI
void DajiHero::AIcontrol(Hero* hero)
{
	/*
	this->setHeroPoint(this->getPosition());
	this->setOtherHeroPoint(hero->getPosition());
	*/
	this->setOtherHero(hero);
	this->schedule(schedule_selector(DajiHero::AIAction), 1.0 / 60.0f);
}

void DajiHero::AIAction(float dt)
{
	//	cocos2d::log("%f  %f\n",this->getOtherHero()->getPosition().x, this->getOtherHero()->getPosition().y);
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//移动AI
	if (this->getHeroAfterShake() <= 0.01)
	{
		cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
		float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		cocos2d::Vec2 standardDistance = distance / length;
		//AI妲己离玩家80以上
		if (length >= 80.0)
		{
			this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
			//	cocos2d::log(" speed %f", this->getMoveSpeed());
		}
	}





}