#ifndef __CRYSTALTOWER__
#define __CRYSTALTOWER__
#include "cocos2d.h"
#include "Hero.h"
#include "GameScene.h"
#include "HelloWorldScene.h"

//�ڴ˴�����ˮ����ʼ����

#define CrystalDefence 40.0
#define CrystalHealthPoint 3000

class CrystalTower : public Hero
{
	//�趨��������
	//ˮ����������Ϊ'C'
	char _towerName;
	PlayerFlag _flag;


public:
	void setTowerFlag(PlayerFlag flag) { _flag = flag; }
	int getTowerFlag() const { return _flag; }

	virtual bool init();

	static CrystalTower* create(PlayerFlag flag);

	virtual void update(float dt);

	

};

extern bool over, victory;

#endif // !__CRYSTALTOWER__