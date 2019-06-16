#include "cocos2d.h"
#include "DefenceTower.h"
#include "GameScene.h"
#include "DefenceNormalAttack.h"


DefenceTower* DefenceTower::create(PlayerFlag flag)
{
	DefenceTower* defence = new DefenceTower();
	defence->setTowerFlag(flag);
	if (defence->init())
	{

		defence->autorelease();

		//在下边初始化防御塔的属性值////////////////////////////////////////////
		defence->setHeroName('T');

		//基础攻击速度，每秒攻击多少次
		defence->changeAttackSpeed(DefenceAttackSpeed);
		defence->setAttackWaitTime(0);
		defence->setHealthPoint(3000);
		defence->changeMaxHealthPoint(3000);
		//基础攻击力
		defence->changeAttackPoint(DefenceAttack);
		//基础防御力

	}
	else
	{
		delete defence;
		defence = NULL;
		return NULL;
	}


	return defence;
}

bool DefenceTower::init()
{
	if (this->getTowerFlag() == Player1 && Sprite::initWithFile("Tower.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		body->setMass(99999);
		this->setPhysicsBody(body);
		this->setScale(0.5);
		this->createBlood();

		return true;
	}

	if (this->getTowerFlag() == Player2 && Sprite::initWithFile("Tower.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(OTHERUNITTEST);
		body->setCategoryBitmask(OTHERUNITCATEGORY);
		body->setCollisionBitmask(OTHERUNITCOLLISION);
		body->setMass(99999);
		this->setPhysicsBody(body);
		this->setScale(0.5);
		this->createBlood();

		return true;
	}
	return false;
}

void DefenceTower::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//平A冷却
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}
	//塔死亡则消失
	if (this->getHealthPoint() <= 0)
	{
		this->removeFromParent();
	}
}


//实现AI
void DefenceTower::AIcontrol(Hero* hero)
{
	this->setOtherHero(hero);
	this->schedule(schedule_selector(DefenceTower::AIAction), 1.0 / 60.0f);
}

void DefenceTower::AIAction(float dt)
{
	//	cocos2d::log("%f  %f\n",this->getOtherHero()->getPosition().x, this->getOtherHero()->getPosition().y);
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());
	cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
	float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	cocos2d::Vec2 standardDistance = distance / length;
	if (length <= DefenceNormalAttackRange && this->getAttackWaitTime() <= 0.01)
	{
		//cocos2d::log("asdad");
		if (this->getTag() == MeTowerTag)
		{
			takeNormalAttack(this, true, this->getHeroPoint(), this->getOtherHeroPoint());

		}
		else //if (this->getTag() == OtherJinzhanSoldierTag)
		{
			takeNormalAttack(this, false, this->getHeroPoint(), this->getOtherHeroPoint());
		}
		this->setAttackWaitTime(1.0 / this->getAttackSpeed());
	}




}
//释放普攻
void DefenceTower::takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{

	DefenceNormalAttack* defenceNormalAttack = DefenceNormalAttack::createTheAttack(hero);
	auto body = cocos2d::PhysicsBody::createBox(defenceNormalAttack->getContentSize());
	defenceNormalAttack->setPhysicsBody(body);

	if (isMe)
	{
		this->getScene()->addChild(defenceNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->getScene()->addChild(defenceNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	defenceNormalAttack->takeDefenceNormalAttack(startPoint, targetPoint);
}