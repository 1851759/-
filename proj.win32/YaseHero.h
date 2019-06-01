//by 王文政 2019年5月30日
//这个类是亚瑟的类
//是Hero类的子类
//代码嫖后羿类


#ifndef __YASEHERO__
#define __YASEHERO__
#include "cocos2d.h"
#include "Hero.h"


class YaseHero : public Hero
{
	//设定英雄的名字
	//亚瑟的名字为'Y'
	char _heroName;

public:

	virtual bool init();

	static YaseHero* create();

	virtual void update(float dt);
};


#endif // !__YASEHERO__
