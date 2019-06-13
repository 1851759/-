#include "cocos2d.h"
#include "GameScene.h"
#include "PaocheSoldier.h"
#include "PaocheNormalAttack.h"


PaocheSoldier* PaocheSoldier::create(PlayerFlag flag)
{
	PaocheSoldier* paoche = new PaocheSoldier();
	//����soldier��flag
	paoche->setSoldierFlag(flag);
	if (paoche->init())
	{
		paoche->autorelease();

		//���±߳�ʼ����սС��������ֵ////////////////////////////////////////////
		paoche->setHeroName('P');
		//�����ƶ��ٶ�
		paoche->changeMoveSpeed(PaocheMoveSpeed * cocos2d::Vec2(1.0, 0).x);
		//���������ٶȣ�ÿ�빥�����ٴ�
		paoche->changeAttackSpeed(PaocheAttackSpeed);
		paoche->setAttackWaitTime(0);
		paoche->setNormalAttackAfterShake(PaocheNormalAttackAfterShake);
		paoche->setHeroInSkake(false);
		paoche->setHealthPoint(PaocheMaxHealthPoint);
		//����������
		paoche->changeAttackPoint(PaocheAttack);
		//����������
		//cocos2d::log("%f,%f,%f", paoche->getAttackSpeed(), paoche->getHealthPoint(), paoche->getAttackPoint());
	}
	else
	{
		delete paoche;
		paoche = NULL;
		return NULL;
	}
	return paoche;
}

bool PaocheSoldier::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
//	cocos2d::log("create soldier");
	if (this->getSoldierFlag() == Player1 && Sprite::initWithFile("PaocheLan.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		this->setPhysicsBody(body);
		this->setScale(0.2);
		return true;
	}

	if (this->getSoldierFlag() == Player2 && Sprite::initWithFile("PaocheHong.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(OTHERUNITTEST);
		body->setCategoryBitmask(OTHERUNITCATEGORY);
		body->setCollisionBitmask(OTHERUNITCOLLISION);
		this->setPhysicsBody(body);
		this->setScale(0.2);
		return true;
	}
	return false;
}

void PaocheSoldier::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//ƽA��ȴ
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}

	//С����ҡʱ��
	if (this->getHeroAfterShake() > 0, 01)
	{
		this->setHeroInSkake(true);
		this->cutHeroAfterShake(cuttime);
	}
	//С����������ʧ
	if (this->getHealthPoint() <= 0)
	{
		this->removeFromParent();
	}
}

//ʵ��AI
void PaocheSoldier::AIcontrol(Hero* hero)
{
	this->setOtherHero(hero);
	this->schedule(schedule_selector(PaocheSoldier::AIAction), 1.0 / 20.0);
}

void PaocheSoldier::AIAction(float dt)
{
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//�ƶ�AI
	cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
	float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	cocos2d::Vec2 standardDistance = distance / length;
	//AI���������80����
	if (length >= 80)
	{
		this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
	}
	if (length <= PaocheNormalAttackRange && this->getHeroAfterShake() <= 0.01)
	{
		//cocos2d::log("asdad");
		if (this->getTag() == MePaocheSoldierTag)
		{
			takeNormalAttack(this, true, this->getHeroPoint(), this->getOtherHeroPoint());

		}
		else //if (this->getTag() == OtherPaocheSoldierTag)
		{
			takeNormalAttack(this, false, this->getHeroPoint(), this->getOtherHeroPoint());
		}
		this->setAttackWaitTime(1.0 / this->getAttackSpeed());
		this->setHeroAfterShake(this->getNormalAttackAfterShake());
	}



}
//�ͷ��չ�
void PaocheSoldier::takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{

	PaocheNormalAttack*paocheNormalAttack = PaocheNormalAttack::createTheAttack(hero);
	auto body = cocos2d::PhysicsBody::createBox(paocheNormalAttack->getContentSize());
	paocheNormalAttack->setPhysicsBody(body);

	if (isMe)
	{
		this->getScene()->addChild(paocheNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->getScene()->addChild(paocheNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	paocheNormalAttack->takePaocheNormalAttack(startPoint, targetPoint);
}