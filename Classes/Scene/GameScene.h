//声明游戏场景
//by 王文政 2019年5月24日

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"

#include "Hero.h"
#include "JinzhanSoldier.h"

#include "HouyiHero.h"
#include "YaseHero.h"
#include "DajiHero.h"
#include"JieHero.h"

USING_NS_CC;

//定义碰撞测试掩码
#define MEUNITTEST 0x08
#define MESKILLTEST 0x04
#define OTHERUNITTEST 0x02
#define OTHERSKILLTEST 0x01

//类别掩码
#define MEUNITCATEGORY 0x01
#define MESKILLCATEGORY 0x02
#define OTHERUNITCATEGORY 0x04
#define OTHERSKILLCATEGORY 0x08

//碰撞掩码
#define MEUNITCOLLISION 0x04
#define MESKILLCOLLISION 0x02
#define OTHERUNITCOLLISION 0x01
#define OTHERSKILLCOLLISION 0x08

//被杀后给对面英雄加的经验
#define HeroExp 100
#define JinzhanSoldierExp 40
#define YuanchengSoldierExp 30
#define PaocheSoldierExp 50
#define TowerExp 0

//被杀后给对面英雄加的金币
#define HeroMoney 300
#define JinzhanSoldierMoney 50
#define YuanchengSoldierMoney 40
#define PaocheSoldierMoney 100
#define TowerMoney 300

//出兵间隔
#define WulaWulaCD 30.0

typedef enum
{
	MeHeroTag = 1111,
	AIHeroTag = 1112,
	OtherHeroTag = 1113
} PlayerType;

typedef enum
{
	MeSkillTag = 1114,
	OtherSkillTag = 1115,
} SkillTag;

typedef enum
{
	MeJinzhanSoldierTag = 1116,
	OtherJinzhanSoldierTag = 1117,
	MeYuanchengSoldierTag = 1118,
	OtherYuanchengSoldierTag = 1119,
	MePaocheSoldierTag = 1120,
	OtherPaocheSoldierTag = 1121,
	MeTowerTag = 1122,
	OtherTowerTag = 1123,
	MeCrystalTag = 1124,
	OtherCrystalTag = 1125
} UnitType;
class GameScene :public cocos2d::Layer
{
	char meHeroTag;
	char otherHeroTag;
	int _enermyType;
	int _meFlag;

	int _meMoney, _meMoney_moment;
	int _meExp;
	int _otherMoney;
	int _otherExp;
	bool _ischecking = false;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collidable;
	cocos2d::Vec2 position_now;
	cocos2d::Vec2 position_now_me, position_now_other;
	int RedScore = 9999, BlueScore = 9998;                 //Tag
	int moneytag = 8888, Expbar = 1234;
	int equ_num_me = 0, equ_num_enemy;

public:
	//经验
	void checkExp(float dt);

	void setMeFlag(int flag) { _meFlag = flag; }
	int getMeFlag() const { return _meFlag; }
	//获取敌我金币和经验
	int getMeMoney() const { return _meMoney; }
	void changeMeMoney(int money) { _meMoney += money; }
	int getMeExp() const { return _meExp; }
	void changeMeExp(int exp) { _meExp += exp; }

	int getOtherMoney() const { return _otherMoney; }
	void changeOtherMoney(int money) { _otherMoney += money; }
	int getOtherExp() const { return _otherExp; }
	void changeOtherExp(int exp) { _otherExp += exp; }

	//英雄操控函数
	void heroMove(Hero* target);
	//后羿技能
	void takeHouyiNormalAttack(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeHouyiWSkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeHouyiESkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//亚瑟技能
	void takeYaseNormalAttack(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeYaseWSkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeYaseESkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//妲己技能
	void takeDajiNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeDajiQSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeDajiWSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeDajiESkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);

	//劫技能
	void takeJieNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeJieQSkill(JieHero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeJieWSkill(JieHero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void jieWShadow(float dt);
	void takeJieESkill(JieHero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void jieEShadow(float dt);
	void jieEappear(float dt);
	void jieEDamage(float dt);

	//获取meHeroTag
	char getMeHeroTag() { return meHeroTag; }
	//设置gamescene的herotag，在roomscece中调用
	void setMeHeroTag(char heroType) { meHeroTag = heroType; }

	//获取otherHeroTag
	char getOtherHeroTag() { return otherHeroTag; }
	void setOtherHeroTag(char heroType) { otherHeroTag = heroType; }

	//获取和设定敌方类型为ai或玩家
	int getEnermyType() const { return _enermyType; }
	void setEnermyType(int type) { _enermyType = type; }

	static cocos2d::Scene* createScene(char meHero, char otherHero, bool isAI);
	virtual bool init();

	//鼠标监听
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//键盘监听
	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//碰撞监听
	bool contactBegin(cocos2d::PhysicsContact& contact);
	virtual void onEnter();
	virtual void onExit();
	static GameScene* create(char meName, char otherName, bool enermyType);
	//	static GameScene* createWithPhysics(char meName, char otherName, bool isAI);
	void shop_xie(cocos2d::Ref *pSender);
	void shop_duanjian(cocos2d::Ref* pSender);
	void shop_changjian(cocos2d::Ref *pSender);
	void shop_kaijia(cocos2d::Ref *pSender);
	void shop_hongshuijing(cocos2d::Ref *pSender);
	virtual void update(float dt);


	bool setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void collision(float dt);

	//鼠标监听器和键盘监听器在onEnter函数中通过λ表达式定义

	//人机控制
	void watchMeAndOther(float dt);

	//出兵函数
	void jinzhanWulawula(float dt);
	void yuanchengWulawula(float dt);
	void paocheWulawula(float dt);

	//装备面板
	void equipmentCheck();
	bool isChecking() const { return _ischecking; }
	void setChecking() { _ischecking = true; }
	void setUnChecking() { _ischecking = false; }

	//发送位置信息
	void SendPosition(float dt);

	//接收对方英雄位置并进行移动
	void GetAndMove(float dt);

	//金钱随时间增加
	void MakeMoney(float dt);

	//攻击与技能释放
	//void Attacking(float dt);

	//敌方装备更新
	void EnemyEquipUpdate(float dt);

	//判断战绩
	void Zhanji(float dt);

};

#endif