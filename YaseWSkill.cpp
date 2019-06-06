#include"cocos2d.h"

#include"YaseHero.h"
#include"YaseWSkill.h"
#include"GameScene.h"
#include"SimpleAudioEngine.h"


YaseWSkill* YaseWSkill::createYaseWSkill(Hero* hero)
{
	YaseWSkill* roll = new YaseWSkill();
	if (roll&&roll->initWithFile("YaseWSkill.png"))
	{
		roll->setDamagePoint(YaseWSkillDamage*hero->getWSkillLevel());
		roll->setCanTakeDamage(true);
		roll->setIfRemoveWhenDamage(false);
		roll->autorelease();
		roll->setScale(0.8);
		return roll;
	}
	CC_SAFE_DELETE(roll);
	return nullptr;
}

void YaseWSkill::takeYaseWSkill(Hero* hero)
{
	isRoll = true;
	this->setPosition(hero->getPosition());
	/*this->setOriginPosition(hero->getPosition());*/
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(2.0, 1080);
	this->runAction(rotateTo);
	this->unscheduleUpdate();
	this->scheduleUpdate();
	this->scheduleOnce(schedule_selector(YaseWSkill::stop), 2);
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