#include "cocos2d.h"
#include "GameScene.h"
#include "YuanchengSoldier.h"
#include "YuanchengNormalAttack.h"


YuanchengSoldier* YuanchengSoldier::create(PlayerFlag flag)
{
	YuanchengSoldier* yuancheng = new YuanchengSoldier();
	//定义soldier的flag
	yuancheng->setSoldierFlag(flag);
	if (yuancheng->init())
	{
		yuancheng->autorelease();

		//在下边初始化远程小兵的属性值////////////////////////////////////////////
		yuancheng->setHeroName('Y');
		//基础移动速度
		yuancheng->changeMoveSpeed(YuanchengMoveSpeed * cocos2d::Vec2(1.0, 0).x);
		//基础攻击速度，每秒攻击多少次
		yuancheng->changeAttackSpeed(YuanchengAttackSpeed);
		yuancheng->setAttackWaitTime(0);
		yuancheng->setNormalAttackAfterShake(YuanchengNormalAttackAfterShake);
		yuancheng->setHeroInSkake(false);
		yuancheng->setHealthPoint(YuanchengMaxHealthPoint);
		//基础攻击力
		yuancheng->changeAttackPoint(YuanchengAttack);
		//基础防御力
		//cocos2d::log("%f,%f,%f", yuancheng->getAttackSpeed(), yuancheng->getHealthPoint(), yuancheng->getAttackPoint());
	}
	else
	{
		delete yuancheng;
		yuancheng = NULL;
		return NULL;
	}
	return yuancheng;
}

bool YuanchengSoldier::init()
{
	//下边的if里搞出了英雄的图片
//	cocos2d::log("create soldier");
	if (this->getSoldierFlag() == Player1 && Sprite::initWithFile("YuanchengLan.png"))
	{
		auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		this->setPhysicsBody(body);
		this->setScale(0.2);
		return true;
	}

	if (this->getSoldierFlag() == Player2 && Sprite::initWithFile("YuanchengHong.png"))
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

void YuanchengSoldier::update(float dt)
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
void YuanchengSoldier::AIcontrol(Hero* hero)
{
	this->setOtherHero(hero);
	this->schedule(schedule_selector(YuanchengSoldier::AIAction), 1.0 / 20.0);
}

void YuanchengSoldier::AIAction(float dt)
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
	if (length <= YuanchengNormalAttackRange && this->getHeroAfterShake() <= 0.01)
	{
		//cocos2d::log("asdad");
		if (this->getTag() == MeYuanchengSoldierTag)
		{
			takeNormalAttack(this, true, this->getHeroPoint(), this->getOtherHeroPoint());

		}
		else //if (this->getTag() == OtherYuanchengSoldierTag)
		{
			takeNormalAttack(this, false, this->getHeroPoint(), this->getOtherHeroPoint());
		}
		this->setAttackWaitTime(1.0 / this->getAttackSpeed());
		this->setHeroAfterShake(this->getNormalAttackAfterShake());
	}



}
//释放普攻
void YuanchengSoldier::takeNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint)
{

	YuanchengNormalAttack* yuanchengNormalAttack = YuanchengNormalAttack::createTheAttack(hero);
	auto body = cocos2d::PhysicsBody::createBox(yuanchengNormalAttack->getContentSize());
	yuanchengNormalAttack->setPhysicsBody(body);

	if (isMe)
	{
		this->getScene()->addChild(yuanchengNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->getScene()->addChild(yuanchengNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yuanchengNormalAttack->takeYuanchengNormalAttack(startPoint, targetPoint);
}