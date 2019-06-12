#ifndef __JIEHERO__

#define __JIEHERO__

#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;

//后羿技能属性
#define JieNormalAttackRange 100.0
#define JieNormalAttackMoveSpeed 1.0//3.0

#define JieQSkillRange 200.0
#define JieQSkillDamage 100
#define JieQSkillMoveSpeed 5.0//5.0
#define JieQSkillCD 2.0
#define JieQSkillAfterShake 1.0

#define JieWSkillRange 200.0
#define JieWSkillLastTime 15.0
#define JieWSkillCD 15.0
#define JieWSkillAfterShake 0.2

#define JieESkillRange 1000.0
#define JieESkillDamage 200
#define JieESkillLastTime 15.0
#define JieESkillDisappearTime 5.0
#define JieESkillMoveSpeed 2.0//5.0
#define JieESkillCD 15.0
#define JieESkillDamageTime 10
#define JieESkillAfterShake 1.0

//在此处定义劫初始属性
#define JieMoveSpeed 60.0
#define JieAttackSpeed 0.5
#define JieAttack 100.0
#define JieDefence 100.0
#define JieMaxHealth 200.0
#define JieHealth 200.0
#define JieMaxMagic 100.0
#define JieMagic 100.0
#define JieNormalAttackAfterShake 1.0/ JieAttackSpeed

typedef enum
{
	WShadowTag = 821,
	EShadowTag = 822
} ShadowTag;

class JieHero : public Hero
{
	Vec2 _wSkillShadowPoint;
	Vec2 _eSkillShadowPoint;
	Vec2 _appearPoint;
	bool _isWShadow;
	bool _canWChange;
	bool _isEShadow;
	bool _canEChange;
	bool _inDisappear;
	float _wShadowLastTime;
	float _eShadowLastTime;
	float _eSkillDamage;

public:

	virtual bool init();

	static JieHero* create();

	Vec2 getWShadowPoint() const { return _wSkillShadowPoint; }
	void setWShadowPoint(Vec2 pos) { _wSkillShadowPoint = pos; }
	Vec2 getEShadowPoint() const { return _eSkillShadowPoint; }
	void setEShadowPoint(Vec2 pos) { _eSkillShadowPoint = pos; }
	Vec2 getAppearPoint() const { return _appearPoint; }
	void setAppearPoint(Vec2 pos) { _appearPoint = pos; }

	float getESkillDamage() const { return _eSkillDamage; }
	void setESkillDamage(float damage) { _eSkillDamage = damage; }

	void wShadowOn() { _isWShadow = true; }
	void wShadowOff() { _isWShadow = false; }
	bool isWShadowOn() const { return _isWShadow; }

	void eShadowOn() { _isEShadow = true; }
	void eShadowOff() { _isEShadow = false; }
	bool isEShadowOn() const { return _isEShadow; }

	void setCanWChange(bool can) { _canWChange = can; }
	bool wCanChange() const { return _canWChange; }
	void setCanEChange(bool can) { _canEChange = can; }
	bool eCanChange() const { return _canEChange; }
	void setInDisappear(bool dsp) { _inDisappear = dsp; }
	bool isInDisappear() const { return _inDisappear; }

	float getWShadowLastTime() const { return _wShadowLastTime; }
	void setWShadowLastTime(float time) { _wShadowLastTime = time; }
	void cutWShadowLastTime(float time) { _wShadowLastTime -= time; }
	float getEShadowLastTime() const { return _eShadowLastTime; }
	void cutEShadowLastTime(float time) { _eShadowLastTime -= time; }
	void setEShadowLastTime(float time) { _eShadowLastTime = time; }
	
};



#endif // !__JIEHERO__
