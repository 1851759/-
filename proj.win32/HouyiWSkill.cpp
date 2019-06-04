//by 王文政 2019年5月27日
#include "cocos2d.h"

#include "HouyiHero.h"
#include "HouyiWSkill.h"

#include "SimpleAudioEngine.h"

HouyiWSkill* HouyiWSkill::createHouyiWSkill(Hero* hero)
{
	HouyiWSkill* arrow = new HouyiWSkill();
	if (arrow&&arrow->initWithFile("HouyiWSkill.png"))
	{
		arrow->setDamagePoint(HouyiWSkillDamage * hero->getWSkillLevel());
		arrow->setCanTakeDamage(true);
		arrow->setIfRemoveWhenDamage(true);
		arrow->autorelease();
		arrow->setScale(0.2);
		return arrow;
	}
	CC_SAFE_DELETE(arrow);
	return nullptr;
}

void HouyiWSkill::takeHouyiWSkill(HouyiHero* hero,float angle)
{
	cocos2d::Vec2 touchPoint = hero->getTouchPoint();
	cocos2d::Vec2 heroPoint = hero->getPosition();

	this->setPosition(heroPoint);
	this->setOriginPosition(heroPoint);
	//获取模长不为1的方向向量
	cocos2d::Vec2  directionWithDistance = touchPoint - heroPoint;

	//////////////////////////////////////////////////////////////////////////////////////////
	//让方向向量转过一个角度
	directionWithDistance.rotate(directionWithDistance-
								cocos2d::Vec2(directionWithDistance.x, directionWithDistance.y), angle);
	
	//////////////////////////////////////////////////////////////////////////////////
	//计算模长
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//获取单位向量
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	
	//将扇形的方向向量赋给成员_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//旋转//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.0001, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void HouyiWSkill::takeHouyiWSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint, float angle)
{
	this->setPosition(startPoint);
	this->setOriginPosition(startPoint);
	//获取模长不为1的方向向量
	cocos2d::Vec2  directionWithDistance = targetPoint - startPoint;

	//////////////////////////////////////////////////////////////////////////////////////////
	//让方向向量转过一个角度
	directionWithDistance.rotate(directionWithDistance -
		cocos2d::Vec2(directionWithDistance.x, directionWithDistance.y), angle);

	//////////////////////////////////////////////////////////////////////////////////
	//计算模长
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//获取单位向量
	cocos2d::Vec2 unitVector = directionWithDistance / distance;

	//将扇形的方向向量赋给成员_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//旋转//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.0001, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void HouyiWSkill::update(float dt)
{
	///这个是箭头移动速度//////////////////// ↓
	/////////////////////////////////////// ↓
	this->setPosition(this->getPosition() + HouyiWSkillMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//这个是箭头移动的最大距离////////// ↓
	////////////////////////////////  ↓
	cocos2d::Vec2 standardAttackRange(HouyiWSkillRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//未添加碰撞检测
}