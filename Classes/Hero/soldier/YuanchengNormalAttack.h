#ifndef __YUANCHENGNORMALATTACK__
#define __YUANCHENGNORMALATTACK__

#include "cocos2d.h"
#include "YuanchengSoldier.h"
#include "BasicSkill.h"



class YuanchengNormalAttack : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:


	//���º���
	virtual void update(float dt);

	//����ƽA
	static YuanchengNormalAttack* createTheAttack(Hero* hero);
	//����take����
	void takeYuanchengNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//����ƽA��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ����ƽA��ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};






#endif // __YUANCHENGNORMALATTACK__