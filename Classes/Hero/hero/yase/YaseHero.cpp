//by ������ 2019��5��30��
#include "cocos2d.h"
#include "YaseHero.h"
#include"YaseNormalAttack.h"
#include"YaseESkill.h"
USING_NS_CC;

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
		yase->setNormalAttackAfterShake(YaseNormalAttackAfterShake);
		yase->setHeroInSkake(false);

		//��������ֵ
		yase->setHealthPoint(YaseHealth);
		yase->changeMaxHealthPoint(YaseHealth);
		//����������
		yase->changeAttackPoint(YaseAttack);
		//����������
		yase->changeDefensePoint(YaseDefence);
		//�����ȼ�
		yase->levelUp();
		//�������
		yase->setMoney(0);
		//��������ֵ
		yase->setExpPoint(0);
		//q����
		yase->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		yase->setQSkillCdTime(YaseQSkillCD);
		yase->setBuff(false);

		//w����
		yase->wSkillLevelUp();
		yase->setWSkillCdTime(YaseWSkillCD);
		yase->setWSkillAfterShake(YaseWSkillAfterShake);

		//e����
		yase->eSkillLevelUp();
		yase->setESkillCdTime(YaseESkillCD);
		yase->setESkillAfterShake(YaseESkillAfterShake);

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
	if (!Sprite::initWithFile("yase.png"))
	{
		return false;
	}
	this->setScale(0.3);
	this->createBlood();
	this->createLevel();

	return true;
}

void YaseHero::buffUpdate(float dt)
{
	float cuttime = 1.0 / 20.0;

	//buff����ʱ��
	if (this->getBuffTime() >= 0.01)
	{
		this->cutBuffTime(cuttime);
		//�ڴ�ȡ��buff
		if (this->getBuffTime() <= 0.01)
		{
			this->changeDefensePoint(-this->getQSkillLevel()*YaseQSkillDefenceAdd);
			this->setNormalAttackAfterShake(1.0 / this->getAttackSpeed());
			this->removeChildByTag(YaseBuffTag);
		}
	}
	//���buff
	if (this->isInBuff())
	{
		this->setBuff(false);
		//�˴�Ϊ��õ�buff����
		this->changeDefensePoint(this->getQSkillLevel()*YaseQSkillDefenceAdd);
		this->setNormalAttackAfterShake(1.0 / this->getAttackSpeed());
		Sprite* yaseBuff = Sprite::create("yaseBuff.png");
		yaseBuff->setPosition(0, 0);
		yaseBuff->setAnchorPoint(cocos2d::Vec2(0, 0));
		this->addChild(yaseBuff, 200, YaseBuffTag);
	}
}

//ʵ��AI
void YaseHero::AIcontrol(Hero* hero)
{
	this->setOtherHero(hero);
	this->schedule(schedule_selector(YaseHero::AIAction), 1.0 / 20.0);
}

void YaseHero::AIAction(float dt)
{
	this->setOtherHeroPoint(this->getOtherHero()->getPosition());
	this->setHeroPoint(this->getPosition());

	//�ƶ�AI
	if (this->getHeroAfterShake() <= 0.01)
	{
		cocos2d::Vec2 distance = this->getOtherHeroPoint() - this->getHeroPoint();
		float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		cocos2d::Vec2 standardDistance = distance / length;
		//AI��ɪ�����20����
		if (length >= YaseNormalAttackRange-10)
		{
			this->setPosition(this->getPosition() + this->getMoveSpeed() / 60 * standardDistance);
		}
	}
}
