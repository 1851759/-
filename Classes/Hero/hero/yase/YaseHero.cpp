//by 王文政 2019年5月30日
#include "cocos2d.h"
#include "YaseHero.h"
#include"YaseNormalAttack.h"
#include"YaseESkill.h"
USING_NS_CC;

YaseHero* YaseHero::create()
{
	YaseHero* yase = new YaseHero();
	if (yase->init())
	{

		yase->autorelease();

		//在下边初始化亚瑟的属性值////////////////////////////////////////////
		yase->setHeroName('Y');
		//基础移动速度
		yase->changeMoveSpeed(YaseMoveSpeed * cocos2d::Vec2(1.0, 0).x);

		//基础攻击速度，每秒攻击多少次
		yase->changeAttackSpeed(YaseAttackSpeed);
		yase->setAttackWaitTime(0);
		yase->setNormalAttackAfterShake(YaseNormalAttackAfterShake);
		yase->setHeroInSkake(false);

		//基础生命值
		yase->setHealthPoint(YaseHealth);
		yase->changeMaxHealthPoint(YaseHealth);
		//基础攻击力
		yase->changeAttackPoint(YaseAttack);
		//基础防御力
		yase->changeDefensePoint(YaseDefence);
		//基础等级
		yase->levelUp();
		//基础金币
		yase->setMoney(0);
		//基础经验值
		yase->setExpPoint(0);
		//q技能
		yase->qSkillLevelUp();//此处默认技能一级用于测试////////////////////////////////////
		yase->setQSkillCdTime(YaseQSkillCD);
		yase->setBuff(false);

		//w技能
		yase->wSkillLevelUp();
		yase->setWSkillCdTime(YaseWSkillCD);
		yase->setWSkillAfterShake(YaseWSkillAfterShake);

		//e技能
		yase->eSkillLevelUp();
		yase->setESkillCdTime(YaseESkillCD);
		yase->setESkillAfterShake(YaseESkillAfterShake);

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
	if (!Sprite::initWithFile("yase.png"))
	{
		return false;
	}
	this->setScale(0.3);
	this->createBlood();
	this->createLevel();

	return true;
}

void YaseHero::buffUpdate(float dt)
{
	float cuttime = 1.0 / 20.0;

	//buff持续时间
	if (this->getBuffTime() >= 0.01)
	{
		this->cutBuffTime(cuttime);
		//在此取消buff
		if (this->getBuffTime() <= 0.01)
		{
			this->changeDefensePoint(-this->getQSkillLevel()*YaseQSkillDefenceAdd);
			this->setNormalAttackAfterShake(1.0 / this->getAttackSpeed());
			this->removeChildByTag(YaseBuffTag);
		}
	}
	//获得buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//此处为获得的buff属性
		this->changeDefensePoint(this->getQSkillLevel()*YaseQSkillDefenceAdd);
		this->setNormalAttackAfterShake(1.0 / this->getAttackSpeed());
		Sprite* yaseBuff = Sprite::create("yaseBuff.png");
		yaseBuff->setPosition(0, 0);
		yaseBuff->setAnchorPoint(cocos2d::Vec2(0, 0));
		this->addChild(yaseBuff, 200, YaseBuffTag);
	}
}

//实现AI
void YaseHero::AIcontrol(Hero* hero)
{
	this->setOtherHero(hero);
	this->schedule(schedule_selector(YaseHero::AIAction), 1.0 / 20.0);
}

void YaseHero::AIAction(float dt)
{
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//移动AI
	if (this->getHeroAfterShake() <= 0.01)
	{
		cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
		float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		cocos2d::Vec2 standardDistance = distance / length;
		//AI亚瑟离玩家20以上
		if (length >= YaseNormalAttackRange-10)
		{
			this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
		}
	}
}
