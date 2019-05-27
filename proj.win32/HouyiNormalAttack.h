//by 王文政 sj2019年5月26日
//定义后羿平A的类
//是Sprite的子类




#ifndef __NORMALATTACK__
#define __NORALATTACK__

#include "cocos2d.h"
#include "HouyiHero.h"



class HouyiNormalAttack : public cocos2d::Sprite
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:
	
	
	//更新函数
	virtual void update(float dt);

	//触发平A
	static HouyiNormalAttack* createTheAttack();
	void takeHouyiNormalAttack(HouyiHero* hero);

	//设置平A箭头移动方向
	//需要设置一个模长为1的二维向量
	//用于在update函数中控制箭头移动方向
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//当运动一定距离时将该平A箭头删除
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
	
};






#endif // __NORMALATTACK__

