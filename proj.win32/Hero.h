//by ������ 2019��5��27��
//Ӣ�۵Ļ��࣬���������ƶ��ͼ����ͷ�

#ifndef __HERO__
#define __HERO__

#include "cocos2d.h"

//ͨ��ö�����Ͷ���Ӣ�۵�tag
//Ӣ�۵�tag
typedef enum
{
	Yase_Tag =101,
	Houyi_Tag = 102,
	Daji_Tag = 103

} HeroName;

//Ӣ�۽��и��ֶ���ʱ��tag
typedef enum
{
	HeroMove = 10,
	HeroSkillQ = 11,
	HeroSkillW = 12,
	HeroSkillE = 13,
	HeroNormalAttack = 14
} HeroAction;

//����Ӣ�۵�״̬ ���Ż�������
typedef	enum
	{
	dead = 1,
	alive = 2
	} status;

class Hero : public cocos2d::Sprite
{
	//���¼���ֵ������ģ����̺����ͬʱ����
	bool _isPressingKeyboard;
	char _pressedKey;
	cocos2d::Vec2 _touchPoint;
	cocos2d::Vec2 _heroPoint;

	//�ڴ˴����Ӣ�۵�������ֵ

	//�ð汾Ŀ��Ϊ�����ƶ��ͼ����ͷ������ݲ�����Ӣ������
	//�趨Ӣ�۵�����
	//���������Ϊ'H'
	//��ɪ������Ϊ'Y'
	//槼�������Ϊ'D'
	char _heroName;
	int _level;
	float _moveSpeed;

	//������ģ��װ��
	//ÿ��װ����һ��ö��ֵ
	//��Ӧ��ֵΪ0ʱ��ʾδװ��
	//��Ӧ��ֵΪ1ʱ��ʾװ����װ��
	int equipmentlist[200];

	//�趨�����ٶȺ���ȴʱ��
	//��Щֵֻ����Ϊװ��Ч���ı�
	float _eSkillCdTime;
	float _wSkillCdTime;
	float _qSkillCdTime;
	float _attackSpeed;
	
	//�趨�����ͼ��ܵȴ�ʱ��
	//��Щֵ��Ϊ0ʱÿ֡����С1/60
	//ֵΪ0ʱ�ſ��Թ����ͷ�������
	float _attackWaitTime;
	float _qSkillWaitTime;
	float _wSkillWaitTime;
	float _eSkillWaitTime;

	//���ܵȼ�
	int _qSkillLevel;
	int _wSkillLevel;
	int _eSkillLevel;

	//buff���ܵĳ���ʱ��
	float _buffTime;
	bool _isInBuff;

public:

	//��дSPrite���init����
	virtual bool init();
	
	static Hero* create();

	//������ȴʱ��ĺ���
	//ͨ������Ϸ�����е���Ӣ�۵�scheduleupdate����
	//������Ӣ�۵���д���update����
	//ʣ����ȴʱ��ļ�����update������ʵ��
	virtual void update(float dt);

	
	//��ú͸ı乥���ٶ�
	float getAttackSpeed() const{ return _attackSpeed; } 
	void changeAttackSpeed(const float equipmentAttackSpeed) { _attackSpeed += equipmentAttackSpeed; }

	//��ú͸ı似����ȴ
	float getESkillCdTime() { return _eSkillCdTime; }
	void setESkillCdTime(float cdtime) { _eSkillCdTime = cdtime; }

	float getWSkillCdTime() { return _wSkillCdTime; }
	void setWSkillCdTime(float cdtime) { _wSkillCdTime = cdtime; }

	float getQSkillCdTime() { return _qSkillCdTime; }
	void setQSkillCdTime(float cdtime) { _qSkillCdTime = cdtime; }

	//��ú͸ı�ȴ�ʱ��
	float getAttackWaitTime() { return _attackWaitTime; }
	void cutAttackWaitTime(float waittime) { _attackWaitTime -= waittime; }
	void setAttackWaitTime(float waittime) { _attackWaitTime = waittime; }

	float getQSkillWaitTime() const{ return _qSkillWaitTime; } 
	void cutQSkillWaitTime(float waittime) { _qSkillWaitTime -= waittime; }
	void setQSkillWaitTime(float waittime) { _qSkillWaitTime = waittime; }

	float getWSkillWaitTime() const{ return _wSkillWaitTime; } 
	void cutWSkillWaitTime(float waittime) { _wSkillWaitTime -= waittime; }
	void setWSkillWaitTime(float waittime) { _wSkillWaitTime = waittime; }

	float getESkillWaitTime() const{ return _eSkillWaitTime; } 
	void cutESkillWaitTime(float waittime) { _eSkillWaitTime -= waittime; }
	void setESkillWaitTime(float waittime) { _eSkillWaitTime = waittime; }

	//��ú͸ı�buff����ʱ��
	float getBuffTime() const{ return _buffTime; } 
	void cutBuffTime(float waittime) { _buffTime -= waittime; }
	void setBuffTime(float lasttime) { _buffTime = lasttime; }
	void setBuff(bool isinbuff) { _isInBuff = isinbuff; }
	bool isInBuff() const{ return _isInBuff; }  

	//��ú͸ı�����
		
	//��Ӣ�������ͻ��Ӣ������
	void setHeroName(char name) { _heroName = name; }
	char getHeroName() const{ return _heroName; } 

	//��ú͸ı�ȼ�

	//��ú͸ı似�ܵȼ�
	int getQSkillLevel() const{ return _qSkillLevel; } 
	void qSkillLevelUp() { _qSkillLevel++; } 

	int getWSkillLevel() const{ return _wSkillLevel; } 
	void wSkillLevelUp() { _wSkillLevel++; }

	int getESkillLevel() const{ return _eSkillLevel; } 
	void eSkillLevelUp() { _eSkillLevel++; }

	//��ú͸ı��ƶ��ٶ�
	float getMoveSpeed() const{ return _moveSpeed; } 
	void changeMoveSpeed(const float equipmentAttackSpeed) { _moveSpeed += equipmentAttackSpeed; }

	//��ú͸ı乥���ٶ�

	//��ú͸ı乥����

	//��ú͸ı������

	//��ú͸ı侭��ֵ

	//��ú͸ı���

	//���װ��
	

	//���м�����������ģ��ͬʱ�������ͼ���
	//�ж��Ƿ��ڰ�����
	//�ͼ����еļ����ͷ��й�
	bool isPressingKeyboard() const{ return _isPressingKeyboard; } 
	void setPressingKeyboard() { _isPressingKeyboard = true; }
	void setUnPressingKeyboard() { _isPressingKeyboard = false; }
	void thisKeyPressed(char key) { _pressedKey = key; }
	char pressThisKey() { return _pressedKey; } 


	void setTouchPoint(cocos2d::Vec2 touchPoint) { _touchPoint = touchPoint; }
	void setHeroPoint(cocos2d::Vec2 heroPoint) { _heroPoint = heroPoint; }
	cocos2d::Vec2 getTouchPoint() { return _touchPoint; }
	cocos2d::Vec2 getHeroPoint() { return _heroPoint; }

};





#endif // !__HERO__

