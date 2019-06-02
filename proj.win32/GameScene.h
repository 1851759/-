//声明游戏场景
//by 王文政 2019年5月24日

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"

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
	OtherJinzhanSodierTag = 1117,
	MeYuanchengSoldierTag = 1118,
	OtherYuanchengSoldierTag = 1119,
	MePaocheSoldierTag = 1120,
	OtherPaocheSoldierTag = 1121,
	MeTowerTag = 1122,
	OtherTowerTag = 1123,
	MeCrystalTag = 1124,
	OtherCrystalTag = 1125
} UnitType;
class GameScene :public cocos2d::Scene
{
	char meHeroTag;
	char otherHeroTag;
	int _enermyType;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collidable;
	cocos2d::Vec2 position_now;
public:
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

	static cocos2d::Scene* createScene(char meHero,char otherHero,bool isAI);
	virtual bool init();

	//返回初始场景
	void menuBackCallback(cocos2d::Ref* pSender);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	static GameScene* create(char meName, char otherName, bool enermyType);
	virtual void onEnter();
	virtual void onExit();

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

};

#endif