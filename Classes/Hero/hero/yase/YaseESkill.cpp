#include"cocos2d.h"

#include"YaseHero.h"
#include"YaseESkill.h"

#include"SimpleAudioEngine.h"
USING_NS_CC;
YaseESkill *YaseESkill::createYaseESkill(Hero* hero)
{
	YaseESkill* bigSword = new YaseESkill();
	if (bigSword&&bigSword->initWithFile("YaseESkill.png"))
	{
		bigSword->setCanTakeDamage(true);
		bigSword->setIfRemoveWhenDamage(true);
		bigSword->setDamagePoint(YaseESkillDamage* hero->getESkillLevel());
		bigSword->autorelease();
		bigSword->setScale(0.5);
		return bigSword;
	}
	CC_SAFE_DELETE(bigSword);
	return nullptr;
}

void YaseESkill::takeYaseESkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{
	cocos2d::Vec2 distance = targetPoint - startPoint;//获取用户点击的位置与精灵所在位置的向量
	float length = sqrt(distance.x*distance.x + distance.y*distance.y);//获取两者之间的距离
	cocos2d::Vec2 unitVector = distance / length;//获取单位向量
	this->setSwordMoveDirection(unitVector);//将单位向量赋给_swordMOveDirection
	this->setPosition(targetPoint+ Vec2(0,500));
	this->setOriginPosition(targetPoint + Vec2(0, 500));
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void YaseESkill::update(float dt)
{
	this->setPosition(this->getPosition() - YaseESkillMoveSpeed * cocos2d::Vec2(0, 1));
	log("%d %d %d %d", this->getPosition().x, this->getPosition().y, this->getOriginPosition().x, this->getOriginPosition().y);
	if ((this->getPosition()).y >= (this->getOriginPosition()).y - 10 && (this->getPosition()).y <= (this->getOriginPosition()).y + 10)
	{
		this->setIfRemoveWhenDamage(true);
		this->removeFromParent();
	}
}