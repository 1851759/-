#ifndef __JIEQSKILL__
#define __JIEQSKILL__

#include "cocos2d.h"
#include "JieHero.h"
#include "BasicSkill.h"

class JieQSkill : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//��������
	static JieQSkill* createJieQSkill(Hero* hero);
	void takeJieQSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//���ùⲨ��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//���˶�һ������ʱ���ùⲨ��ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
};

#endif // !__DAJIQSKILL__
