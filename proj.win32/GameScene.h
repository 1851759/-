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

	static cocos2d::Scene* createScene(char meHero,char otherHero);
	virtual bool init();

	//���س�ʼ����
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

	//���������ͼ��̼�������onEnter������ͨ���˱��ʽ����
};

#endif