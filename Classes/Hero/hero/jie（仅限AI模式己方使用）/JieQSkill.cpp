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
	cocos2d::RotateTo* roll = cocos2d::RotateTo::create(4, 10 * 360);
	this->runAction(roll);
	this->unscheduleUpdate();
	this->scheduleUpdate();
}


void JieQSkill::update(float dt)
{
	///����Ǽ�ͷ�ƶ��ٶ�//////////////////// ��
	/////////////////////////////////////// ��
	this->setPosition(this->getPosition() + JieQSkillMoveSpeed * this->getArrowMoveDirection());

	/////////////////////////////////////////
	cocos2d::Vec2 distance = this->getPosition() - this->getOriginPosition();
	float lengthSquare = distance.x*distance.x + distance.y*distance.y;
	float length = sqrt(lengthSquare);

	//����Ǽ�ͷ�ƶ���������////////// ��
	////////////////////////////////  ��
	cocos2d::Vec2 standardAttackRange(JieQSkillRange, 0);
	float standardLength = standardAttackRange.x;


	if (length >= standardLength)
	{
		this->removeFromParent();
	}

	//δ�����ײ���
}