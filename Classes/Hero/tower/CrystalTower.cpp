#include "cocos2d.h"
#include "CrystalTower.h"
#include "GameScene.h"
#include"client.h"
bool over = 0, victory = 0;
CrystalTower* CrystalTower::create(PlayerFlag flag)
{
	CrystalTower* crystal = new CrystalTower();
	crystal->setTowerFlag(flag);
	if (crystal->init())
	{

		crystal->autorelease();

		//在下边初始化防御塔的属性值////////////////////////////////////////////
		crystal->setHeroName('C');


		//生命值
		crystal->setHealthPoint(CrystalHealthPoint);
		crystal->changeMaxHealthPoint(CrystalHealthPoint);
		//基础防御力

	}
	else
	{
		delete crystal;
		crystal = NULL;
		return NULL;
	}


	return crystal;
}

bool CrystalTower::init()
{
	//下边的if里搞出了英雄的图片
	if (this->getTowerFlag() == Player1 && Sprite::initWithFile("crystal.png"))
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

	if (this->getTowerFlag() == Player2 && Sprite::initWithFile("crystal.png"))
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

void CrystalTower::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//塔死亡则游戏结束
	if (this->getHealthPoint() <= 0)
	{
		over = 1;
		Cli.MessageSending("over");
		if (this->getTowerFlag() == Player1)
		{
			if (IfAI)
			{
				victory = 0;
			}
			else
			{
				if (ID == 1)
				{
					victory = 0;
				}
				else
				{
					victory = 1;
				}
			}
		}
		else
		{
			if (IfAI)
			{
				victory = 1;
			}
			else
			{
				if (ID == 1)
				{
					victory = 1;
				}
				else
				{
					victory = 0;
				}
			}
		}
		auto sc = HelloWorld::createScene();
		Director::getInstance()->replaceScene(sc);
	}
}



	