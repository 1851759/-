//by ������ 2019��5��30��
#include "cocos2d.h"
#include "YaseHero.h"


YaseHero* YaseHero::create()
{
	YaseHero* yase = new YaseHero();
	if (yase->init())
	{

		yase->autorelease();

		//���±߳�ʼ����ɪ������ֵ////////////////////////////////////////////
		yase->setHeroName('Y');
		//�����ƶ��ٶ�
		yase->changeMoveSpeed(YaseMoveSpeed * cocos2d::Vec2(1.0, 0).x);

		//���������ٶȣ�ÿ�빥�����ٴ�
		yase->changeAttackSpeed(YaseAttackSpeed);
		yase->setAttackWaitTime(0);

		//q����
		yase->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		yase->setQSkillCdTime(YaseQSkillCD);
		yase->setBuff(false);

		//w����
		yase->wSkillLevelUp();
		yase->setWSkillCdTime(YaseWSkillCD);

		//e����
		yase->eSkillLevelUp();
		yase->setESkillCdTime(YaseESkillCD);
	}
	else
	{
		delete yase;
		yase = NULL;
		return NULL;
	}


	return yase;
}

bool YaseHero::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
	if (!Sprite::initWithFile("YaseHero.png"))
	{
		return false;
	}

	return true;
}

void YaseHero::update(float dt)
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
			this->changeDefensePoint(-this->getQSkillLevel() * YaseQSkillDefenceAdd);
		}
	}
	//���buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//�˴�Ϊ��õ�buff����
		this->changeDefensePoint(this->getQSkillLevel() * YaseQSkillDefenceAdd);
	}
}