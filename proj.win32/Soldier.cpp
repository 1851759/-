#include "Soldier.h"
#include "SimpleAudioEngine.h"
#include"cocos2d.h"

bool Soldier::init()
{
	initWithFile("soldier.png");

	return true;
}

Soldier* Soldier::create()
{
	Soldier* sprite = new Soldier();
	if (sprite->init())
	{
		sprite->autorelease();

	}
	else
	{
		delete sprite;
		sprite = NULL;
		return NULL;
	}
    return sprite;
}
void Soldier::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//Æ½AÀäÈ´
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}
}