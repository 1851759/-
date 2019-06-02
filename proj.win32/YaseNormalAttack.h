//by 王文政 2019年6月2日
//亚瑟平A的类
//嫖后羿平A类
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
	
	//更新函数
	virtual void update(float dt);

	//触发平A
	static YaseNormalAttack* createTheAttack();
	void takeYaseNormalAttack(cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//设置平A箭头移动方向
	//需要设置一个模长为1的二维向量
	//用于在update函数中控制剑移动方向
	void setSwordMoveDirection(cocos2d::Vec2 moveDir) { _swordMoveDirection = moveDir; }
	cocos2d::Vec2 getSwordMoveDirection() { return _swordMoveDirection; }

	//当运动一定距离时将该平A箭头删除
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }

};


#endif // !__YASENORMALATTACK__

