//声明游戏场景
//by 王文政 2019年5月24日

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"

typedef enum
{
	HeroTag = 1111,
} lalala;

class GameScene :public cocos2d::Scene
{
	char meHeroTag;
	char otherHeroTag;


public:
	//获取meHeroTag
	char getMeHeroTag() { return meHeroTag; }
	//设置gamescene的herotag，在roomscece中调用
	void setMeHeroTag(char heroType) { meHeroTag = heroType; }

	//获取otherHeroTag
	char getOtherHeroTag() { return otherHeroTag; }
	void setOtherHeroTag(char heroType) { otherHeroTag = heroType; }

	static cocos2d::Scene* createScene(char meHero,char otherHero);
	virtual bool init();

	//返回初始场景
	void menuBackCallback(cocos2d::Ref* pSender);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	static GameScene* create(char meName, char otherName);
	virtual void onEnter();
	virtual void onExit();

	void shop_xie(cocos2d::Ref *pSender);
	void shop_shoutao(cocos2d::Ref* pSender);
	void shop_changgong(cocos2d::Ref *pSender);
	void shop_kaijia(cocos2d::Ref *pSender);
	void shop_hongshuijing(cocos2d::Ref *pSender);
	void shop_lanshuijing(cocos2d::Ref *pSender);
	void Update(float dt);

	//鼠标监听器和键盘监听器在onEnter函数中通过λ表达式定义
};

#endif