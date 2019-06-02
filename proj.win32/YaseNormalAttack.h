//by ������ 2019��6��2��
//��ɪƽA����
//�κ���ƽA��
#ifndef __YASENORMALATTACK__
#define __YASENORMALATTACK__


#include "cocos2d.h"
#include "YaseHero.h"
#include "BasicSkill.h"

class YaseNormalAttack : public BasicSkill
{
	cocos2d::Vec2 _swordMoveDirection;
	cocos2d::Vec2 _originPosition;

public:
	
	//���º���
	virtual void update(float dt);

	//����ƽA
	static YaseNormalAttack* createTheAttack();
	void takeYaseNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//����ƽA��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��ƽ��ƶ�����
	void setSwordMoveDirection(cocos2d::Vec2 moveDir) { _swordMoveDirection = moveDir; }
	cocos2d::Vec2 getSwordMoveDirection() { return _swordMoveDirection; }

	//���˶�һ������ʱ����ƽA��ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};


#endif // !__YASENORMALATTACK__

