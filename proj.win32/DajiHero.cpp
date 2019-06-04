#include "cocos2d.h"
#include "DajiHero.h"
#include "DajiNormalAttack.h"
#include "DajiESkill.h"


DajiHero* DajiHero::create()
{
	DajiHero* daji = new DajiHero();
	if (daji->init())
	{

		daji->autorelease();

		//���±߳�ʼ��槼�������ֵ////////////////////////////////////////////
		daji->setHeroName('D');
		//�����ƶ��ٶ�
		daji->changeMoveSpeed(DajiMoveSpeed * cocos2d::Vec2(1.0, 0).x);

		//���������ٶȣ�ÿ�빥�����ٴ�
		daji->changeAttackSpeed(DajiAttackSpeed);
		daji->setAttackWaitTime(0);
		daji->setNormalAttackAfterShake(DajiNormalAttackAfterShake);
		daji->setHeroInSkake(false);

		//��������ֵ
		daji->setHealthPoint(DajiHealth);
		daji->changeMaxHealthPoint(DajiHealth);
		//����������
		daji->changeAttackPoint(DajiAttack);
        //����������
		daji->changeDefensePoint(DajiDefence);
		//�����ȼ�
		daji->levelUp();
		//�������
		daji->setMoney(0);
		//��������ֵ
		daji->setExpPoint(0);
		//q����
		daji->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		daji->setQSkillCdTime(DajiQSkillCD);
		daji->setQSkillAfterShake(DajiQSkillAfterShake);

		//w����
		daji->wSkillLevelUp();
		daji->setWSkillCdTime(DajiWSkillCD);
		daji->setWSkillAfterShake(DajiWSkillAfterShake);

		//e����
		daji->eSkillLevelUp();
		daji->setESkillCdTime(DajiESkillCD);
		daji->setESkillAfterShake(DajiESkillAfterShake);
	}
	else
	{
		delete daji;
		daji = NULL;
		return NULL;
	}


	return daji;
}

bool DajiHero::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
	if (!Sprite::initWithFile("DajiHero.png"))
	{

		return false;
	}
	this->setScale(0.2);
	return true;
}




//ʵ��AI
void DajiHero::AIcontrol(Hero* hero)
{
	/*
	this->setHeroPoint(this->getPosition());
	this->setOtherHeroPoint(hero->getPosition());
	*/
	this->setOtherHero(hero);
	this->schedule(schedule_selector(DajiHero::AIAction), 1.0 / 60.0f);
}

void DajiHero::AIAction(float dt)
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
		//AI槼������80����
		if (length >= 80.0)
		{
			this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
			//	cocos2d::log(" speed %f", this->getMoveSpeed());
		}
	}





}