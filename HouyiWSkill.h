//by ������ 2019��5��27��
//��������W����
//ɢ��
//����󲿷���houyi�չ�����
//��Sprite�������

#ifndef __HOUYIWSKILL__
#define __HOUYIWSKILL__

#include "cocos2d.h"
#include "HouyiHero.h"
#include "BasicSkill.h"

class HouyiWSkill : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//����ɢ�似��
	static HouyiWSkill* createHouyiWSkill();
	void takeHouyiWSkill(HouyiHero* hero, float angle);
	//����take����
	void takeHouyiWSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint, float angle);

	//����ɢ���м��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ���ü�ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};

#endif // !__HOUYIWSKILL__

