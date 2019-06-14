#ifndef __YASEWSKILL__
#define __YASEWSKILL__

#include "cocos2d.h"
#include "YaseHero.h"
#include "BasicSkill.h"

class YaseWSkill : public BasicSkill
{
	cocos2d::Vec2 _swordMoveDirection;
	cocos2d::Vec2 _originPosition;
	cocos2d::Vec2 MeHeroPoint;
	bool isRoll;
public:

	//���º���
	virtual void update(float dt);

	//������ת����
	static YaseWSkill* createYaseWSkill(Hero* hero);
	void takeYaseWSkill(Hero* hero);
	//����take����
	void takeYaseWSkill(cocos2d::Vec2 heroPoint);

	//����ɢ���м��ͷ�ƶ�����
	//��Ҫ����һ��ģ��Ϊ1�Ķ�ά����
	//������update�����п��Ƽ�ͷ�ƶ�����
	/*void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _swordMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _swordMoveDirection; }
*/
//���˶�һ������ʱ���ü�ͷɾ��
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
	void stop(float dt);//��ת���ܽ���ֹͣ
};

#endif // !__YASEWSKILL__
