#ifndef __DAJINORMALATTACK__
#define __DAJINORMALATTACK__

#include "cocos2d.h"
#include "DajiHero.h"
#include "BasicSkill.h"


class DajiNormalAttack : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//����ƽA
	static DajiNormalAttack* createTheAttack(Hero* hero);
	void takeDajiNormalAttack(DajiHero* hero);
	//����take����
	void takeDajiNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//����ƽA��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ����ƽA��ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};






#endif // __DAJINORMALATTACK__
