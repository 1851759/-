#include "cocos2d.h"
#include "GameScene.h"
#include "JinzhanSoldier.h"
#include "JinzhanNormalAttack.h"


JinzhanSoldier* JinzhanSoldier::create(SoldierFlag flag)
{
	JinzhanSoldier* jinzhan = new JinzhanSoldier();
	//定义soldier的flag
	jinzhan->setSoldierFlag(flag);
	if (jinzhan->init())
	{
		jinzhan->autorelease();

		//在下边初始化近战小兵的属性值////////////////////////////////////////////
		jinzhan->setHeroName('J');
		//基础移动速度
		jinzhan->changeMoveSpeed(JinzhanMoveSpeed * cocos2d::Vec2(1.0, 0).x);
		//基础攻击速度，每秒攻击多少次
		jinzhan->changeAttackSpeed(JinzhanAttackSpeed);
		jinzhan->setAttackWaitTime(0);
		jinzhan->setNormalAttackAfterShake(JinzhanNormalAttackAfterShake);
		jinzhan->setHeroInSkake(false);
		jinzhan->setHealthPoint(JinzhanMaxHealthPoint);
		//基础攻击力
		jinzhan->changeAttackPoint(JinzhanAttack);
		//基础防御力
		cocos2d::log("%f,%f,%f", jinzhan->getAttackSpeed(), jinzhan->getHealthPoint(), jinzhan->getAttackPoint());
	}
	else
	{
		delete jinzhan;
		jinzhan = NULL;
		return NULL;
	}
	return jinzhan;
}

bool JinzhanSoldier::init()
{
	//下边的if里搞出了英雄的图片
//	cocos2d::log("create soldier");
	if (this->getSoldierFlag() == MeSoldier && Sprite::initWithFile("HouyiHero.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		this->setPhysicsBody(body);
		this->setScale(0.5);
		return true;
	}
	
	if (this->getSoldierFlag() == OtherSoldier && Sprite::initWithFile("YaseHero.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(OTHERUNITTEST);
		body->setCategoryBitmask(OTHERUNITCATEGORY);
		body->setCollisionBitmask(OTHERUNITCOLLISION);
		this->setPhysicsBody(body);
		this->setScale(0.5);
		return true;
	}
	return false;
}

void JinzhanSoldier::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//平A冷却
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}

	//小兵后摇时间
	if (this->getHeroAfterShake() > 0, 01)
	{
		this->setHeroInSkake(true);
		this->cutHeroAfterShake(cuttime);
	}
	//小兵死亡则消失
	if (this->getHealthPoint() <= 0)
	{
		this->removeFromParent();
	}
}

//实现AI
void JinzhanSoldier::AIcontrol(Hero* hero)
{
	this->setOtherHero(hero);
	this->schedule(schedule_selector(JinzhanSoldier::AIAction), 1.0 / 60.0f);
}

void JinzhanSoldier::AIAction(float dt)
{
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//移动AI
	cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
	float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	cocos2d::Vec2 standardDistance = distance / length;
	//AI后羿离玩家80以上
	if (length >= 80)
	{
		this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
	}
	if (length <= JinzhanNormalAttackRange && this->getHeroAfterShake()<=0.01)
	{
		//cocos2d::log("asdad");
		if (this->getTag() == MeJinzhanSoldierTag)
		{
			takeNormalAttack(this, true, this->getHeroPoint(), this->getOtherHeroPoint());
			
		}
		else //if (this->getTag() == OtherJinzhanSoldierTag)
		{
			takeNormalAttack(this, false, this->getHeroPoint(), this->getOtherHeroPoint());
		}
		this->setAttackWaitTime(1.0/this->getAttackSpeed());
		this->setHeroAfterShake(this->getNormalAttackAfterShake());
	}



}
//释放普攻
void JinzhanSoldier::takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{

	JinzhanNormalAttack* jinzhanNormalAttack = JinzhanNormalAttack::createTheAttack(hero);
	auto body = cocos2d::PhysicsBody::createBox(jinzhanNormalAttack->getContentSize());
	jinzhanNormalAttack->setPhysicsBody(body);

	if (isMe)
	{
		this->getScene()->addChild(jinzhanNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->getScene()->addChild(jinzhanNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	jinzhanNormalAttack->takeJinzhanNormalAttack(startPoint, targetPoint);
}








