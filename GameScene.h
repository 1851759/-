//声明游戏场景
//by 王文政 2019年5月24日

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"

#include "Hero.h"
#include "JinzhanSoldier.h"

#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"
#include "HouyiWSkill.h"

#include "YaseHero.h"
#include "YaseNormalAttack.h"

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
#define JinzhanSoldierExp 100
#define YuanchengSoldierExp 100
#define PaocheSoldierExp 100
#define TowerExp 100

//被杀后给对面英雄加的金币
#define HeroMoney 100
#define JinzhanSoldierMoney 100
#define YuanchengSoldierMoney 100
#define PaocheSoldierMoney 100
#define TowerMoney 100

//出兵间隔
#define WulaWulaCD 10.0

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

	int _meMoney;
	int _meExp;
	int _otherMoney;
	int _otherExp;

	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collidable;
	cocos2d::Vec2 position_now;
public:

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
	void takeHouyiNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeHouyiWSkill(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeHouyiESkill(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//亚瑟技能
	void takeYaseNormalAttack(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeYaseWSkill(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeYaseESkill(Hero* hero, bool isMe, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

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

	//返回初始场景
	void menuBackCallback(cocos2d::Ref* pSender);
	//鼠标监听
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//碰撞监听
	bool contactBegin(cocos2d::PhysicsContact& contact);
	virtual void onEnter();
	virtual void onExit();
	static GameScene* create(char meName, char otherName, bool enermyType);
	//	static GameScene* createWithPhysics(char meName, char otherName, bool isAI);
	void shop_xie(cocos2d::Ref *pSender);
	void shop_shoutao(cocos2d::Ref* pSender);
	void shop_changgong(cocos2d::Ref *pSender);
	void shop_kaijia(cocos2d::Ref *pSender);
	void shop_hongshuijing(cocos2d::Ref *pSender);
	void shop_lanshuijing(cocos2d::Ref *pSender);
	virtual void update(float dt);


	bool setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void collision(float dt);

	//鼠标监听器和键盘监听器在onEnter函数中通过λ表达式定义

	//人机控制
	void watchMeAndOther(float dt);

	//出兵函数
	//void wulawula(float dt);


};

#endif