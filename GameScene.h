#pragma once
//声明游戏场景
//by 王文政 2019年5月24日

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"


class GameScene :public cocos2d::Scene
{

public:
	static cocos2d::Scene* createScene();
	virtual bool GameScene::init();

	//返回初始场景
	void menuBackCallback(cocos2d::Ref* pSender);

	void shop_xie(cocos2d::Ref *pSender);
	void shop_shoutao(cocos2d::Ref* pSender);
	void shop_changgong(cocos2d::Ref *pSender);
	void shop_kaijia(cocos2d::Ref *pSender);
	void shop_hongshuijing(cocos2d::Ref *pSender);
	void shop_lanshuijing(cocos2d::Ref *pSender);
	void Update(float dt);
	CREATE_FUNC(GameScene);
	/*virtual void onEnter();
	virtual void onExit();*/



	//鼠标监听器和键盘监听器在onEnter函数中通过λ表达式定义
};

#endif __GAMESCENE__
