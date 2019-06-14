//by ������ 2019��5��26��
//������Ǻ������
//��Hero�������


#ifndef __HOUYIHERO__
#define __HOUYIHERO__
#include "cocos2d.h"
#include "Hero.h"


//���༼������
#define HouyiNormalAttackRange 100.0
#define HouyiNormalAttackMoveSpeed 1.5


#define HouyiQSkillLastTime 5.0
#define HouyiQSkillAttackSpeedAdd 0.1
#define HouyiQSkillMoveSpeedAdd 1.0
#define HouyiQSkillCD 10.0
#define HouyiQSkillAfterShake 1.0

#define HouyiWSkillRange 200.0
#define HouyiWSkillDamage 100
#define HouyiWSkillArrowNumber 5
#define HouyiWSkillMoveSpeed 1.5
#define HouyiWSkillCD 5.0
#define HouyiWSkillAfterShake 1.0

#define HouyiESkillRange 1000.0
#define HouyiESkillDamage 100
#define HouyiESkillMoveSpeed 2.5
#define HouyiESkillCD 5.0
#define HouyiESkillAfterShake 1.0

//�ڴ˴���������ʼ����
#define HouyiMoveSpeed 60.0
#define HouyiAttackSpeed 0.5
#define HouyiAttack 100.0
#define HouyiDefence 100.0
#define HoyyiMaxHealth 200.0
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
