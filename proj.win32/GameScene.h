//������Ϸ����
//by ������ 2019��5��24��

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"


class GameScene :public cocos2d::Scene
{

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//���س�ʼ����
	void menuBackCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();

	//���������ͼ��̼�������onEnter������ͨ���˱��ʽ����
};

#endif

