#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;
//定义两方英雄复活点
//注意此处用数字表示///////////////////////////////////////////////////////////////////////////////////////////////////
cocos2d::Vec2 Player1Reborn(650, 350);
cocos2d::Vec2 Player2Reborn(1050, 650);

int n_RedDeath = 0, n_BlueDeath = 0;
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
		this->qSkillLevelUp();
		this->wSkillLevelUp();
		this->eSkillLevelUp();
		this->changeAttackPoint(AtkPerLevel);
		this->changeDefensePoint(DefPerLevel);
		this->changeMaxHealthPoint(HpPerLevel);
		//this->setHealthPoint(this->getMaxHealthPoint());
		this->changeMagicPoint(MpPerLevel);
		cocos2d::log("levelUP");
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
			n_RedDeath++;
			this->setPosition(Player1Reborn);
		}
		if (this->getFlag() == Player2)
		{
			n_BlueDeath++;
			this->setPosition(Player2Reborn);
		}
	}
	cocos2d::log("hp %f exp %d money %d", this->getHealthPoint(), this->getExpPoint(), this->showMeTheMoney());
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
	this->schedule(schedule_selector(Hero::checkBlood), 0.01f);
}

void Hero::checkBlood(float dt)
{
	auto pro = (ProgressTimer*)this->getChildByTag(bloodbar);
	log("HP %f", this->getHealthPoint());
	pro->setPercentage(this->getHealthPoint() / this->getMaxHealthPoint()*100.0);
}



