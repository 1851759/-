//by 王文政 2019年5月27日
//英雄的基类，用来测试移动和技能释放

#ifndef __HERO__
#define __HERO__

#include "cocos2d.h"
#include "BasicSprite.h"

//通过枚举类型定义英雄的tag
//英雄的tag
typedef enum
{
	Yase_Tag =101,
	Houyi_Tag = 102,
	Daji_Tag = 103

} HeroName;

//英雄进行移动时的tag
typedef enum
{
	HeroMove = 10,
} HeroAction;

//两方玩家的flag 默认人机player2
typedef enum
{
	Player1 = 300,
	Player2 = 301
} PlayerFlag;

typedef enum
{
	bloodbar = 400
} BloodBar;



//所有英雄的通用属性
//每级所需经验
#define ExpPerLevel 200
//每秒回蓝红
#define MpPerSec 1.0
#define HpPerSec 1.0

//每级加属性
#define MpPerLevel 20.0
#define HpPerLevel 20.0
#define AtkPerLevel 20.0
#define DefPerLevel 20.0

class Hero : public BasicSprite
{
	//以下几个值作用是模拟键盘和鼠标同时监听
	bool _isPressingKeyboard;
	char _pressedKey;
	cocos2d::Vec2 _touchPoint;
	cocos2d::Vec2 _heroPoint;

	//pve,pvp相关
	bool _isAI;
	cocos2d::Vec2 _otherHeroPoint;
	cocos2d::Vec2 _otherTowerPoint;
	cocos2d::Vec2 _otherSoldierPoint;
	int _flag;
	Hero* _otherHero;
	
	//在此处添加英雄的属性数值

	//该版本目的为测试移动和技能释放所以暂不定义英雄属性
	//设定英雄的名字
	//后羿的名字为'H'
	//亚瑟的名字为'Y'
	//妲己的名字为'D'
	char _heroName;
	int _level;
	float _moveSpeed;
	float _atk;
	float _def;
	//血量
	float _healthPoint;
	float _maxHealthPoint;
	//蓝
	float _magicPoint;
	float _maxMagicPoint;
	//经验值
	int _experiencePoint;
	//金币
	int _money;

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

	//普攻和技能后摇时间
	float _attackAfterShake;
	float _qSkillAfterShake;
	float _wSkillAfterShake;
	float _eSkillAfterShake;

	float _heroAfterShake;
	bool _heroInShake;
	
public:
	//血条
	void createBlood();

	void checkBlood(float dt);

	int getFlag() const { return _flag; }
	void setFlag(PlayerFlag flag) { _flag = flag; }

	//重写SPrite类的init函数
	virtual bool init();
	
	static Hero* create();

	//计算冷却时间的函数
	//通过在游戏场景中调用英雄的scheduleupdate函数
	//来调用英雄的重写后的update函数
	//剩余冷却时间的减少在update函数中实现
	virtual void update(float dt);

	//设定为人机
	void setAI() { _isAI = true; };
	void setHuman() { _isAI = false; }
	bool isAI() const { return _isAI; }
	//设置该英雄的敌方英雄
	void setOtherHero(Hero* hero) { _otherHero = hero; }
	Hero* getOtherHero() const { return _otherHero; }
	
	//交互相关

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

	//获得和改变技能后摇及后摇相关
	float getNormalAttackAfterShake() const { return _attackAfterShake; }
	void setNormalAttackAfterShake(float shakeTime) { _attackAfterShake = shakeTime; }
	bool isInShake() const { return _heroInShake; }
	void setHeroInSkake(bool isshake) { _heroInShake = isshake; }


	float getQSkillAfterShake() const { return _qSkillAfterShake; }
	void setQSkillAfterShake(float shakeTime) { _qSkillAfterShake = shakeTime; }

	float getWSkillAfterShake() const { return _wSkillAfterShake; }
	void setWSkillAfterShake(float shakeTime) { _wSkillAfterShake = shakeTime; }

	float getESkillAfterShake() const { return _eSkillAfterShake; }
	void setESkillAfterShake(float shakeTime) { _eSkillAfterShake = shakeTime; }

	float getHeroAfterShake() const { return _heroAfterShake; }
	void setHeroAfterShake(float shakeTime) { _heroAfterShake = shakeTime; }
	void cutHeroAfterShake(float cuttime) { _heroAfterShake -= cuttime; }
	//获得和改变属性
		
	//给英雄命名和获得英雄名字
	void setHeroName(char name) { _heroName = name; }
	char getHeroName() const{ return _heroName; } 

	//获得和改变等级
	int getLevel() const { return _level; }
	void levelUp() { _level++; }

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

	//获得和改变攻击力
	float getAttackPoint() const { return _atk; }
	void changeAttackPoint(float point) { _atk += point; }

	//获得和改变防御力
	float getDefensePoint() const { return _def; }
	void changeDefensePoint(float point) { _def += point; }

	//生命值相关
	virtual float getHealthPoint() const { return _healthPoint; }
	float getMaxHealthPoint() const { return _maxHealthPoint; }
	void changeMaxHealthPoint(float point) { _maxHealthPoint += point; }
	void changeHealthPoint(float point) { _healthPoint += point; }
	virtual void setHealthPoint(float point) { _healthPoint = point; }
	virtual void sufferDamage(float damage) { _healthPoint -= damage; }

	//蓝相关
	float getMagicPoint() const { return _magicPoint; }
	float getMaxMagicPoint() const { return _maxMagicPoint; }
	void changeMaxMagicPoint(float point) { _maxMagicPoint += point; }
	void changeMagicPoint(float point) { _magicPoint += point; }
	void cutMagicPoint(float point) { _magicPoint -= point; }

	virtual int getExpPoint() const { return _experiencePoint; }
	virtual void setExpPoint(int point) { _experiencePoint = point; }
	virtual void changeExpPoint(int point) { _experiencePoint += point; }

	virtual int showMeTheMoney() const { return _money; }
	virtual void setMoney(int point) { _money = point; }
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
	cocos2d::Vec2 getTouchPoint() { return _touchPoint; }

	void setHeroPoint(cocos2d::Vec2 heroPoint) { _heroPoint = heroPoint; }
	cocos2d::Vec2 getHeroPoint() { return _heroPoint; }

	//人机控制相关
	void setOtherHeroPoint(cocos2d::Vec2 heroPoint) { _otherHeroPoint = heroPoint; }
	cocos2d::Vec2 getOtherHeroPoint() { return _otherHeroPoint; }

};


extern int n_RedDeath, n_BlueDeath;


#endif // !__HERO__

