//by 王文政 2019年5月27日
//定义后羿的E技能
//放一个大（yuan）鸟（quan）
//代码大部分嫖houyi普攻的类
//是Sprite类的子类

#ifndef __HOUYIESKILL__
#define __HOUYIESKILL__

#include "cocos2d.h"
#include "HouyiHero.h"
#include "BasicSkill.h"

class HouyiESkill : public BasicSkill
{
	cocos2d::Vec2 _arrowMoveDirection;
	cocos2d::Vec2 _originPosition;

public:

	//更新函数
	virtual void update(float dt);

	//触发技能
	static HouyiESkill* createHouyiESkill(Hero* hero);
	void takeHouyiESkill(HouyiHero* hero);
	//重载take函数
	void takeHouyiESkill(cocos2d::Vec2 startPoint,cocos2d::Vec2 targetPoint);

	//设置大鸟箭头移动方向
	//需要设置一个模长为1的二维向量
	//用于在update函数中控制箭头移动方向
	void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _arrowMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _arrowMoveDirection; }

	//当运动一定距离时将该大鸟箭头删除
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
};

#endif // !__HOUYIESKILL__
