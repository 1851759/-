#include "cocos2d.h"

#include "JieHero.h"
#include "JieQSkill.h"


JieQSkill* JieQSkill::createJieQSkill(Hero* hero)
{
	JieQSkill* star = new JieQSkill();
	if (star&&star->initWithFile("JieQSkill.png"))
	{
		star->setCanTakeDamage(true);
		star->setIfRemoveWhenDamage(false);
		star->setDamagePoint(JieQSkillDamage * hero->getQSkillLevel());
		star->autorelease();
		star->setScale(0.4);
		return star;
	}
	CC_SAFE_DELETE(star);
	return nullptr;
}

void JieQSkill::takeJieQSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
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
	cocos2d::RotateTo* roll = cocos2d::RotateTo::create(4, 10 * 360);
	this->runAction(roll);
	this->unscheduleUpdate();
	this->scheduleUpdate();
}


void JieQSkill::update(float dt)
{
	///这个是箭头移动速度//////////////////// ↓
	/////////////////////////////////////// ↓
	this->setPosition(this->getPosition() + JieQSkillMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//这个是箭头移动的最大距离////////// ↓
	////////////////////////////////  ↓
	cocos2d::Vec2 standardAttackRange(JieQSkillRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//未添加碰撞检测
}