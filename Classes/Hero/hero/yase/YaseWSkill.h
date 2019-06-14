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

	//更新函数
	virtual void update(float dt);

	//触发旋转技能
	static YaseWSkill* createYaseWSkill(Hero* hero);
	void takeYaseWSkill(Hero* hero);
	//重载take函数
	void takeYaseWSkill(cocos2d::Vec2 heroPoint);

	//设置散射中间箭头移动方向
	//需要设置一个模长为1的二维向量
	//用于在update函数中控制箭头移动方向
	/*void setArrowMoveDirection(cocos2d::Vec2 moveDir) { _swordMoveDirection = moveDir; }
	cocos2d::Vec2 getArrowMoveDirection() { return _swordMoveDirection; }
*/
//当运动一定距离时将该箭头删除
	cocos2d::Vec2 getOriginPosition() { return _originPosition; };
	void setOriginPosition(cocos2d::Vec2 position) { _originPosition = position; }
	void stop(float dt);//旋转技能结束停止
};

#endif // !__YASEWSKILL__
