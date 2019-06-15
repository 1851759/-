#ifndef __DAJIESKILL__
#define __DAJIESKILL__

#include "cocos2d.h"
#include "DajiHero.h"
#include "BasicSkill.h"

class DajiESkill : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//��������
	static DajiESkill* createDajiESkill(Hero* hero);
	void takeDajiESkill(DajiHero* hero);
	//����take����
	void takeDajiESkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//���ùⲨ��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ���ô����ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
};

#endif // !__DAJIESKILL__