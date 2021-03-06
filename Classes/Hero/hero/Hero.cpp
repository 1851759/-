#include "cocos2d.h"
#include "Hero.h"
#include"client.h"
#include"HouyiHero.h"
#include"DajiHero.h"
#include"YaseHero.h"
#include"JieHero.h"
USING_NS_CC;
//定义两方英雄复活点
//注意此处用数字表示///////////////////////////////////////////////////////////////////////////////////////////////////
cocos2d::Vec2 Player1Reborn(650, 350);
cocos2d::Vec2 Player2Reborn(1050, 650);

int n_RedDeath = 0, n_BlueDeath = 0, i;
char ZhanjiSengding[SIZE] = "Z";
string zhanji;
bool Hero::init()
{
	//下边的if里搞出了英雄的图片
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


//以60帧计算冷却时间
//调用colddown函数减少冷却时间
//具体内容在update函数中
//重置冷却时间在gamescece函数监听部分实现


void Hero::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//平A冷却
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}
	//q技能冷却
	if (this->getQSkillWaitTime() >= 0.01)
	{
		this->cutQSkillWaitTime(cuttime);
	}
	//w技能冷却
	if (this->getWSkillWaitTime() >= 0.01)
	{
		this->cutWSkillWaitTime(cuttime);
	}
	//e技能冷却
	if (this->getESkillWaitTime() >= 0.01)
	{
		this->cutESkillWaitTime(cuttime);
	}
	/*
	//回血回蓝
	if (this->getHealthPoint() <= this->getMaxHealthPoint())
	{
		this->changeHealthPoint(HpPerSec / 60.0);
	}
	if (this->getMagicPoint() <= this->getMaxMagicPoint())
	{
		this->changeMagicPoint(MpPerSec / 60.0);
	}
	*/
	//每升一级增加属性
	if (this->getExpPoint() >= ExpPerLevel)
	{
		this->changeExpPoint(-ExpPerLevel);
		this->levelUp();
		//this->qSkillLevelUp();
		//this->wSkillLevelUp();
		//this->eSkillLevelUp();
		//this->changeAttackPoint(AtkPerLevel);
		//this->changeDefensePoint(DefPerLevel);
		//this->changeMaxHealthPoint(HpPerLevel);
		//this->setHealthPoint(this->getMaxHealthPoint());
		//this->changeMagicPoint(MpPerLevel);
		cocos2d::log("levelUP");
	}

	this->setQSkillLevel(this->getLevel());
	this->setWSkillLevel(this->getLevel());
	this->setESkillLevel(this->getLevel());
	
	if (this->getHeroName() == 'H')
	{
		this->setAttackPoint(HouyiAttack+AtkPerLevel*(this->getLevel()-1));
		this->setDefencePoint(HouyiDefence + DefPerLevel * (this->getLevel()-1));
		this->setMaxHealthPoint(HoyyiMaxHealth + DefPerLevel * (this->getLevel()-1));
	}
	if (this->getHeroName() == 'Y')
	{
		this->setAttackPoint(YaseAttack + AtkPerLevel * (this->getLevel()-1));
		this->setDefencePoint(YaseDefence + DefPerLevel * (this->getLevel()-1));
		this->setMaxHealthPoint(YaseMaxHealth + DefPerLevel * (this->getLevel()-1));
	}
	if (this->getHeroName() == 'D')
	{
		this->setAttackPoint(DajiAttack + AtkPerLevel * (this->getLevel()-1));
		this->setDefencePoint(DajiDefence + DefPerLevel * (this->getLevel()-1));
		this->setMaxHealthPoint(DajiMaxHealth + DefPerLevel * (this->getLevel()-1));
	}

	if (this->getHeroName() == 'J')
	{
		this->setAttackPoint(JieAttack + AtkPerLevel * (this->getLevel() - 1));
		this->setDefencePoint(JieDefence + DefPerLevel * (this->getLevel() - 1));
		this->setMaxHealthPoint(JieMaxHealth + DefPerLevel * (this->getLevel() - 1));
	}
	//英雄后摇时间
	if (this->getHeroAfterShake() > 0.01)
	{
		this->setHeroInSkake(true);
		this->cutHeroAfterShake(cuttime);
	}
	//如果生命值为0 复活
	if (this->getHealthPoint() <= 0)
	{
		this->setHealthPoint(this->getMaxHealthPoint());
		if (this->getFlag() == Player1)
		{
			
			if (ID == 1)
			{
				n_RedDeath++;
				ZhanjiSengding[1] = 'R';
				ZhanjiSengding[2] = n_RedDeath;
				ZhanjiSengding[3] = '/';
				Cli.MessageSending(ZhanjiSengding);
			}
			this->setPosition(Player1Reborn);
		}
		if (this->getFlag() == Player2)
		{
			
			if (ID == 1)
			{
				n_BlueDeath++;
				ZhanjiSengding[1] = 'B';
				ZhanjiSengding[2] = n_BlueDeath;
				ZhanjiSengding[3] = '/';
				Cli.MessageSending(ZhanjiSengding);
			}
			this->setPosition(Player2Reborn);
		}
	}
	/*cocos2d::log("hp %f exp %d money %d", this->getHealthPoint(), this->getExpPoint(), this->showMeTheMoney());*/
}

void Hero::createBlood()
{
	Sprite* bar = Sprite::create("Bar.png");
	bar->setPosition(0, 100);
	this->addChild(bar, 200);
	Sprite* blood = Sprite::create("Blood.png");
	ProgressTimer* pro = ProgressTimer::create(blood);
	pro->setType(ProgressTimer::Type::BAR);
	pro->setPosition(0, 100);
	pro->setMidpoint(Vec2(0, 0.5));
	pro->setBarChangeRate(Vec2(1, 0));
	pro->setTag(bloodbar);
	this->addChild(pro, 200);
	this->schedule(schedule_selector(Hero::checkBlood), 1.0 / 10.0);
}

void Hero::checkBlood(float dt)
{
	auto pro = (ProgressTimer*)this->getChildByTag(bloodbar);
	log("HP %f", this->getHealthPoint());
	pro->setPercentage(this->getHealthPoint() / this->getMaxHealthPoint()*100.0);
}



void Hero::createLevel()
{
	auto level = LabelTTF::create("1", "Arial", 45);
	level->setPosition(-350, 100);
	this->addChild(level, 200, 9888);
	this->schedule(schedule_selector(Hero::checkLevel), 1.0 / 10.0);
}

void Hero::checkLevel(float dt)
{
	this->getChildByTag(9888);
	this->removeChildByTag(9888);
	cocos2d::__String* level = cocos2d::__String::createWithFormat("%d", this->getLevel());
	auto level2 = LabelTTF::create(level->getCString(), "Arial", 45);
	level2->setPosition(-350, 100);
	this->addChild(level2, 200, 9888);
}