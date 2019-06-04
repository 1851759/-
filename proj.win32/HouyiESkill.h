//by ������ 2019��5��27��
//��������E����
//��һ����yuan����quan��
//����󲿷���houyi�չ�����
//��Sprite�������

#ifndef __HOUYIESKILL__
#define __HOUYIESKILL__

#include "cocos2d.h"
#include "HouyiHero.h"
#include "BasicSkill.h"

class HouyiESkill : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//��������
	static HouyiESkill* createHouyiESkill(Hero* hero);
	void takeHouyiESkill(HouyiHero* hero);
	//����take����
	void takeHouyiESkill(cocos2d::Vec2 startPoint,cocos2d::Vec2 targetPoint);

	//���ô����ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ���ô����ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
};

#endif // !__HOUYIESKILL__
