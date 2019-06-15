#ifndef __PAOCHENORMALATTACK__
#define __PAOCHENORMALATTACK__

#include "cocos2d.h"
#include "PaocheSoldier.h"
#include "BasicSkill.h"



class PaocheNormalAttack : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:


	//���º���
	virtual void update(float dt);

	//����ƽA
	static PaocheNormalAttack* createTheAttack(Hero* hero);
	//����take����
	void takePaocheNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//����ƽA��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ����ƽA��ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};






#endif // __PAOCHENORMALATTACK__
