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
		bigSword->setCanTakeDamage(false);
		bigSword->setIfRemoveWhenDamage(false);
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
	cocos2d::Vec2 distance = targetPoint - startPoint;//��ȡ�û������λ���뾫������λ�õ�����
	float length = sqrt(distance.x*distance.x + distance.y*distance.y);//��ȡ����֮��ľ���
	cocos2d::Vec2 unitVector = distance / length;//��ȡ��λ����
	this->setSwordMoveDirection(unitVector);//����λ��������_swordMOveDirection
	this->setPosition((startPoint + 50 * unitVector).x,900);
	this->setOriginPosition(startPoint + 50 * unitVector);
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void YaseESkill::update(float dt)
{
	this->setPosition(this->getPosition() - YaseESkillMoveSpeed * cocos2d::Vec2(0, 1));
	log("%d %d %d %d", this->getPosition().x, this->getPosition().y, this->getOriginPosition().x, this->getOriginPosition().y);
	if ((this->getPosition()).y>=(this->getOriginPosition()).y-10&& (this->getPosition()).y <= (this->getOriginPosition()).y + 10)
	{
		this->setIfRemoveWhenDamage(true);
		this->removeFromParent();
	}
}