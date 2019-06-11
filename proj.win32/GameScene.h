//������Ϸ����
//by ������ 2019��5��24��

#ifndef __GAMESCENE__
#define __GAMESCENE__

#include "cocos2d.h"

#include "Hero.h"
#include "JinzhanSoldier.h"

#include "HouyiHero.h"
#include "YaseHero.h"
#include "DajiHero.h"

USING_NS_CC;

//������ײ��������
#define MEUNITTEST 0x08
#define MESKILLTEST 0x04
#define OTHERUNITTEST 0x02
#define OTHERSKILLTEST 0x01

//�������
#define MEUNITCATEGORY 0x01
#define MESKILLCATEGORY 0x02
#define OTHERUNITCATEGORY 0x04
#define OTHERSKILLCATEGORY 0x08

//��ײ����
#define MEUNITCOLLISION 0x04
#define MESKILLCOLLISION 0x02
#define OTHERUNITCOLLISION 0x01
#define OTHERSKILLCOLLISION 0x08

//��ɱ�������Ӣ�ۼӵľ���
#define HeroExp 100
#define JinzhanSoldierExp 100
#define YuanchengSoldierExp 100
#define PaocheSoldierExp 100
#define TowerExp 100

//��ɱ�������Ӣ�ۼӵĽ��
#define HeroMoney 100
#define JinzhanSoldierMoney 100
#define YuanchengSoldierMoney 100
#define PaocheSoldierMoney 100
#define TowerMoney 100

//�������
#define WulaWulaCD 10.0

typedef enum
{
	MeHeroTag = 1111,
	AIHeroTag = 1112,
	OtherHeroTag = 1113
} PlayerType;

typedef enum
{
	MeSkillTag = 1114,
	OtherSkillTag = 1115,
} SkillTag;

typedef enum
{
	MeJinzhanSoldierTag = 1116,
	OtherJinzhanSoldierTag = 1117,
	MeYuanchengSoldierTag = 1118,
	OtherYuanchengSoldierTag = 1119,
	MePaocheSoldierTag = 1120,
	OtherPaocheSoldierTag = 1121,
	MeTowerTag = 1122,
	OtherTowerTag = 1123,
	MeCrystalTag = 1124,
	OtherCrystalTag = 1125
} UnitType;
class GameScene :public cocos2d::Layer
{
	char meHeroTag;
	char otherHeroTag;
	int _enermyType;
	int _meFlag;

	int _meMoney, _meMoney_moment;
	int _meExp;
	int _otherMoney;
	int _otherExp;
	bool _ischecking=false;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collidable;
	cocos2d::Vec2 position_now;
	int RedScore = 9999, BlueScore = 9998;                 //Tag
	int moneytag = 8888;
	int equ_num_me = 0,equ_num_enemy;

public:

	void setMeFlag(int flag) { _meFlag = flag; }
	int getMeFlag() const { return _meFlag; }
	//��ȡ���ҽ�Һ;���
	int getMeMoney() const { return _meMoney; }
	void changeMeMoney(int money) { _meMoney += money; }
	int getMeExp() const { return _meExp; }
	void changeMeExp(int exp) { _meExp += exp; }

	int getOtherMoney() const { return _otherMoney; }
	void changeOtherMoney(int money) { _otherMoney += money; }
	int getOtherExp() const { return _otherExp; }
	void changeOtherExp(int exp) { _otherExp += exp; }

	//Ӣ�۲ٿغ���
	void heroMove(Hero* target);
	//���༼��
	void takeHouyiNormalAttack(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeHouyiWSkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeHouyiESkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//��ɪ����
	void takeYaseNormalAttack(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeYaseWSkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);
	void takeYaseESkill(Hero* hero, int flag, cocos2d::Vec2 startPoint, cocos2d::Vec2 targetPoint);

	//槼�����
	void takeDajiNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeDajiQSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeDajiWSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);
	void takeDajiESkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint);

	//��ȡmeHeroTag
	char getMeHeroTag() { return meHeroTag; }
	//����gamescene��herotag����roomscece�е���
	void setMeHeroTag(char heroType) { meHeroTag = heroType; }

	//��ȡotherHeroTag
	char getOtherHeroTag() { return otherHeroTag; }
	void setOtherHeroTag(char heroType) { otherHeroTag = heroType; }

	//��ȡ���趨�з�����Ϊai�����
	int getEnermyType() const { return _enermyType; }
	void setEnermyType(int type) { _enermyType = type; }

	static cocos2d::Scene* createScene(char meHero, char otherHero, bool isAI);
	virtual bool init();

	//���س�ʼ����
	void menuBackCallback(cocos2d::Ref* pSender);
	//������
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//���̼���
	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//��ײ����
	bool contactBegin(cocos2d::PhysicsContact& contact);
	virtual void onEnter();
	virtual void onExit();
	static GameScene* create(char meName, char otherName, bool enermyType);
	//	static GameScene* createWithPhysics(char meName, char otherName, bool isAI);
	void shop_xie(cocos2d::Ref *pSender);
	void shop_duanjian(cocos2d::Ref* pSender);
	void shop_changjian(cocos2d::Ref *pSender);
	void shop_kaijia(cocos2d::Ref *pSender);
	void shop_hongshuijing(cocos2d::Ref *pSender);
	virtual void update(float dt);


	bool setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void collision(float dt);

	//���������ͼ��̼�������onEnter������ͨ���˱��ʽ����

	//�˻�����
	void watchMeAndOther(float dt);

	//��������
	void wulawula(float dt);

	//װ�����
	void equipmentCheck();
	bool isChecking() const { return _ischecking; }
	void setChecking() { _ischecking = true; }
	void setUnChecking() { _ischecking = false; }

	//����λ����Ϣ
	void SendPosition(float dt);

	//���նԷ�Ӣ��λ�ò������ƶ�
	void GetAndMove(float dt);

	//�����뼼���ͷ�
	//void Attacking(float dt);

	//�з�װ������
	void EnemyEquipUpdate(float dt);

	//�ж�ս��
	void Zhanji(float dt);
};

#endif