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

	//更新函数
	virtual void update(float dt);

	//触发技能
	static YaseESkill* createYaseESkill(Hero* hero);
	void takeYaseESkill(YaseHero* hero);
	//重载take函数
	void takeYaseESkill(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//设置大剑移动方向
	//需要设置一个模长为1的二维向量
	//用于在update函数中控制箭头移动方向
	void setSwordMoveDirection(cocos2d::Vec2 moveDir) { _swordMoveDirection = moveDir; }
	cocos2d::Vec2 getSwordMoveDirection() { return _swordMoveDirection; }

	//当运动一定距离时将该大剑删除
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
};

#endif // !__YASEESKILL__

