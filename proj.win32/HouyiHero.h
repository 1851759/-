//by ������ 2019��5��26��
//������Ǻ������
//��Hero�������


#ifndef __HOUYIHERO__
#define __HOUYIHERO__
#include "cocos2d.h"
#include "Hero.h"


class HouyiHero : public Hero
{
	//�趨Ӣ�۵�����
	//���������Ϊ'H'
	char _heroName;
	
public:
	
	virtual bool init();

	static HouyiHero* create();

	virtual void update(float dt);
};


#endif // !__HOUYIHERO__
