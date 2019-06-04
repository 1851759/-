#include "Tower.h"
#include "SimpleAudioEngine.h"
#include"cocos2d.h"

bool Tower::init()
{
	initWithFile("tower.png");

	return true;
}

Tower* Tower::create()
{
	Tower* sprite = new Tower();
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
void Tower::update(float dt)
{
	float cuttime = 1.0 / 60.0;
	//Æ½AÀäÈ´
	if (this->getAttackWaitTime() >= 0.01)
	{
		this->cutAttackWaitTime(cuttime);
	}
}