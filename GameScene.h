#pragma once
//������Ϸ����
//by ������ 2019��5��24��

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"


class GameScene :public cocos2d::Scene
{

public:
	static cocos2d::Scene* createScene();
	virtual bool GameScene::init();

	//���س�ʼ����
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



	//���������ͼ��̼�������onEnter������ͨ���˱��ʽ����
};

#endif __GAMESCENE__
