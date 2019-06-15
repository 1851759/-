#include "cocos2d.h"
#include "YaseHero.h"
#include "YaseNormalAttack.h"
USING_NS_CC;
YaseNormalAttack* YaseNormalAttack::createTheAttack(Hero* hero)
{
	YaseNormalAttack* normalAttack = new YaseNormalAttack();
	if (normalAttack&&normalAttack->initWithFile("YaseNormalAttack.png"))
	{
		normalAttack->setDamagePoint(hero->getAttackPoint());
		normalAttack->setCanTakeDamage(true);
		normalAttack->setIfRemoveWhenDamage(true);
		normalAttack->autorelease();
		normalAttack->setScale(0.7);
		return normalAttack;
	}
	CC_SAFE_DELETE(normalAttack);
	return nullptr;
}

void YaseNormalAttack::takeYaseNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{
	this->setPosition(startPoint);
	this->setOriginPosition(startPoint);

	//��ȡģ����Ϊ1�ķ�������
	cocos2d::Vec2 directionWithDistance = targetPoint - startPoint;
	//����ģ��
	float distanceSquare = directionWithDistance.x*directionWithDistance.x + directionWithDistance.y*directionWithDistance.y;
	float distance = sqrt(distanceSquare);

	//��ȡ��λ����
	cocos2d::Vec2 unitVector = directionWithDistance / distance;
	//��ƽA�ķ�������������Ա_arrowMoveDirection
	this->setSwordMoveDirection(unitVector);

	//�Ѿ�����ת���ü�ͷָ��������
	cocos2d::RotateTo* rotateTo = cocos2d::RotateTo::create(0.01, -180.0 / 3.14*unitVector.getAngle());
	this->runAction(rotateTo);

	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void YaseNormalAttack::update(float dt)
{
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//����ǽ��ƶ���������////////// ��
	////////////////////////////////  ��
	cocos2d::Vec2 standardAttackRange(YaseNormalAttackRange, 0);
	float standardLength = standardAttackRange.x;
	if (go)
	{
		///����ǽ��ƶ��ٶ�//////////////////// ��
		/////////////////////////////////////// ��
		this->setPosition(this->getPosition() + YaseNormalAttackMoveSpeed * this->getSwordMoveDirection());
		/////////////////////////////////////////
		if (length >= YaseNormalAttackRange)
		{
			//	log("bb");
			go = false;
		}
	}
	else
	{
		this->setPosition(this->getPosition() - YaseNormalAttackMoveSpeed * this->getSwordMoveDirection());
		if (length <= 0.01)
		{
			this->removeFromParent();
		}
	}
	//δ�����ײ���
}
