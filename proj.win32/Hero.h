//Ӣ�۵Ļ��࣬���������ƶ��ͼ����ͷ�


#ifndef __HERO__
#define __HERO__

#include "cocos2d.h"

//ͨ��ö�����Ͷ���Ӣ�۵�tag
//Ӣ�۵�tag
typedef enum
{
	Hero_Tag = 102
} HeroTags;

//Ӣ�۽��и��ֶ���ʱ��tag
typedef enum
{
	HeroMove = 10,
	HeroUseSkillQ = 11,
	HeroUseSkillW = 12,
	HeroUseSkillE = 13,
	HeroUseSkillA = 14
} HeroAction;


//����Ӣ�۵�״̬ ���Ż�������
typedef	enum
	{
	dead = 1,
	alive = 2
	} status;


class Hero : public cocos2d::Sprite
{
	//�ڴ˴����Ӣ�۵�������ֵ
	//�ð汾Ŀ��Ϊ�����ƶ��ͼ����ͷ������ݲ�����Ӣ������


	float _moveSpeed;


public:

	//��дSPrite���init����
	virtual bool init();
	static Hero* create();


	float getMoveSpeed() { return _moveSpeed; } const
		void changeMoveSpeed(const float equipmentMoveSpeed) { _moveSpeed += equipmentMoveSpeed; }

	
	
};





#endif // !__HERO__

