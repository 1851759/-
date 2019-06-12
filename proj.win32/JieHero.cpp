#include "JieHero.h"
#include "cocos2d.h"
#include "GameScene.h"
JieHero* JieHero::create()
{
	JieHero* jie = new JieHero();
	if (jie->init())
	{
		jie->autorelease();

		//在下边初始化劫的属性值////////////////////////////////////////////
		jie->setHeroName('J');
		//基础移动速度
		jie->changeMoveSpeed(JieMoveSpeed * cocos2d::Vec2(1.0, 0).x);

		//基础攻击速度，每秒攻击多少次
		jie->changeAttackSpeed(JieAttackSpeed);
		jie->setAttackWaitTime(0);
		jie->setNormalAttackAfterShake(JieNormalAttackAfterShake);
		jie->setHeroInSkake(false);

		//基础生命值
		jie->setHealthPoint(JieHealth);
		jie->changeMaxHealthPoint(JieHealth);
		//基础攻击力
		jie->changeAttackPoint(JieAttack);
		//基础防御力
		jie->changeDefensePoint(JieDefence);
		//基础等级
		jie->levelUp();
		//基础金币
		jie->setMoney(0);
		//基础经验值
		jie->setExpPoint(0);
		//q技能
		jie->qSkillLevelUp();//此处默认技能一级用于测试////////////////////////////////////
		jie->setQSkillCdTime(JieQSkillCD);
		jie->setBuff(false);
		jie->setQSkillAfterShake(JieQSkillAfterShake);

		//w技能
		jie->wSkillLevelUp();
		jie->setWSkillCdTime(JieWSkillCD);
		jie->setWSkillAfterShake(JieWSkillAfterShake);

		//e技能
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
	//下边的if里搞出了英雄的图片
	if (!Sprite::initWithFile("JieHero.png"))
	{

		return false;
	}
	this->createBlood();
	this->setScale(0.2);
	return true;
}
