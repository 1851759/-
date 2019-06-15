#include "cocos2d.h"

#include "DajiHero.h"
#include "DajiQSkill.h"

#include "SimpleAudioEngine.h"

DajiQSkill* DajiQSkill::createDajiQSkill(Hero* hero)
{
	DajiQSkill* bigMoon = new DajiQSkill();
	if (bigMoon&&bigMoon->initWithFile("DajiQSkill.png"))
	{
		bigMoon->setCanTakeDamage(true);
		bigMoon->setIfRemoveWhenDamage(true);
		bigMoon->setDamagePoint(DajiQSkillDamage * hero->getQSkillLevel());
		bigMoon->autorelease();
		bigMoon->setScale(0.1);
		return bigMoon;
	}
	CC_SAFE_DELETE(bigMoon);
	return nullptr;
}

void DajiQSkill::takeDajiQSkill(DajiHero* hero)
{
	cocos2d::Vec2 touchPoint = hero->getTouchPoint();
	cocos2d::Vec2 heroPoint = hero->getPosition();
	//cocos2d::log("toouchPoint %f %f ", touchPoint.x, touchPoint.y);
	//cocos2d::log("heroPoint %f %f ", heroPoint.x, heroPoint.y);
	this->setPosition(heroPoint);
	this->setOriginPosition(heroPoint);
	//��ȡģ����Ϊ1�ķ�������
	cocos2d::Vec2  directionWithDistance = touchPoint - heroPoint;
	//����ģ��
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//��ȡ��λ����
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	//��ƽA�ķ�������������Ա_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//��ת//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void DajiQSkill::takeDajiQSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{
	this->setPosition(startPoint);
	this->setOriginPosition(startPoint);
	//��ȡģ����Ϊ1�ķ�������
	cocos2d::Vec2  directionWithDistance = targetPoint - startPoint;
	//����ģ��
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//��ȡ��λ����
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	//��ƽA�ķ�������������Ա_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//��ת//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}


void DajiQSkill::update(float dt)
{
	///����Ǽ�ͷ�ƶ��ٶ�//////////////////// ��
	/////////////////////////////////////// ��
	this->setPosition(this->getPosition() + DajiQSkillMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//����Ǽ�ͷ�ƶ���������////////// ��
	////////////////////////////////  ��
	cocos2d::Vec2 standardAttackRange(DajiQSkillRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//δ�����ײ���
}