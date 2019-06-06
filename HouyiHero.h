//by ������ 2019��5��26��
//������Ǻ������
//��Hero�������


#ifndef __HOUYIHERO__
#define __HOUYIHERO__
#include "cocos2d.h"
#include "Hero.h"


//���༼������
#define HouyiNormalAttackRange 100.0
#define HouyiNormalAttackMoveSpeed 3.0


#define HouyiQSkillLastTime 5.0
#define HouyiQSkillAttackSpeedAdd 2.0
#define HouyiQSkillMoveSpeedAdd 20.0
#define HouyiQSkillCD 10.0
#define HouyiQSkillAfterShake 1.0

#define HouyiWSkillRange 200.0
#define HouyiWSkillDamage 100
#define HouyiWSkillArrowNumber 9
#define HouyiWSkillMoveSpeed 3.0
#define HouyiWSkillCD 5.0
#define HouyiWSkillAfterShake 1.0

#define HouyiESkillRange 1000.0
#define HouyiESkillDamage 100
#define HouyiESkillMoveSpeed 5.0
#define HouyiESkillCD 5.0
#define HouyiESkillAfterShake 1.0

//�ڴ˴���������ʼ����
#define HouyiMoveSpeed 60.0
#define HouyiAttackSpeed 0.5
#define HouyiAttack 100.0
#define HouyiDefence 100.0
#define HouyiMaxHealth 200.0
#define HouyiHealth 200.0
#define HouyiMaxMagic 100.0
#define HouyiMagic 100.0
#define HouyiNormalAttackAfterShake 1.0/ HouyiAttackSpeed

typedef enum
{
	HouyiBuffTag = 2222,
} HouyiBuff;


class HouyiHero : public Hero
{
	//�趨Ӣ�۵�����
	//���������Ϊ'H'
	char _heroName;


public:

	virtual bool init();

	static HouyiHero* create();

	void buffUpdate(float dt);

	void AIcontrol(Hero* hero);

	void AIAction(float dt);
};


#endif // !__HOUYIHERO__
