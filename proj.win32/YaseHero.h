//by ������ 2019��5��30��
//���������ɪ����
//��Hero�������
//�����κ�����


#ifndef __YASEHERO__
#define __YASEHERO__
#include "cocos2d.h"
#include "Hero.h"


class YaseHero : public Hero
{
	//�趨Ӣ�۵�����
	//��ɪ������Ϊ'Y'
	char _heroName;

public:

	virtual bool init();

	static YaseHero* create();

	virtual void update(float dt);
};


#endif // !__YASEHERO__
