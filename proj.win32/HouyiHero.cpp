//by ������ 2019��5��27��
#include "cocos2d.h"
#include "Hero.h"
#include "HouyiHero.h"
#include "HouyiNormalAttack.h"

HouyiHero* HouyiHero::create()
{
	HouyiHero* houyi = new HouyiHero();
	if (houyi->init())
	{
		
		houyi->autorelease();

		//���±߳�ʼ�����������ֵ////////////////////////////////////////////
		houyi->setHeroName('H');
		//�����ƶ��ٶ�
		houyi->changeMoveSpeed(60);
		
		//���������ٶȣ�ÿ�빥�����ٴ�
		houyi->changeAttackSpeed(0.5);
		houyi->setAttackWaitTime(0);

		//q����
		houyi->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		houyi->setQSkillCdTime(10);
		houyi->setBuff(false);

		//w����
		houyi->wSkillLevelUp();
		houyi->setWSkillCdTime(5);

		//e����
		houyi->eSkillLevelUp();
		houyi->setESkillCdTime(2);
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
			this->changeMoveSpeed(-this->getQSkillLevel() * 200);
			this->changeAttackSpeed(-this->getQSkillLevel() * 20);
		}
	}
	//���buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//�˴�Ϊ��õ�buff����
		this->changeMoveSpeed(this->getQSkillLevel() * 200);
		this->changeAttackSpeed(this->getQSkillLevel() * 20);
	}
}






