//by ������ 2019��5��27��
//Ӣ�۵Ļ��࣬���������ƶ��ͼ����ͷ�

#ifndef __HERO__
#define __HERO__

#include "cocos2d.h"
#include "BasicSprite.h"

//ͨ��ö�����Ͷ���Ӣ�۵�tag
//Ӣ�۵�tag
typedef enum
{
	Yase_Tag =101,
	Houyi_Tag = 102,
	Daji_Tag = 103

} HeroName;

//Ӣ�۽����ƶ�ʱ��tag
typedef enum
{
	HeroMove = 10,
} HeroAction;

//������ҵ�flag Ĭ���˻�player2
typedef enum
{
	Player1 = 300,
	Player2 = 301
} PlayerFlag;

typedef enum
{
	bloodbar = 400
} BloodBar;



//����Ӣ�۵�ͨ������
//ÿ�����辭��
#define ExpPerLevel 200
//ÿ�������
#define MpPerSec 1.0
#define HpPerSec 1.0

//ÿ��������
#define MpPerLevel 20.0
#define HpPerLevel 20.0
#define AtkPerLevel 20.0
#define DefPerLevel 20.0

class Hero : public BasicSprite
{
	//���¼���ֵ������ģ����̺����ͬʱ����
	bool _isPressingKeyboard;
	char _pressedKey;
	cocos2d::Vec2 _touchPoint;
	cocos2d::Vec2 _heroPoint;

	//pve,pvp���
	bool _isAI;
	cocos2d::Vec2 _otherHeroPoint;
	cocos2d::Vec2 _otherTowerPoint;
	cocos2d::Vec2 _otherSoldierPoint;
	int _flag;
	Hero* _otherHero;
	
	//�ڴ˴����Ӣ�۵�������ֵ

	//�ð汾Ŀ��Ϊ�����ƶ��ͼ����ͷ������ݲ�����Ӣ������
	//�趨Ӣ�۵�����
	//���������Ϊ'H'
	//��ɪ������Ϊ'Y'
	//槼�������Ϊ'D'
	char _heroName;
	int _level;
	float _moveSpeed;
	float _atk;
	float _def;
	//Ѫ��
	float _healthPoint;
	float _maxHealthPoint;
	//��
	float _magicPoint;
	float _maxMagicPoint;
	//����ֵ
	int _experiencePoint;
	//���
	int _money;

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

	//�չ��ͼ��ܺ�ҡʱ��
	float _attackAfterShake;
	float _qSkillAfterShake;
	float _wSkillAfterShake;
	float _eSkillAfterShake;

	float _heroAfterShake;
	bool _heroInShake;
	
public:
	//Ѫ��
	void createBlood();

	void checkBlood(float dt);

	int getFlag() const { return _flag; }
	void setFlag(PlayerFlag flag) { _flag = flag; }

	//��дSPrite���init����
	virtual bool init();
	
	static Hero* create();

	//������ȴʱ��ĺ���
	//ͨ������Ϸ�����е���Ӣ�۵�scheduleupdate����
	//������Ӣ�۵���д���update����
	//ʣ����ȴʱ��ļ�����update������ʵ��
	virtual void update(float dt);

	//�趨Ϊ�˻�
	void setAI() { _isAI = true; };
	void setHuman() { _isAI = false; }
	bool isAI() const { return _isAI; }
	//���ø�Ӣ�۵ĵз�Ӣ��
	void setOtherHero(Hero* hero) { _otherHero = hero; }
	Hero* getOtherHero() const { return _otherHero; }
	
	//�������

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

	//��ú͸ı似�ܺ�ҡ����ҡ���
	float getNormalAttackAfterShake() const { return _attackAfterShake; }
	void setNormalAttackAfterShake(float shakeTime) { _attackAfterShake = shakeTime; }
	bool isInShake() const { return _heroInShake; }
	void setHeroInSkake(bool isshake) { _heroInShake = isshake; }


	float getQSkillAfterShake() const { return _qSkillAfterShake; }
	void setQSkillAfterShake(float shakeTime) { _qSkillAfterShake = shakeTime; }

	float getWSkillAfterShake() const { return _wSkillAfterShake; }
	void setWSkillAfterShake(float shakeTime) { _wSkillAfterShake = shakeTime; }

	float getESkillAfterShake() const { return _eSkillAfterShake; }
	void setESkillAfterShake(float shakeTime) { _eSkillAfterShake = shakeTime; }

	float getHeroAfterShake() const { return _heroAfterShake; }
	void setHeroAfterShake(float shakeTime) { _heroAfterShake = shakeTime; }
	void cutHeroAfterShake(float cuttime) { _heroAfterShake -= cuttime; }
	//��ú͸ı�����
		
	//��Ӣ�������ͻ��Ӣ������
	void setHeroName(char name) { _heroName = name; }
	char getHeroName() const{ return _heroName; } 

	//��ú͸ı�ȼ�
	int getLevel() const { return _level; }
	void levelUp() { _level++; }

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

	//��ú͸ı乥����
	float getAttackPoint() const { return _atk; }
	void changeAttackPoint(float point) { _atk += point; }

	//��ú͸ı������
	float getDefensePoint() const { return _def; }
	void changeDefensePoint(float point) { _def += point; }

	//����ֵ���
	virtual float getHealthPoint() const { return _healthPoint; }
	float getMaxHealthPoint() const { return _maxHealthPoint; }
	void changeMaxHealthPoint(float point) { _maxHealthPoint += point; }
	void changeHealthPoint(float point) { _healthPoint += point; }
	virtual void setHealthPoint(float point) { _healthPoint = point; }
	virtual void sufferDamage(float damage) { _healthPoint -= damage; }

	//�����
	float getMagicPoint() const { return _magicPoint; }
	float getMaxMagicPoint() const { return _maxMagicPoint; }
	void changeMaxMagicPoint(float point) { _maxMagicPoint += point; }
	void changeMagicPoint(float point) { _magicPoint += point; }
	void cutMagicPoint(float point) { _magicPoint -= point; }

	virtual int getExpPoint() const { return _experiencePoint; }
	virtual void setExpPoint(int point) { _experiencePoint = point; }
	virtual void changeExpPoint(int point) { _experiencePoint += point; }

	virtual int showMeTheMoney() const { return _money; }
	virtual void setMoney(int point) { _money = point; }
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
	cocos2d::Vec2 getTouchPoint() { return _touchPoint; }

	void setHeroPoint(cocos2d::Vec2 heroPoint) { _heroPoint = heroPoint; }
	cocos2d::Vec2 getHeroPoint() { return _heroPoint; }

	//�˻��������
	void setOtherHeroPoint(cocos2d::Vec2 heroPoint) { _otherHeroPoint = heroPoint; }
	cocos2d::Vec2 getOtherHeroPoint() { return _otherHeroPoint; }

};


extern int n_RedDeath, n_BlueDeath;


#endif // !__HERO__

