//������Ϸ����
//by ������ 2019��5��24��

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
	//��ȡmeHeroTag
	char getMeHeroTag() { return meHeroTag; } 
	//����gamescene��herotag����roomscece�е���
	void setMeHeroTag(char heroType) { meHeroTag = heroType; }

	//��ȡotherHeroTag
	char getOtherHeroTag() { return otherHeroTag; }
	void setOtherHeroTag(char heroType) { otherHeroTag = heroType; }

	static cocos2d::Scene* createScene();
	virtual bool init();

	//���س�ʼ����
	void menuBackCallback(cocos2d::Ref* pSender);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();

	//���������ͼ��̼�������onEnter������ͨ���˱��ʽ����
};

#endif

