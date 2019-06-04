//���Դ���һ���㲢��ӵ�gamescene��

#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__
#include "cocos2d.h"

//˫�����
typedef enum
{
	MeFlag = 30,
	OtherFlag = 31
} Player;

class RoomScene : public cocos2d::Scene
{
	char _meHeroName;
	char _otherHeroName;
	int _flag;
	bool _isAI;

public:

	virtual bool init();

	static cocos2d::Scene* createScene();

	//flag���
	//���ڴ����˻�
	void setFlag(int flag) { _flag = flag; }
	int getFlag() { return _flag; }


	void ChooseHero_h(cocos2d::Ref* pSender);
	void menuBackToStart(cocos2d::Ref* pSender);
	void menuReadyCallback(cocos2d::Ref* pSender);

	void setMeHeroName(char name) { _meHeroName = name; }
	char getMeHeroName() { return _meHeroName; }

	void setOtherHeroName(char name) { _otherHeroName = name; }
	char getOtherHeroName() { return _otherHeroName; }
	void ChooseHero_y(cocos2d::Ref* pSender);
	void ChooseHero_d(cocos2d::Ref* pSender);


	void menuClickToAddAI(cocos2d::Ref* pSender);
	void menuClickToAddMyHero(cocos2d::Ref* pSender);

	void setAI() { _isAI = true; }
	void setHuman() { _isAI = false; }
	bool isAI() const { return _isAI; }

	CREATE_FUNC(RoomScene);
};



#endif // !__ROOM_SCENE_H__

