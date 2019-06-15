#include "cocos2d.h"

#include "DajiHero.h"
#include "DajiESkill.h"

#include "SimpleAudioEngine.h"

DajiESkill* DajiESkill::createDajiESkill(Hero* hero)
{
	DajiESkill* bigBall = new DajiESkill();
	if (bigBall&&bigBall->initWithFile("DajiESkill.png"))
	{
		bigBall->setCanTakeDamage(true);
		bigBall->setIfRemoveWhenDamage(true);
		bigBall->setDamagePoint(DajiESkillDamage * hero->getESkillLevel());
		bigBall->autorelease();
		bigBall->setScale(0.1);
		return bigBall;
	}
	CC_SAFE_DELETE(bigBall);
	return nullptr;
}

void DajiESkill::takeDajiESkill(DajiHero* hero)
{
	cocos2d::Vec2 touchPoint = hero->getTouchPoint();
	cocos2d::Vec2 heroPoint = hero->getPosition();
	//cocos2d::log("toouchPoint %f %f ", touchPoint.x, touchPoint.y);
	//cocos2d::log("heroPoint %f %f ", heroPoint.x, heroPoint.y);
	this->setPosition(heroPoint);
	this->setOriginPosition(heroPoint);
	//获取模长不为1的方向向量
	cocos2d::Vec2  directionWithDistance = touchPoint - heroPoint;
	//计算模长
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//获取单位向量
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	//将平A的方向向量赋给成员_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//旋转//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void DajiESkill::takeDajiESkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{
	this->setPosition(startPoint);
	this->setOriginPosition(startPoint);
	//获取模长不为1的方向向量
	cocos2d::Vec2  directionWithDistance = targetPoint - startPoint;
	//计算模长
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//获取单位向量
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	//将平A的方向向量赋给成员_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//旋转//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}


void DajiESkill::update(float dt)
{
	///这个是箭头移动速度//////////////////// ↓
	/////////////////////////////////////// ↓
	this->setPosition(this->getPosition() + DajiESkillMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//这个是箭头移动的最大距离////////// ↓
	////////////////////////////////  ↓
	cocos2d::Vec2 standardAttackRange(DajiESkillRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//未添加碰撞检测
}