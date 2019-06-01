//by ������ 2019��5��27��
#include "cocos2d.h"
#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"


HouyiHero* HouyiHero::create()
{
	HouyiHero* houyi = new HouyiHero();
	if (houyi->init())
	{
		
		houyi->autorelease();

		//���±߳�ʼ�����������ֵ////////////////////////////////////////////
		houyi->setHeroName('H');
		//�����ƶ��ٶ�
		houyi->changeMoveSpeed(HouyiMoveSpeed);
		
		//���������ٶȣ�ÿ�빥�����ٴ�
		houyi->changeAttackSpeed(HouyiAttackSpeed);
		houyi->setAttackWaitTime(0);

		//����������

		//����������

		//�����ȼ�

		//�������

		//��������ֵ

		//q����
		houyi->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		houyi->setQSkillCdTime(HouyiQSkillCD);
		houyi->setBuff(false);

		//w����
		houyi->wSkillLevelUp();
		houyi->setWSkillCdTime(HouyiWSkillCD);

		//e����
		houyi->eSkillLevelUp();
		houyi->setESkillCdTime(HouyiESkillCD);
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
	this->setScale(0.5);
	return true;
}





void HouyiHero::update(float dt)
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
		}
	}
	//���buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//�˴�Ϊ��õ�buff����
		this->changeMoveSpeed(this->getQSkillLevel() * HouyiQSkillMoveSpeedAdd);
		this->changeAttackSpeed(this->getQSkillLevel() * HouyiQSkillAttackSpeedAdd);
	}

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
	cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
	float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	cocos2d::Vec2 standardDistance = distance / length;
	this->setPosition(this->getPosition() + standardDistance);
	
	

}





