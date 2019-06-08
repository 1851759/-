#include "cocos2d.h"
#include "CrystalTower.h"
#include "GameScene.h"

CrystalTower* CrystalTower::create(PlayerFlag flag)
{
	CrystalTower* crystal = new CrystalTower();
	crystal->setTowerFlag(flag);
	if (crystal->init())
	{

		crystal->autorelease();

		//���±߳�ʼ��������������ֵ////////////////////////////////////////////
		crystal->setHeroName('C');


		//����ֵ
		crystal->setHealthPoint(CrystalHealthPoint);

		//����������

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
	//�±ߵ�if������Ӣ�۵�ͼƬ
		if (this->getTowerFlag() == Player1 && Sprite::initWithFile("crystal.png"))
		{
			auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2);
			body->setContactTestBitmask(MEUNITTEST);
			body->setCategoryBitmask(MEUNITCATEGORY);
			body->setCollisionBitmask(MEUNITCOLLISION);
			this->setPhysicsBody(body);
			this->setScale(0.2);
			return true;
		}

	if (this->getTowerFlag() == Player2 && Sprite::initWithFile("crystal.png"))
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

void CrystalTower::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//����������Ϸ����
	if (this->getHealthPoint() <= 0)
	{
		auto sc = HelloWorld::createScene();
		Director::getInstance()->replaceScene(sc);
		
	}
}



	