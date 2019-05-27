//by 王文政 2019年5月26日
//这个类是后羿的类
//是Hero类的子类


#ifndef __HOUYIHERO__
#define __HOUYIHERO__
#include "cocos2d.h"
#include "Hero.h"


class HouyiHero : public Hero
{
	//设定英雄的名字
	//后羿的名字为'H'
	char _heroName;
	
public:
	
	virtual bool init();

	static HouyiHero* create();

	virtual void update(float dt);
};


#endif // !__HOUYIHERO__
