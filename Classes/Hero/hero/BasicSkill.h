//by 王文政 2019年6月3日
//所有技能的基类

#ifndef __BASICSKILL__
#define __BASICSKILL__

#include "cocos2d.h"
#include "BasicSprite.h"

class BasicSkill : public BasicSprite
{
	bool _canTakeDamage;
	bool _removeWhenDamage;

public:
	
	//判断能否造成伤害
	//为true时可以造成伤害
	//为false时忽视碰撞
	bool canTakeDamage() const { return _canTakeDamage; }
	void setCanTakeDamage(bool can) { _canTakeDamage = can; }

	//判断技能造成伤害后是否remove
	//为true时 造成伤害后删除
	//为false时 造成伤害后不删除
	bool shouldRemove() const { return _removeWhenDamage; }
	void setIfRemoveWhenDamage(bool can) { _removeWhenDamage = can; }

};

#endif // !__BASICSKILL__
