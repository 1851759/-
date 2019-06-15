#ifndef __PAOCHENORMALATTACK__
#define __PAOCHENORMALATTACK__

#include "cocos2d.h"
#include "PaocheSoldier.h"
#include "BasicSkill.h"



class PaocheNormalAttack : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:


	//更新函数
	virtual void update(float dt);

	//触发平A
	static PaocheNormalAttack* createTheAttack(Hero* hero);
	//重载take函数
	void takePaocheNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//设置平A箭头移动方向
	//需要设置一个模长为1的二维向量
	//用于在update函数中控制箭头移动方向
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//当运动一定距离时将该平A箭头删除
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};






#endif // __PAOCHENORMALATTACK__
