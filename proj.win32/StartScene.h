#ifndef __START_SCENE_H__
#define __START_SCENE_H__


#include "cocos2d.h"







class StartScene :public cocos2d::Scene
{

	


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuBackCallback(cocos2d::Ref* pSender);
	void menuStarttestCallback(cocos2d::Ref* pSender);





	CREATE_FUNC(StartScene);
};




#endif
