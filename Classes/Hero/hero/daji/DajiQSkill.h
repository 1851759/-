#ifndef __DAJIQSKILL__
#define __DAJIQSKILL__

#include "cocos2d.h"
#include "DajiHero.h"
#include "BasicSkill.h"

class DajiQSkill : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//���º���
	virtual void update(float dt);

	//��������
	static DajiQSkill* createDajiQSkill(Hero* hero);
	void takeDajiQSkill(DajiHero* hero);
	//����take����
	void takeDajiQSkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

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
