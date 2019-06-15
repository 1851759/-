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
		normalAttack->setScale(0.2);
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
	//��ȡģ����Ϊ1�ķ�������
	cocos2d::Vec2  directionWithDistance = touchPoint - heroPoint;
	//����ģ��
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//��ȡ��λ����
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	//��ƽA�ķ�������������Ա_arrowMoveDirection
	this->setArrowMoveDirection(unitVector);

	//�Ѿ�����ת���ü�ͷָ��������

	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void DajiNormalAttack::takeDajiNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
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

	//�Ѿ�����ת���ü�ͷָ��������

	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void DajiNormalAttack::update(float dt)
{
	///����Ǽ�ͷ�ƶ��ٶ�//////////////////// ��
	/////////////////////////////////////// ��
	this->setPosition(this->getPosition() + DajiNormalAttackMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//����Ǽ�ͷ�ƶ���������////////// ��
	////////////////////////////////  ��
	cocos2d::Vec2 standardAttackRange(DajiNormalAttackRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//δ������ײ���
}