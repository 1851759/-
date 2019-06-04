//by ������ 2019��5��27��
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
	//��ȡģ����Ϊ1�ķ�������
	cocos2d::Vec2  directionWithDistance = touchPoint - heroPoint;

	//////////////////////////////////////////////////////////////////////////////////////////
	//�÷�������ת��һ���Ƕ�
	directionWithDistance.rotate(directionWithDistance-
								cocos2d::Vec2(directionWithDistance.x, directionWithDistance.y), angle);
	
	//////////////////////////////////////////////////////////////////////////////////
	//����ģ��
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//��ȡ��λ����
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	
	//�����εķ�������������Ա_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//��ת//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.0001, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void HouyiWSkill::takeHouyiWSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint, float angle)
{
	this->setPosition(startPoint);
	this->setOriginPosition(startPoint);
	//��ȡģ����Ϊ1�ķ�������
	cocos2d::Vec2  directionWithDistance = targetPoint - startPoint;

	//////////////////////////////////////////////////////////////////////////////////////////
	//�÷�������ת��һ���Ƕ�
	directionWithDistance.rotate(directionWithDistance -
		cocos2d::Vec2(directionWithDistance.x, directionWithDistance.y), angle);

	//////////////////////////////////////////////////////////////////////////////////
	//����ģ��
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//��ȡ��λ����
	cocos2d::Vec2 unitVector = directionWithDistance / distance;

	//�����εķ�������������Ա_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//��ת//////
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.0001, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void HouyiWSkill::update(float dt)
{
	///����Ǽ�ͷ�ƶ��ٶ�//////////////////// ��
	/////////////////////////////////////// ��
	this->setPosition(this->getPosition() + HouyiWSkillMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//����Ǽ�ͷ�ƶ���������////////// ��
	////////////////////////////////  ��
	cocos2d::Vec2 standardAttackRange(HouyiWSkillRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//δ�����ײ���
}