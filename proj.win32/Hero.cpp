#include "cocos2d.h"
#include "Hero.h"

//��������Ӣ�۸����
//ע��˴������ֱ�ʾ///////////////////////////////////////////////////////////////////////////////////////////////////
cocos2d::Vec2 Player1Reborn(250, 250);
cocos2d::Vec2 Player2Reborn(1300, 800);

bool Hero::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
	if (!Sprite::initWithFile("qqhero.png"))
	{
		return false;
	}

	return true;
}

Hero* Hero::create()
{
	Hero* sprite = new Hero();
	if (sprite->init())
	{
		sprite->autorelease();

	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
	
	
	return sprite;
}


//��60֡������ȴʱ��
//����colddown����������ȴʱ��
//����������update������
//������ȴʱ����gamescece������������ʵ��


void Hero::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//ƽA��ȴ
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}
	//q������ȴ
	if (this->getQSkillWaitTime() >= 0.01)
	{
		this->cutQSkillWaitTime(cuttime);
	}
	//w������ȴ
	if (this->getWSkillWaitTime() >= 0.01)
	{
		this->cutWSkillWaitTime(cuttime);
	}
	//e������ȴ
	if (this->getESkillWaitTime() >= 0.01)
	{
		this->cutESkillWaitTime(cuttime);
	}
	/*
	//��Ѫ����
	if (this->getHealthPoint() <= this->getMaxHealthPoint())
	{
		this->changeHealthPoint(HpPerSec / 60.0);
	}
	if (this->getMagicPoint() <= this->getMaxMagicPoint())
	{
		this->changeMagicPoint(MpPerSec / 60.0);
	}
	*/
	//ÿ��һ����������
	if (this->getExpPoint() >= ExpPerLevel)
	{
		this->changeExpPoint(-ExpPerLevel);
		this->levelUp();
		this->qSkillLevelUp();
		this->wSkillLevelUp();
		this->eSkillLevelUp();
		this->changeAttackPoint(AtkPerLevel);
		this->changeDefensePoint(DefPerLevel);
		this->changeMaxHealthPoint(HpPerLevel);
		this->setHealthPoint(this->getMaxHealthPoint());
		this->changeMagicPoint(MpPerLevel);
		cocos2d::log("levelUP");
	}

	//Ӣ�ۺ�ҡʱ��
	if (this->getHeroAfterShake() > 0.01)
	{
		this->setHeroInSkake(true);
		this->cutHeroAfterShake(cuttime);
	}
	//�������ֵΪ0 ����
	if (this->getHealthPoint() <= 0)
	{
		this->setHealthPoint(this->getMaxHealthPoint());
		if (this->getFlag() == Player1)
		{
			this->setPosition(Player1Reborn);
		}
		if (this->getFlag() == Player2)
		{
			this->setPosition(Player2Reborn);
		}
	}
	//cocos2d::log("hp %f exp %d money %d", this->getHealthPoint(), this->getExpPoint(), this->showMeTheMoney());
}







