#include"cocos2d.h"

#include"YaseHero.h"
#include"YaseWSkill.h"
#include"GameScene.h"

YaseWSkill* YaseWSkill::createYaseWSkill(Hero* hero)
{
	YaseWSkill* roll = new YaseWSkill();
	if (roll&&roll->initWithFile("YaseWSkill.png"))
	{
		roll->setDamagePoint(YaseWSkillDamage*hero->getWSkillLevel());
		roll->setCanTakeDamage(true);
		roll->setIfRemoveWhenDamage(false);
		roll->autorelease();
		roll->setScale(2.8);
		return roll;
	}
	CC_SAFE_DELETE(roll);
	return nullptr;
}

void YaseWSkill::takeYaseWSkill(Hero* hero)
{
	isRoll = true;
	this->setPosition(cocos2d::Vec2::ZERO);
	/*this->setOriginPosition(hero->getPosition());*/
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(YaseWSkillLastTime, YaseWSkillRollNumber * 360);
	this->runAction(rotateTo);
	this->unscheduleUpdate();
	this->scheduleUpdate();
	this->scheduleOnce(schedule_selector(YaseWSkill::stop), YaseWSkillLastTime);
}

void YaseWSkill::update(float dt)
{
	if (isRoll == false)
	{
		this->removeFromParent();
	}
}

void YaseWSkill::stop(float dt)
{
	isRoll = false;
}