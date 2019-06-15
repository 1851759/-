#include "cocos2d.h"
#include "DajiHero.h"
#include "DajiNormalAttack.h"

DajiNormalAttack* DajiNormalAttack::createTheAttack(Hero* hero)
{
	DajiNormalAttack* normalAttack = new DajiNormalAttack();
	if (normalAttack&&normalAttack->initWithFile("DajiNormalAttack.png"))
	{
		normalAttack->setDamagePoint(hero->getAttackPoint());
		normalAttack->setCanTakeDamage(true);
		normalAttack->setIfRemoveWhenDamage(true);
		normalAttack->autorelease();
		normalAttack->setScale(0.05);
		return normalAttack;
	}
	CC_SAFE_DELETE(normalAttack);
	return nullptr;
}

void DajiNormalAttack::takeDajiNormalAttack(DajiHero* hero)
{
	cocos2d::Vec2 touchPoint = hero->getTouchPoint();
	cocos2d::Vec2 heroPoint = hero->getPosition();

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

	//把精灵旋转，让箭头指向点击方向

	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void DajiNormalAttack::takeDajiNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
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

	//把精灵旋转，让箭头指向点击方向

	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void DajiNormalAttack::update(float dt)
{
	///这个是箭头移动速度//////////////////// ↓
	/////////////////////////////////////// ↓
	this->setPosition(this->getPosition() + DajiNormalAttackMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//这个是箭头移动的最大距离////////// ↓
	////////////////////////////////  ↓
	cocos2d::Vec2 standardAttackRange(DajiNormalAttackRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//未添加碰撞检测
}