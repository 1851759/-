#include "JieHero.h"
#include "cocos2d.h"
#include "GameScene.h"
JieHero* JieHero::create()
{
	JieHero* jie = new JieHero();
	if (jie->init())
	{
		jie->autorelease();

		//���±߳�ʼ���ٵ�����ֵ////////////////////////////////////////////
		jie->setHeroName('J');
		//�����ƶ��ٶ�
		jie->changeMoveSpeed(JieMoveSpeed * cocos2d::Vec2(1.0, 0).x);

		//���������ٶȣ�ÿ�빥�����ٴ�
		jie->changeAttackSpeed(JieAttackSpeed);
		jie->setAttackWaitTime(0);
		jie->setNormalAttackAfterShake(JieNormalAttackAfterShake);
		jie->setHeroInSkake(false);

		//��������ֵ
		jie->setHealthPoint(JieHealth);
		jie->changeMaxHealthPoint(JieHealth);
		//����������
		jie->changeAttackPoint(JieAttack);
		//����������
		jie->changeDefensePoint(JieDefence);
		//�����ȼ�
		jie->levelUp();
		//�������
		jie->setMoney(0);
		//��������ֵ
		jie->setExpPoint(0);
		//q����
		jie->qSkillLevelUp();//�˴�Ĭ�ϼ���һ�����ڲ���////////////////////////////////////
		jie->setQSkillCdTime(JieQSkillCD);
		jie->setBuff(false);
		jie->setQSkillAfterShake(JieQSkillAfterShake);

		//w����
		jie->wSkillLevelUp();
		jie->setWSkillCdTime(JieWSkillCD);
		jie->setWSkillAfterShake(JieWSkillAfterShake);

		//e����
		jie->eSkillLevelUp();
		jie->setESkillCdTime(JieESkillCD);
		jie->setESkillAfterShake(JieESkillAfterShake);
		jie->setInDisappear(false);
	}
	else
	{
		delete jie;
		jie = NULL;
		return NULL;
	}
	return jie;
}

bool JieHero::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
	if (!Sprite::initWithFile("JieHero.png"))
	{

		return false;
	}
	this->createBlood();
	this->setScale(0.2);
	return true;
}
