//by 王文政 2019年5月27日
//英雄的基类，用来测试移动和技能释放

#ifndef __HERO__
#define __HERO__

#include "cocos2d.h"

//通过枚举类型定义英雄的tag
//英雄的tag
typedef enum
{
	Yase_Tag =101,
	Houyi_Tag = 102,
	Daji_Tag = 103

} HeroName;

//英雄进行各种动作时的tag
typedef enum
{
	HeroMove = 10,
	HeroSkillQ = 11,
	HeroSkillW = 12,
	HeroSkillE = 13,
	HeroNormalAttack = 14
} HeroAction;

//定义英雄的状态 活着或者死了
typedef	enum
	{
	dead = 1,
	alive = 2
	} status;

class Hero : public cocos2d::Sprite
{
	//以下几个值作用是模拟键盘和鼠标同时监听
	bool _isPressingKeyboard;
	char _pressedKey;
	cocos2d::Vec2 _touchPoint;
	cocos2d::Vec2 _heroPoint;

	//在此处添加英雄的属性数值

	//该版本目的为测试移动和技能释放所以暂不定义英雄属性
	//设定英雄的名字
	//后羿的名字为'H'
	//亚瑟的名字为'Y'
	//妲己的名字为'D'
	char _heroName;
	int _level;
	float _moveSpeed;

	//用数组模拟装备
	//每个装备有一个枚举值
	//对应的值为0时表示未装备
	//对应的值为1时表示装备该装备
	int equipmentlist[200];

	//设定攻击速度和冷却时间
	//这些值只能因为装备效果改变
	float _eSkillCdTime;
	float _wSkillCdTime;
	float _qSkillCdTime;
	float _attackSpeed;
	
	//设定攻击和技能等待时间
	//这些值不为0时每帧都减小1/60
	//值为0时才可以攻击和发动技能
	float _attackWaitTime;
	float _qSkillWaitTime;
	float _wSkillWaitTime;
	float _eSkillWaitTime;

	//技能等级
	int _qSkillLevel;
	int _wSkillLevel;
	int _eSkillLevel;

	//buff技能的持续时间
	float _buffTime;
	bool _isInBuff;

public:

	//重写SPrite类的init函数
	virtual bool init();
	
	static Hero* create();

	//计算冷却时间的函数
	//通过在游戏场景中调用英雄的scheduleupdate函数
	//来调用英雄的重写后的update函数
	//剩余冷却时间的减少在update函数中实现
	virtual void update(float dt);

	
	//获得和改变攻击速度
	float getAttackSpeed() const{ return _attackSpeed; } 
	void changeAttackSpeed(const float equipmentAttackSpeed) { _attackSpeed += equipmentAttackSpeed; }

	//获得和改变技能冷却
	float getESkillCdTime() { return _eSkillCdTime; }
	void setESkillCdTime(float cdtime) { _eSkillCdTime = cdtime; }

	float getWSkillCdTime() { return _wSkillCdTime; }
	void setWSkillCdTime(float cdtime) { _wSkillCdTime = cdtime; }

	float getQSkillCdTime() { return _qSkillCdTime; }
	void setQSkillCdTime(float cdtime) { _qSkillCdTime = cdtime; }

	//获得和改变等待时间
	float getAttackWaitTime() { return _attackWaitTime; }
	void cutAttackWaitTime(float waittime) { _attackWaitTime -= waittime; }
	void setAttackWaitTime(float waittime) { _attackWaitTime = waittime; }

	float getQSkillWaitTime() const{ return _qSkillWaitTime; } 
	void cutQSkillWaitTime(float waittime) { _qSkillWaitTime -= waittime; }
	void setQSkillWaitTime(float waittime) { _qSkillWaitTime = waittime; }

	float getWSkillWaitTime() const{ return _wSkillWaitTime; } 
	void cutWSkillWaitTime(float waittime) { _wSkillWaitTime -= waittime; }
	void setWSkillWaitTime(float waittime) { _wSkillWaitTime = waittime; }

	float getESkillWaitTime() const{ return _eSkillWaitTime; } 
	void cutESkillWaitTime(float waittime) { _eSkillWaitTime -= waittime; }
	void setESkillWaitTime(float waittime) { _eSkillWaitTime = waittime; }

	//获得和改变buff持续时间
	float getBuffTime() const{ return _buffTime; } 
	void cutBuffTime(float waittime) { _buffTime -= waittime; }
	void setBuffTime(float lasttime) { _buffTime = lasttime; }
	void setBuff(bool isinbuff) { _isInBuff = isinbuff; }
	bool isInBuff() const{ return _isInBuff; }  

	//获得和改变属性
		
	//给英雄命名和获得英雄名字
	void setHeroName(char name) { _heroName = name; }
	char getHeroName() const{ return _heroName; } 

	//获得和改变等级

	//获得和改变技能等级
	int getQSkillLevel() const{ return _qSkillLevel; } 
	void qSkillLevelUp() { _qSkillLevel++; } 

	int getWSkillLevel() const{ return _wSkillLevel; } 
	void wSkillLevelUp() { _wSkillLevel++; }

	int getESkillLevel() const{ return _eSkillLevel; } 
	void eSkillLevelUp() { _eSkillLevel++; }

	//获得和改变移动速度
	float getMoveSpeed() const{ return _moveSpeed; } 
	void changeMoveSpeed(const float equipmentAttackSpeed) { _moveSpeed += equipmentAttackSpeed; }

	//获得和改变攻击速度

	//获得和改变攻击力

	//获得和改变防御力

	//获得和改变经验值

	//获得和改变金币

	//获得装备
	

	//下列几个函数用于模拟同时监听鼠标和键盘
	//判断是否在按键盘
	//和监听中的技能释放有关
	bool isPressingKeyboard() const{ return _isPressingKeyboard; } 
	void setPressingKeyboard() { _isPressingKeyboard = true; }
	void setUnPressingKeyboard() { _isPressingKeyboard = false; }
	void thisKeyPressed(char key) { _pressedKey = key; }
	char pressThisKey() { return _pressedKey; } 


	void setTouchPoint(cocos2d::Vec2 touchPoint) { _touchPoint = touchPoint; }
	void setHeroPoint(cocos2d::Vec2 heroPoint) { _heroPoint = heroPoint; }
	cocos2d::Vec2 getTouchPoint() { return _touchPoint; }
	cocos2d::Vec2 getHeroPoint() { return _heroPoint; }

};





#endif // !__HERO__

