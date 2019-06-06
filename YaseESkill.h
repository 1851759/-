#ifndef __YASEESKILL__
#define __YASEESKILL__

#include "cocos2d.h"
#include "YaseHero.h"
#include "BasicSkill.h"

class YaseESkill : public BasicSkill
{
	cocos2d::Vec2 _swordMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//��������
	static YaseESkill* createYaseESkill(Hero* hero);
	void takeYaseESkill(YaseHero* hero);
	//����take����
	void takeYaseESkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//���ô��ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setSwordMoveDirection(cocos2d::Vec2 moveDir) { _swordMoveDirection = moveDir; }
	cocos2d::Vec2 getSwordMoveDirection() { return _swordMoveDirection; }

	//���˶�һ������ʱ���ô�ɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
};

#endif // !__YASEESKILL__

