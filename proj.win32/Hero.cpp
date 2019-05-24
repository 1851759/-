#include "cocos2d.h"
#include "Hero.h"

bool Hero::init()
{
	//�±ߵ�if������Ӣ�۵�ͼƬ
	if (!Sprite::initWithFile("qqhero.png"))
	{
		return false;
	}

	return true;
}

Hero* Hero::create()
{
	Hero* sprite = new Hero();
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
	sprite->_moveSpeed = 10;
	
	return sprite;
}
