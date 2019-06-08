//by ������ 2019��5��27��
#include "cocos2d.h"
#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"

USING_NS_CC;

HouyiHero* HouyiHero::create()
{
	HouyiHero* houyi = new HouyiHero();
	if (houyi->init())
	{
		houyi->autorelease();

		//���±߳�ʼ�����������ֵ////////////////////////////////////////////
		houyi->setHeroName('H');
		//�����ƶ��ٶ�
		houyi->changeMoveSpeed(HouyiMoveSpeed * cocos2d::Vec2(1.0,0).x);
		
		//���������ٶȣ�ÿ�빥�����ٴ�
		houyi->changeAttackSpeed(HouyiAttackSpeed);
		houyi->setAttackWaitTime(0);
		houyi->setNormalAttackAfterShake(HouyiNormalAttackAfterShake);
		houyi->setHeroInSkake(false);

		//��������ֵ
		houyi->setHealthPoint(HouyiHealth);
		houyi->changeMaxHealthPoint(HouyiHealth);
		//����������
		houyi->changeAttackPoint(HouyiAttack);
		//����������
		houyi->changeDefensePoint(HouyiDefence);
		//�����ȼ�
		houyi->levelUp();
		//�������
		houyi->setMoney(0);
		//��������ֵ
		houyi->setExpPoint(0);
		//q����
		houyi->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		houyi->setQSkillCdTime(HouyiQSkillCD);
		houyi->setBuff(false);
		houyi->setQSkillAfterShake(HouyiQSkillAfterShake);

		//w����
		houyi->wSkillLevelUp();
		houyi->setWSkillCdTime(HouyiWSkillCD);
		houyi->setWSkillAfterShake(HouyiWSkillAfterShake);

		//e����
		houyi->eSkillLevelUp();
		houyi->setESkillCdTime(HouyiESkillCD);
		houyi->setESkillAfterShake(HouyiESkillAfterShake);
	}
	else
	{
		delete houyi;
		houyi = NULL;
		return NULL;
	}


	return houyi;
}

bool HouyiHero::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
	if (!Sprite::initWithFile("HouyiHero.png"))
	{
		
		return false;
	}
	this->createBlood();
	this->setScale(0.2);
	return true;
}

void HouyiHero::buffUpdate(float dt)
{
	float cuttime = 1.0 / 60.0;
	
	//buff����ʱ��
	if (this->getBuffTime() >= 0.01)
	{
		this->cutBuffTime(cuttime);
		//�ڴ˴�ȡ��buff
		if (this->getBuffTime() <= 0.01)
		{
			//�˴�ΪӦ��ȥ������
			this->changeMoveSpeed(-this->getQSkillLevel() * HouyiQSkillMoveSpeedAdd);
			this->changeAttackSpeed(-this->getQSkillLevel() * HouyiQSkillAttackSpeedAdd);
			this->setNormalAttackAfterShake(1.0 / this->getAttackSpeed());
			this->removeChildByTag(HouyiBuffTag);
		}
	}
	//���buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//�˴�Ϊ��õ�buff����
		this->changeMoveSpeed(this->getQSkillLevel() * HouyiQSkillMoveSpeedAdd);
		this->changeAttackSpeed(this->getQSkillLevel() * HouyiQSkillAttackSpeedAdd);
		this->setNormalAttackAfterShake(1.0 / this->getAttackSpeed());
		Sprite* houyiBuff = Sprite::create("HouyiBuff.png");
		houyiBuff->setPosition(0, 0);
		houyiBuff->setAnchorPoint(cocos2d::Vec2(0,0));
		this->addChild(houyiBuff, 200, HouyiBuffTag);
	}
//	cocos2d::log("attackspeed %f", this->getAttackSpeed());
}

//ʵ��AI
void HouyiHero::AIcontrol(Hero* hero)
{
	/*
	this->setHeroPoint(this->getPosition());
	this->setOtherHeroPoint(hero->getPosition());
	*/
	this->setOtherHero(hero);
	this->schedule(schedule_selector(HouyiHero::AIAction),1.0/60.0f);
}
	
void HouyiHero::AIAction(float dt)
{
//	cocos2d::log("%f  %f\n",this->getOtherHero()->getPosition().x, this->getOtherHero()->getPosition().y);
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//�ƶ�AI
	if (this->getHeroAfterShake() <= 0.01)
	{
		cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
		float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		cocos2d::Vec2 standardDistance = distance / length;
		//AI���������80����
		if (length >= 80.0)
		{
			this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
		//	cocos2d::log(" speed %f", this->getMoveSpeed());
		}
	}
}
