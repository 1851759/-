//by ������ sj2019��5��26��
//�������ƽA����
//��Sprite������




#ifndef __NORMALATTACK__
#define __NORALATTACK__

#include "cocos2d.h"
#include "HouyiHero.h"



class HouyiNormalAttack : public cocos2d::Sprite
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:
	
	
	//���º���
	virtual void update(float dt);

	//����ƽA
	static HouyiNormalAttack* createTheAttack();
	void takeHouyiNormalAttack(HouyiHero* hero);

	//����ƽA��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ����ƽA��ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
	
};






#endif // __NORMALATTACK__

