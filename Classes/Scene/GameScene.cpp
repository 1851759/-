#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "GameScene.h"
#include "RoomScene.h"

#include "DefenceTower.h"
#include "CrystalTower.h"
#include "Hero.h"

#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"
#include "HouyiWSkill.h"

#include "YaseHero.h"
#include "YaseNormalAttack.h"
#include"YaseESkill.h"
#include"YaseWSkill.h"

#include "DajiHero.h"
#include "DajiNormalAttack.h"
#include "DajiQSkill.h"
#include "DajiWSkill.h"
#include "DajiESkill.h"

#include "JieHero.h"
#include "JieNormalAttack.h"
#include "JieQSkill.h"


#include"Soldier.h"
#include"JinzhanSoldier.h"
#include"YuanchengSoldier.h"
#include"PaocheSoldier.h"
#include"client.h"

//修改技能范围时需要修改英雄头文件define中的参数

USING_NS_CC;
Vec2 position_last = Vec2(0, 0);
Vec2 position_last_me = Vec2(0, 0), position_last_other = Vec2(0, 0);
//英雄起始位置
//注意此处用数字表示////////////////////////////////////////////////////////////////////////////////////////////////////
Vec2 Player1StartPosition(650, 350);
Vec2 Player2StartPosition(1050, 650);
Vec2 HeroPosition;
char *AboutKeyboardMessage;
char JustAboutKeyboard[SIZE] = "Q0/0/", TwoBlood[SIZE] = "X", TwoLevel[SIZE] = "L";

GameScene* GameScene::create(char meName, char otherName, bool isAI)
{
	//	log("create before if");
	GameScene* gameScene = new GameScene();

	gameScene->setMeHeroTag(meName);
	gameScene->setOtherHeroTag(otherName);
	gameScene->setUnChecking();
	if (isAI)
	{
		gameScene->setEnermyType(AIHeroTag);
	}
	else
	{
		gameScene->setEnermyType(OtherHeroTag);
	}
	if (gameScene->init())
	{
		gameScene->autorelease();
		return gameScene;
	}
	else
	{
		delete gameScene;
		gameScene = NULL;
		return NULL;
	}
}

Scene* GameScene::createScene(char meHero, char otherHero, bool isAI)
{
	Scene* scene = Scene::createWithPhysics();
	/*scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);*/
	//将物理世界的重力设为0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto gs = GameScene::create(meHero, otherHero, isAI);
	scene->addChild(gs);
	return scene;
}

//onEnter函数
//在该函数中注册监听器
//在该函数定义背景之类不需要进行操作和只需加载一次的精灵

//by 王文政 2019年5月27日
void GameScene::onEnter()
{
	//该onEnter函数重写了Scene类的onEnter函数
	//onExit函数也是一个道理
	//onEnter函数第一行一定要加这句
	Layer::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	//注册鼠标监听器
	//使用λ表达式
	//目前只实现了使英雄在鼠标松开时  根据移动速度 移动到鼠标位置的功能
	//根据左键响应，右键我不会
	auto mouseListener = EventListenerTouchOneByOne::create();
	//点击时
	//注意该函数是一个bool类型
	mouseListener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};

	//点击后未松开并移动鼠标时
	mouseListener->onTouchMoved = [](Touch* touch, Event* event)
	{

	};

	//松开时
	mouseListener->onTouchEnded = CC_CALLBACK_2(GameScene::touchEnded, this);

	//吞没事件，使鼠标的操作不传给下一层
	mouseListener->setSwallowTouches(true);
	//又是看不懂的玄学一步，通过这步给鼠标监听器绑定英雄的tag/////////////////////////////////    ↓这个就是tag
	EventDispatcher *mouseDispatcher = Director::getInstance()->getEventDispatcher(); //     ↓
	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(this->getMeFlag()));

	//注册键盘监听器
	//使用λ表达式
	//目前只实现了 Q W E A B P键按下时英雄做出响应

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		auto target = static_cast<Hero*>(event->getCurrentTarget());

		target->setUnPressingKeyboard();
		target->thisKeyPressed('\0');
	};
	//不知道该不该吞没事件，也不知道怎么设置键盘吞没
	//书上没写
	//咱也不知道，咱也不敢问

	//跟鼠标监听看不懂的玄学一步一样，通过这步给鼠标监听器绑定英雄的tag/////////////////////////////    ↓这个就是tag
	EventDispatcher *keyboardDispatcher = Director::getInstance()->getEventDispatcher();//       ↓
	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(this->getMeFlag()));

	//注册物理碰撞监听器
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::contactBegin, this);
	contactListener->onContactPreSolve = [](PhysicsContact& contact, const PhysicsContactPreSolve& solve)
	{
		log("asdaaaaaaaaaa");
		return true;
	};
	contactListener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};
	contactListener->onContactSeparate = [](PhysicsContact& contact)
	{
		log("DSDSD");
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 1);


}

void GameScene::onExit()
{
	//反正一定要加下边这句
	Layer::onExit();

	//在onExit函数中注销监听器
	//不会呐
	//不知道会弄出什么bug//////////////////////////////////////////////////////////////////////////////////////////////////
	//但是目前不注销没事

}

bool GameScene::init()
{
	log("gs init run");

	/////////////////////////////
	// 1. super init first
	//不知道为什么要加但是还是加上
	//可能跟场景没有成功创建有关
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//游戏地图
	_tileMap = TMXTiledMap::create("Map.tmx");
	addChild(_tileMap, 0, 100);

	//初始化碰撞层
	_collidable = _tileMap->getLayer("Collidable");
	_collidable->setVisible(false);


	//根据meHeroTag设置己方英雄精灵
	switch (this->getMeHeroTag())
	{

	case 'H':
	{
		static auto hero = HouyiHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		hero->setPhysicsBody(body);
		if (!IfAI)
		{
			if (ID == 1)
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				hero->setPosition(Player1StartPosition);
				hero->setFlag(Player1);
			}
			else
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				hero->setPosition(Player2StartPosition);
				hero->setFlag(Player2);
			}
		}
		else
		{
			body->setContactTestBitmask(MEUNITTEST);
			body->setCategoryBitmask(MEUNITCATEGORY);
			body->setCollisionBitmask(MEUNITCOLLISION);
			hero->setPosition(Player1StartPosition);
			hero->setFlag(Player1);
		}
		hero->setHuman();
		addChild(hero, 100, hero->getFlag());
		this->setMeFlag(hero->getFlag());

		//增加技能图标
		auto HouyiQ = Sprite::create("HouyiQ.png");
		HouyiQ->setPosition(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height / 9);
		this->addChild(HouyiQ, 200);
		auto HouyiW = Sprite::create("HouyiW.png");
		HouyiW->setPosition(origin.x + visibleSize.width * 13 / 16, origin.y + visibleSize.height / 9);
		this->addChild(HouyiW, 200);
		auto HouyiE = Sprite::create("HouyiE.png");
		HouyiE->setPosition(origin.x + visibleSize.width * 7 / 8, origin.y + visibleSize.height / 9);
		this->addChild(HouyiE, 200);

		//该函数为计算冷却时间和攻击间隔的函数
		hero->schedule(schedule_selector(HouyiHero::buffUpdate), 1.0 / 20.0);
		hero->scheduleUpdate();
		break;
	}
	case 'Y':
	{
		auto hero = YaseHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		hero->setPhysicsBody(body);
		if (!IfAI)
		{
			if (ID == 1)
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				hero->setPosition(Player1StartPosition);
				hero->setFlag(Player1);
			}
			else
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				hero->setPosition(Player2StartPosition);
				hero->setFlag(Player2);
			}
		}
		else
		{
			body->setContactTestBitmask(MEUNITTEST);
			body->setCategoryBitmask(MEUNITCATEGORY);
			body->setCollisionBitmask(MEUNITCOLLISION);
			hero->setPosition(Player1StartPosition);
			hero->setFlag(Player1);
		}
		hero->setHuman();
		addChild(hero, 100, hero->getFlag());
		this->setMeFlag(hero->getFlag());

		//增加技能图标
		auto YaseQ = Sprite::create("YaseQ.png");
		YaseQ->setPosition(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height / 9);
		this->addChild(YaseQ, 200);
		auto YaseW = Sprite::create("YaseW.png");
		YaseW->setPosition(origin.x + visibleSize.width * 13 / 16, origin.y + visibleSize.height / 9);
		this->addChild(YaseW, 200);
		auto YaseE = Sprite::create("YaseE.png");
		YaseE->setPosition(origin.x + visibleSize.width * 7 / 8, origin.y + visibleSize.height / 9);
		this->addChild(YaseE, 200);

		//该函数为计算冷却时间和攻击间隔的函数
		hero->schedule(schedule_selector(YaseHero::buffUpdate), 1.0 / 20.0);
		hero->scheduleUpdate();
		break;
	}

	case 'D':
	{
		static auto hero = DajiHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		hero->setPhysicsBody(body);
		if (!IfAI)
		{
			if (ID == 1)
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				hero->setPosition(Player1StartPosition);
				hero->setFlag(Player1);
			}
			else
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				hero->setPosition(Player2StartPosition);
				hero->setFlag(Player2);
			}
		}
		else
		{
			body->setContactTestBitmask(MEUNITTEST);
			body->setCategoryBitmask(MEUNITCATEGORY);
			body->setCollisionBitmask(MEUNITCOLLISION);
			hero->setPosition(Player1StartPosition);
			hero->setFlag(Player1);
		}
		hero->setHuman();
		addChild(hero, 100, hero->getFlag());
		this->setMeFlag(hero->getFlag());

		//增加技能图标
		auto DajiQ = Sprite::create("DajiQ.png");
		DajiQ->setPosition(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height / 9);
		this->addChild(DajiQ, 200);
		auto DajiW = Sprite::create("DajiW.png");
		DajiW->setPosition(origin.x + visibleSize.width * 13 / 16, origin.y + visibleSize.height / 9);
		this->addChild(DajiW, 200);
		auto DajiE = Sprite::create("DajiE.png");
		DajiE->setPosition(origin.x + visibleSize.width * 7 / 8, origin.y + visibleSize.height / 9);
		this->addChild(DajiE, 200);

		//该函数为计算冷却时间和攻击间隔的函数
		hero->scheduleUpdate();
		break;
	}
	//劫
	case 'J':
	{
		static auto hero = JieHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		hero->setPhysicsBody(body);
		if (!IfAI)
		{
			if (ID == 1)
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				hero->setPosition(Player1StartPosition);
				hero->setFlag(Player1);
			}
			else
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				hero->setPosition(Player2StartPosition);
				hero->setFlag(Player2);
			}
		}
		else
		{
			body->setContactTestBitmask(MEUNITTEST);
			body->setCategoryBitmask(MEUNITCATEGORY);
			body->setCollisionBitmask(MEUNITCOLLISION);
			hero->setPosition(Player1StartPosition);
			hero->setFlag(Player1);
		}
		hero->setHuman();
		addChild(hero, 100, hero->getFlag());
		this->setMeFlag(hero->getFlag());

		//增加技能图标
		auto JieQ = Sprite::create("JieQ.png");
		JieQ->setPosition(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height / 9);
		this->addChild(JieQ, 200);
		auto JieW = Sprite::create("JieW.png");
		JieW->setPosition(origin.x + visibleSize.width * 13 / 16, origin.y + visibleSize.height / 9);
		this->addChild(JieW, 200);
		auto JieE = Sprite::create("JieE.png");
		JieE->setPosition(origin.x + visibleSize.width * 7 / 8, origin.y + visibleSize.height / 9);
		this->addChild(JieE, 200);
		//该函数为计算冷却时间和攻击间隔的函数
		hero->scheduleUpdate();
		break;
	}

	default:break;
	}

	//设置敌方英雄
	switch (this->getOtherHeroTag())
	{
	case 'H':
	{
		auto otherHero = HouyiHero::create();
		auto body = PhysicsBody::createCircle(otherHero->getContentSize().width / 2);
		otherHero->setPhysicsBody(body);
		if (IfAI)
		{
			body->setContactTestBitmask(OTHERUNITTEST);
			body->setCategoryBitmask(OTHERUNITCATEGORY);
			body->setCollisionBitmask(OTHERUNITCOLLISION);
			otherHero->setPosition(Player2StartPosition);
			otherHero->setAI();
			otherHero->setFlag(Player2);
			otherHero->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(this->getMeFlag())));
		}
		else
		{
			otherHero->setHuman();
			if (ID == 1)
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				otherHero->setPosition(Player2StartPosition);
				otherHero->setFlag(Player2);
			}
			else
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				otherHero->setPosition(Player1StartPosition);
				otherHero->setFlag(Player1);
			}
		}
		addChild(otherHero, 100, otherHero->getFlag());
		otherHero->scheduleUpdate();
		otherHero->schedule(schedule_selector(HouyiHero::buffUpdate), 1.0 / 20.0);
		break;
	}

	case 'D':
	{
		auto otherHero = DajiHero::create();
		auto body = PhysicsBody::createCircle(otherHero->getContentSize().width / 2);
		otherHero->setPhysicsBody(body);
		if (IfAI)
		{
			body->setContactTestBitmask(OTHERUNITTEST);
			body->setCategoryBitmask(OTHERUNITCATEGORY);
			body->setCollisionBitmask(OTHERUNITCOLLISION);
			otherHero->setPosition(Player2StartPosition);
			otherHero->setAI();
			otherHero->setFlag(Player2);
			otherHero->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(this->getMeFlag())));
		}
		else
		{
			otherHero->setHuman();
			if (ID == 1)
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				otherHero->setPosition(Player2StartPosition);
				otherHero->setFlag(Player2);
			}
			else
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				otherHero->setPosition(Player1StartPosition);
				otherHero->setFlag(Player1);
			}
		}
		addChild(otherHero, 100, otherHero->getFlag());
		otherHero->scheduleUpdate();
		break;
	}

	case 'Y':
	{
		auto otherHero = YaseHero::create();
		auto body = PhysicsBody::createCircle(otherHero->getContentSize().width / 2);
		otherHero->setPhysicsBody(body);
		if (IfAI)
		{
			body->setContactTestBitmask(OTHERUNITTEST);
			body->setCategoryBitmask(OTHERUNITCATEGORY);
			body->setCollisionBitmask(OTHERUNITCOLLISION);
			otherHero->setPosition(Player2StartPosition);
			otherHero->setAI();
			otherHero->setFlag(Player2);
			otherHero->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(this->getMeFlag())));
		}
		else
		{
			otherHero->setHuman();
			if (ID == 1)
			{
				body->setContactTestBitmask(OTHERUNITTEST);
				body->setCategoryBitmask(OTHERUNITCATEGORY);
				body->setCollisionBitmask(OTHERUNITCOLLISION);
				otherHero->setPosition(Player2StartPosition);
				otherHero->setFlag(Player2);
			}
			else
			{
				body->setContactTestBitmask(MEUNITTEST);
				body->setCategoryBitmask(MEUNITCATEGORY);
				body->setCollisionBitmask(MEUNITCOLLISION);
				otherHero->setPosition(Player1StartPosition);
				otherHero->setFlag(Player1);
			}
		}
		addChild(otherHero, 100, otherHero->getFlag());
		otherHero->scheduleUpdate();
		otherHero->schedule(schedule_selector(YaseHero::buffUpdate), 1.0 / 20.0);
		break;
	}



	default:break;
	}

	//双方防御塔
	auto player1Tower = DefenceTower::create(Player1);
	player1Tower->setPosition(560, 310);
	////////////////////////////////////////////////////playerflag之和是601
	player1Tower->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(Player2)));
	player1Tower->scheduleUpdate();
	this->addChild(player1Tower, 200, MeTowerTag);
	//player1Tower->setScale(0.8);

	auto player2Tower = DefenceTower::create(Player2);
	player2Tower->setPosition(1160, 695);
	player2Tower->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(Player1)));
	player2Tower->scheduleUpdate();
	this->addChild(player2Tower, 200, OtherTowerTag);
	//player2Tower->setScale(0.8);

	//双方水晶
	auto player1Crystal = CrystalTower::create(Player1);
	player1Crystal->setPosition(380, 165);
	player1Crystal->scheduleUpdate();
	this->addChild(player1Crystal, 200, MeCrystalTag);
	//player1Crystal->setScale(0.8);

	auto player2Crystal = CrystalTower::create(Player2);
	player2Crystal->setPosition(1285, 795);
	player2Crystal->scheduleUpdate();
	this->addChild(player2Crystal, 200, OtherCrystalTag);
	//player2Crystal->setScale(0.8);
	

	//装备商店
    MenuItemImage *shop_xie = MenuItemImage::create("zhuangbei/xie.png", "zhuangbei/xie.png", CC_CALLBACK_1(GameScene::shop_xie, this));
    shop_xie->setPosition(Vec2(-710,300));
    MenuItemImage *shop_shoutao = MenuItemImage::create("zhuangbei/duanjian.png", "zhuangbei/duanjian.png", CC_CALLBACK_1(GameScene::shop_duanjian, this));
    shop_shoutao->setPosition(Vec2(-710,235));
    MenuItemImage *shop_changgong = MenuItemImage::create("zhuangbei/changjian.png", "zhuangbei/changgong.png", CC_CALLBACK_1(GameScene::shop_changjian, this));
    shop_changgong->setPosition(Vec2(-710,170));
    MenuItemImage *shop_kaijia = MenuItemImage::create("zhuangbei/kaijia.png", "zhuangbei/kaijia.png", CC_CALLBACK_1(GameScene::shop_kaijia, this));
    shop_kaijia->setPosition(Vec2(-710,115));
    MenuItemImage *shop_hongshuijing = MenuItemImage::create("zhuangbei/hongshuijing.png", "zhuangbei/hongshuijing.png", CC_CALLBACK_1(GameScene::shop_hongshuijing, this));
    shop_hongshuijing->setPosition(Vec2(-710,50));

    Menu *_menu = Menu::create(shop_xie, shop_shoutao,shop_changgong,shop_kaijia,shop_hongshuijing, NULL);
    this->addChild(_menu,200);

//左上角战绩
	auto score_blue = LabelTTF::create("0 ", "Arial", 36);
	this->addChild(score_blue, 2);
	score_blue->setPosition(80, 850);
	score_blue->setTag(BlueScore);
	auto vs = LabelTTF::create("vs", "Arial", 24);
	this->addChild(vs, 2);
	vs->setPosition(122, 850);
	auto score_red = LabelTTF::create("0 ", "Arial", 36);
	this->addChild(score_red, 2);
	score_red->setPosition(150, 850);
	score_red->setTag(RedScore);

	this->schedule(schedule_selector(GameScene::Zhanji), 1.0 / 10.0);

	//金币
	auto gold = LabelTTF::create("Gold:", "Arial", 18);
	gold->setPosition(Vec2(1290, 20));
	this->addChild(gold, 2);
	auto num = LabelTTF::create(" ", "Arial", 18);
	num->setPosition(Vec2(1330, 20));
	this->addChild(num, 2);
	//_meMoney_moment = _meMoney*100;
	this->setTag(moneytag);

	//经验条
	Sprite* bar = Sprite::create("bar.png");
	this->addChild(bar, 200);
	bar->setPosition(1300, 200);
	bar->setScale(0.5);
	Sprite* Exp = Sprite::create("Exp.png");
	ProgressTimer* EXP = ProgressTimer::create(Exp);
	EXP->setType(ProgressTimer::Type::BAR);
	EXP->setPosition(1300, 200);
	EXP->setMidpoint(Vec2(0, 0.5));
	EXP->setBarChangeRate(Vec2(1, 0));
	EXP->setTag(Expbar);
	this->addChild(EXP, 200);
	Exp->setScale(0.5);
	this->schedule(schedule_selector(GameScene::checkExp), 0.1f);

	//装备查看面板
	Sprite*equ_che = Sprite::create("equipment.png");
	equ_che->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(equ_che, 200, 666);
	equ_che->setVisible(false);

	this->schedule(schedule_selector(GameScene::watchMeAndOther), 1.0 / 20.0);
	this->schedule(schedule_selector(GameScene::jinzhanWulawula), WulaWulaCD);
	this->schedule(schedule_selector(GameScene::EnemyEquipUpdate), 1.0 / 20.0);
	this->schedule(schedule_selector(GameScene::MakeMoney), 1);
	if (!IfAI)
	{
		this->schedule(schedule_selector(GameScene::GetAndMove), 1.0 / 20.0);
		this->schedule(schedule_selector(GameScene::SendPosition), 1.0 / 20.0);
	}
	return true;
}

//控制AI的函数
//by 王文政 2019年6月2日
void GameScene::watchMeAndOther(float dt)
{
	position_now_other = (this->getChildByTag(601 - this->getMeFlag()))->getPosition();
	if (setPlayerPosition(position_now_other) == true)
	{
		(this->getChildByTag(601 - this->getMeFlag()))->setPosition(position_last_other);
	}
	else position_last_other = position_now_other;
	Hero* meHero = dynamic_cast<Hero*>(this->getChildByTag(this->getMeFlag()));
	Hero* otherHero = dynamic_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()));
	//监控我方经验金币
	meHero->setMoney(this->getMeMoney());
	meHero->setExpPoint(this->getMeExp());
	if (this->getMeExp() >= ExpPerLevel)
	{
		this->changeMeExp(-ExpPerLevel);
	}
	//监控敌方经验金币
	otherHero->setMoney(this->getOtherMoney());
	otherHero->setExpPoint(this->getOtherExp());
	if (this->getOtherExp() >= ExpPerLevel)
	{
		this->changeOtherExp(-ExpPerLevel);
	}

	//获取双方英雄的位置
	Vec2 meHeroPoint = meHero->getPosition();
	Vec2 otherHeroPoint = otherHero->getPosition();

	//如果是AI 对AI进行控制
	if (this->getEnermyType() == AIHeroTag)
	{
		Vec2 distance = otherHeroPoint - meHeroPoint;
		//获取双方距离
		float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		//如果AI控制后羿
		if (this->getOtherHeroTag() == 'H')
		{
			//判断并进行普攻
			if (length <= HouyiNormalAttackRange && otherHero->getAttackWaitTime() <= 0.01)
			{
				takeHouyiNormalAttack(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setAttackWaitTime(1.0 / otherHero->getAttackSpeed());
				otherHero->setHeroAfterShake(otherHero->getNormalAttackAfterShake());
			}//end 普攻

			//判断并Q技能开buff
			if (length <= 200.0 && otherHero->getQSkillWaitTime() <= 0.01)
			{
				//发动q技能，持续时间内增加后羿攻击速度
				otherHero->setBuff(true);
				//持续时间k*q技能等级
				otherHero->setBuffTime(HouyiQSkillLastTime * otherHero->getQSkillLevel());
				//该技能实现效果在update函数中实现
				otherHero->setQSkillWaitTime(otherHero->getQSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getQSkillAfterShake());
			}//end buff

			//判断并W技能
			if (length <= HouyiWSkillRange - 20 && otherHero->getWSkillWaitTime() <= 0.01)
			{
				takeHouyiWSkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W

			//判断并放大
			if (length <= HouyiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				takeHouyiESkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E

		}

		//如果AI控制亚瑟
		if (this->getOtherHeroTag() == 'Y')
		{
			//判断并进行普攻
			if (length <= YaseNormalAttackRange && otherHero->getAttackWaitTime() <= 0.01)
			{
				takeYaseNormalAttack(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setAttackWaitTime(1.0 / otherHero->getAttackSpeed());
				otherHero->setHeroAfterShake(otherHero->getNormalAttackAfterShake());
			}//end 普攻

			//判断并W技能
			if (length <= YaseWSkillRange - 20 && otherHero->getWSkillWaitTime() <= 0.01)
			{
				takeYaseWSkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W

			//判断并放大
			if (length <= YaseESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				takeYaseESkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E
		}
		//如果AI控制妲己
		if (this->getOtherHeroTag() == 'D')
		{
			//判断并进行普攻
			if (length <= DajiNormalAttackRange && otherHero->getAttackWaitTime() <= 0.01)
			{
				takeDajiNormalAttack(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setAttackWaitTime(1.0 / otherHero->getAttackSpeed());
				otherHero->setHeroAfterShake(otherHero->getNormalAttackAfterShake());
			}//end 普攻
			//判断并Q技能
			if (length <= DajiQSkillRange && otherHero->getQSkillWaitTime() <= 0.01)
			{
				takeDajiQSkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setQSkillWaitTime(otherHero->getQSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getQSkillAfterShake());
			}//end Q
			//判断并W技能
			if (length <= DajiWSkillRange && otherHero->getWSkillWaitTime() <= 0.01)
			{
				takeDajiWSkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W
			//判断并放大
			if (length <= DajiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				takeDajiESkill(otherHero, Player2, otherHeroPoint, meHeroPoint);
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E
		}
	}
	else
	{
		if (n > 0)
		{
			//后裔
			if (this->getOtherHeroTag() == 'H')
			{
				//判断并进行普攻
				if (AQWE == 'A')
				{
					takeHouyiNormalAttack(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行Q技能
				if (AQWE == 'Q')
				{
					//发动q技能，持续时间内增加后羿攻击速度
					otherHero->setBuff(true);
					//持续时间k*q技能等级
					otherHero->setBuffTime(HouyiQSkillLastTime * otherHero->getQSkillLevel());
					//该技能实现效果在update函数中实现
				}
				//判断并进行W技能
				if (AQWE == 'W')
				{
					takeHouyiWSkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行E技能
				if (AQWE == 'E')
				{
					takeHouyiESkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}

			}
			//亚瑟
			if (this->getOtherHeroTag() == 'Y')
			{
				//判断并进行普攻
				if (AQWE == 'A')
				{
					takeYaseNormalAttack(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行Q技能
				if (AQWE == 'Q')
				{
					otherHero->setBuff(true);
					otherHero->setBuffTime(YaseQSkillLastTime * otherHero->getQSkillLevel());
				}
				//判断并进行W技能
				if (AQWE == 'W')
				{
					takeYaseWSkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行E技能
				if (AQWE == 'E')
				{
					takeYaseESkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
			}
			//妲己
			if (this->getOtherHeroTag() == 'D')
			{
				//判断并进行普攻
				if (AQWE == 'A')
				{
					takeDajiNormalAttack(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行Q技能
				if (AQWE == 'Q')
				{
					takeDajiQSkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行W技能
				if (AQWE == 'W')
				{
					takeDajiWSkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
				//判断并进行E技能
				if (AQWE == 'E')
				{
					takeDajiESkill(otherHero, 601 - this->getMeFlag(), otherHeroPoint, AQWE_Direction);
				}
			}
			n--;
		}
	}
	this->removeChildByTag(moneytag);
	//_meMoney_moment = _meMoney*100;
	cocos2d::__String* m = cocos2d::__String::createWithFormat("%d", _meMoney);
	auto mm = LabelTTF::create(m->getCString(), "Arial", 18);
	mm->setPosition(1330, 20);
	this->addChild(mm, 2, moneytag);

	//客户端1号发送己方血量和等级
	if (ID == 1)
	{
		P1Blood = meHero->getHealthPoint();
		P2Blood = otherHero->getHealthPoint();
		P1Level = meHero->getLevel();
		P2Level = otherHero->getLevel();
		TwoBlood[1] = P1Blood / 10;
		TwoBlood[2] = P2Blood / 10;
		TwoLevel[1] = P1Level;
		TwoLevel[2] = P2Level;
		Cli.MessageSending(TwoBlood);
		Cli.MessageSending(TwoLevel);
	}
	else
	{
		meHero->setHealthPoint(P2Blood);
		otherHero->setHealthPoint(P1Blood);
		meHero->setLevel(P2Level);
		otherHero->setLevel(P1Level);
	}
}

//by 王文政 2019年5月20日
//λ表达式无法使用this，故单独把touchEnded函数 keypressed拿出来写
void GameScene::keyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//根据tag获取英雄
	auto target = static_cast<Hero*>(event->getCurrentTarget());
	//当前正在按下按键，此时点击鼠标会变为类似选择攻击目标的作用
	//不再是移动
	target->setPressingKeyboard();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
	{
		target->thisKeyPressed('A');
		break;
	}

	case EventKeyboard::KeyCode::KEY_Q:
	{
		target->thisKeyPressed('Q');
		//在此处发动后羿Q
		if (target->getHeroName() == 'H')
		{

			if (target->getQSkillWaitTime() <= 0.01)
			{
				//停止移动动作发动技能
				target->stopActionByTag(HeroMove);
				//发动q技能，持续时间内增加后羿攻击速度和移动速度
				target->setBuff(true);
				//持续时间5*q技能等级
				target->setBuffTime(HouyiQSkillLastTime);

				//发送给对方客户端
				if (!IfAI)
				{
					Cli.MessageSending(JustAboutKeyboard);
				}

				//该技能实现效果在HouyiHero update函数中实现
				target->setQSkillWaitTime(target->getQSkillCdTime());
				target->setHeroAfterShake(target->getQSkillAfterShake());

			}
		}
		//在此处发动亚瑟Q
		if (target->getHeroName() == 'Y')
		{
			if (target->getQSkillWaitTime() <= 0.01)
			{

				//停止移动动作发动技能
				target->stopActionByTag(HeroMove);
				//发动q技能，持续时间内增加后羿攻击速度和移动速度
				target->setBuff(true);
				//持续时间5*q技能等级
				target->setBuffTime(YaseQSkillLastTime * target->getQSkillLevel());

				//发送给对方客户端
				if (!IfAI)
				{
					Cli.MessageSending(JustAboutKeyboard);
				}

				//该技能实现效果在YaseHero update函数中实现
				target->setQSkillWaitTime(target->getQSkillCdTime());
				target->setHeroAfterShake(target->getQSkillAfterShake());
			}
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		target->thisKeyPressed('W');
		if (target->getHeroName() == 'J' && !static_cast<JieHero*>(target)->isInDisappear())
		{
			if (static_cast<JieHero*>(target)->isWShadowOn() && static_cast<JieHero*>(target)->wCanChange())
			{
				static_cast<JieHero*>(target)->setCanWChange(false);
				Vec2 tPos{ target->getPosition() };
				target->setPosition(this->getChildByTag(WShadowTag)->getPosition());
				this->getChildByTag(WShadowTag)->setPosition(tPos);
				static_cast<JieHero*>(target)->setWShadowPoint(tPos);
			}
		}
		break;
	}

	case EventKeyboard::KeyCode::KEY_E:
	{
		target->thisKeyPressed('E');
		if (target->getHeroName() == 'J' && !static_cast<JieHero*>(target)->isInDisappear())
		{
			if (static_cast<JieHero*>(target)->isEShadowOn() && static_cast<JieHero*>(target)->eCanChange())
			{
				static_cast<JieHero*>(target)->setCanEChange(false);
				Vec2 tPos{ target->getPosition() };
				target->setPosition(this->getChildByTag(EShadowTag)->getPosition());
				this->getChildByTag(EShadowTag)->setPosition(tPos);
				static_cast<JieHero*>(target)->setEShadowPoint(tPos);
			}
		}
		break;
	}
	//暂定按P键实现查看装备功能
	case EventKeyboard::KeyCode::KEY_P:
	{
		target->thisKeyPressed('P');
		this->equipmentCheck();
		break;
	}
	//B键打开商店
	case EventKeyboard::KeyCode::KEY_B:
	{
		target->thisKeyPressed('B');
		break;
	}
	default: break;
	}
}
void GameScene::touchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//通过给英雄设置的标签获取英雄
	//书上原话是获取事件所绑定的精灵
	//很玄学的一步我也不知道是什么原理
	//init函数中addChild(hero,20,tag),其中的tag就是该英雄的标签

	//获取松开鼠标时的鼠标位置
	Vec2 touchPosition = touch->getLocation();
	//如果当前英雄为后羿
	if (this->meHeroTag == 'H')
	{
		auto target = static_cast<HouyiHero*>(event->getCurrentTarget());
		//将英雄的成员变量touchPoint赋值为touchPosition
		target->setTouchPoint(touchPosition);
		//获取英雄当前位置
		Vec2 heroPosition = target->getPosition();

		//如果点击鼠标时未按键，则把鼠标点击作为向该点移动
		if (!target->isPressingKeyboard() && target->getHeroAfterShake() <= 0.01)
		{
			heroMove(target);
		}
		//如果点击鼠标时按键，则根据按键进行技能释放
		//此时鼠标的点对应于技能释放的点
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01)
				{
					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);
					takeHouyiNormalAttack(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'A';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置普攻间隔和攻击后摇
					target->setAttackWaitTime(1.0 / target->getAttackSpeed());
					target->setHeroAfterShake(target->getNormalAttackAfterShake());
				}
				break;
			}

			case 'Q':
			{
				//后羿的q技能为未点击鼠标时使用
				//在键盘监听中定义
				break;
			}
			case 'W':
			{
				if (target->getWSkillWaitTime() <= 0.01)
				{
					//停止当前的移动进行W
					target->stopActionByTag(HeroMove);
					takeHouyiWSkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'W';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置W CD和技能后摇
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}
			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					//停止当前的移动进行大招
					target->stopActionByTag(HeroMove);
					takeHouyiESkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'E';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置大招等待时间
					target->setESkillWaitTime(target->getESkillCdTime());
					target->setHeroAfterShake(target->getESkillAfterShake());
				}
				break;

			}

			case 'P':
			{
				break;
			}

			case 'B':
			{
				break;
			}
			default:break;
			}
		}
	}

	//如果当前英雄为亚瑟
	if (this->meHeroTag == 'Y')
	{
		auto target = static_cast<YaseHero*>(event->getCurrentTarget());
		//将英雄的成员变量touchPoint赋值为touchPosition
		target->setTouchPoint(touchPosition);
		//获取英雄当前位置
		Vec2 heroPosition = target->getPosition();

		//如果点击鼠标时未按键，则把鼠标点击作为向该点移动
		if (!target->isPressingKeyboard())
		{
			heroMove(target);
		}

		//如果点击鼠标时按键，则根据按键进行技能释放
		//此时鼠标的点对应于技能释放的点
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01)
				{
					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);
					takeYaseNormalAttack(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'A';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置平A等待时间
					target->setAttackWaitTime(1.0 / target->getAttackSpeed());
					target->setHeroAfterShake(target->getNormalAttackAfterShake());
				}
				break;
			}

			case 'Q':
			{
				break;
			}

			case 'W':
			{
				if (target->getWSkillWaitTime() <= 0.01)
				{
					//边移动边旋转
					takeYaseWSkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'W';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置CD和技能后摇
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}

			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					//停止当前的移动进行大招
					target->stopActionByTag(HeroMove);
					takeYaseESkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'E';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置大招等待时间
					target->setESkillWaitTime(target->getESkillCdTime());
					target->setHeroAfterShake(target->getESkillAfterShake());
				}
				break;
			}

			case 'P':
			{
				break;
			}

			case 'B':
			{
				break;
			}
			default:break;
			}
		}
	}

	//如果当前英雄为妲己
	if (this->meHeroTag == 'D')
	{
		auto target = static_cast<DajiHero*>(event->getCurrentTarget());
		//将英雄的成员变量touchPoint赋值为touchPosition
		target->setTouchPoint(touchPosition);
		//获取英雄当前位置
		Vec2 heroPosition = target->getPosition();

		//如果点击鼠标时未按键，则把鼠标点击作为向该点移动
		if (!target->isPressingKeyboard() && target->getHeroAfterShake() <= 0.01)
		{
			heroMove(target);
		}
		//如果点击鼠标时按键，则根据按键进行技能释放
		//此时鼠标的点对应于技能释放的点
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01)
				{
					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);
					takeDajiNormalAttack(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'A';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置普攻间隔和攻击后摇
					target->setAttackWaitTime(1.0 / target->getAttackSpeed());
					target->setHeroAfterShake(target->getNormalAttackAfterShake());
				}
				break;
			}

			case 'Q':
			{
				if (target->getQSkillWaitTime() <= 0.01)
				{
					//停止当前的移动进行Q
					target->stopActionByTag(HeroMove);
					takeDajiQSkill(target, target->getFlag(), heroPosition, touchPosition);
					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'Q';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置Q CD和技能后摇
					target->setQSkillWaitTime(target->getQSkillCdTime());
					target->setHeroAfterShake(target->getQSkillAfterShake());
				}
				break;
			}
			case 'W':
			{
				if (target->getWSkillWaitTime() <= 0.01)
				{
					//停止当前的移动进行W
					target->stopActionByTag(HeroMove);
					takeDajiWSkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'W';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置W CD和技能后摇
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}
			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					//停止当前的移动进行大招
					target->stopActionByTag(HeroMove);
					takeDajiESkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'E';
						Cli.MessageSending(AboutKeyboardMessage);
					}

					//重置大招等待时间
					target->setESkillWaitTime(target->getESkillCdTime());
					target->setHeroAfterShake(target->getESkillAfterShake());
				}
				break;

			}

			case 'P':
			{
				break;
			}

			case 'B':
			{
				break;
			}
			default:break;
			}
		}
	}
	//如果选择劫，暂时劫仅限于人机对战中己方使用
	if (this->meHeroTag == 'J')
	{
		auto target = static_cast<JieHero*>(event->getCurrentTarget());
		//将英雄的成员变量touchPoint赋值为touchPosition
		target->setTouchPoint(touchPosition);
		//获取英雄当前位置
		Vec2 heroPosition = target->getPosition();

		//如果点击鼠标时未按键，则把鼠标点击作为向该点移动
		if (!target->isPressingKeyboard() && target->getHeroAfterShake() <= 0.01)
		{
			heroMove(target);
		}
		//如果点击鼠标时按键，则根据按键进行技能释放
		//此时鼠标的点对应于技能释放的点
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01 && !target->isInDisappear())
				{
					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);
					takeJieNormalAttack(target, target->getFlag(), heroPosition, touchPosition);

					////发送给对方客户端
					//if (!IfAI)
					//{
					//	AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
					//	AboutKeyboardMessage[0] = 'A';
					//	Cli.MessageSending(AboutKeyboardMessage);
					//}

					//重置普攻间隔和攻击后摇
					target->setAttackWaitTime(1.0 / target->getAttackSpeed());
					target->setHeroAfterShake(target->getNormalAttackAfterShake());
				}
				break;
			}

			case 'Q':
			{
				if (target->getQSkillWaitTime() <= 0.01 && !target->isInDisappear())
				{
					//停止当前的移动进行Q
					target->stopActionByTag(HeroMove);
					takeJieQSkill(target, target->getFlag(), heroPosition, touchPosition);
					//发送给对方客户端
					/*if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'Q';
						Cli.MessageSending(AboutKeyboardMessage);
					}*/
					//重置Q CD和技能后摇
					target->setQSkillWaitTime(target->getQSkillCdTime());
					target->setHeroAfterShake(target->getQSkillAfterShake());
				}
				break;
			}
			case 'W':
			{

				if (target->getWSkillWaitTime() <= 0.01 && heroPosition.getDistance(touchPosition) <= JieWSkillRange
					&& !target->isInDisappear())
				{
					//停止当前的移动进行W
					target->stopActionByTag(HeroMove);
					takeJieWSkill(target, target->getFlag(), heroPosition, touchPosition);

					//发送给对方客户端
					/*if (!IfAI)
					{
						AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
						AboutKeyboardMessage[0] = 'W';
						Cli.MessageSending(AboutKeyboardMessage);
					}*/

					//重置W CD和技能后摇
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}
			case 'E':
			{

				if (target->getESkillWaitTime() <= 0.01 && heroPosition.getDistance(touchPosition) <= JieESkillRange
					&& !target->isInDisappear()
					&& touchPosition.getDistance(this->getChildByTag(601 - this->getMeFlag())->getPosition()) <= 10)
				{
					//停止当前的移动进行大招
					target->stopActionByTag(HeroMove);
					takeJieESkill(target, target->getFlag(), heroPosition, touchPosition);

					////发送给对方客户端
					//if (!IfAI)
					//{
					//	AboutKeyboardMessage = FloatToChar(touchPosition.x, touchPosition.y);
					//	AboutKeyboardMessage[0] = 'E';
					//	Cli.MessageSending(AboutKeyboardMessage);
					//}

					//重置大招等待时间
					target->setESkillWaitTime(target->getESkillCdTime());
					target->setHeroAfterShake(target->getESkillAfterShake());
				}
				break;

			}

			case 'P':
			{
				break;
			}

			case 'B':
			{
				break;
			}
			default:break;
			}
		}
	}
	this->schedule(schedule_selector(GameScene::collision), 1.0 / 60.0);
}

void GameScene::shop_xie(cocos2d::Ref* pSender)
{
	if (_meMoney >= 300&&equ_num_me<=4) 
	{
		_meMoney -= 300; 
		static_cast<Hero*>(this->getChildByTag(this->getMeFlag()))->changeMoveSpeed(30);
		auto xie = Sprite::create("1.png");
		this->getChildByTag(666)->addChild(xie);
		xie->setPosition(320+equ_num_me*80,340);
		if (!IfAI)
			Cli.MessageSending("BX");
		equ_num_me++;
	}
}

void GameScene::shop_duanjian(cocos2d::Ref* pSender)
{
	if (_meMoney >= 300&&equ_num_me<=4)
	{
		_meMoney -= 300;
		static_cast<Hero*>(this->getChildByTag(this->getMeFlag()))->changeAttackSpeed(0.5);
		auto duanjian= Sprite::create("2.png");
		this->getChildByTag(666)->addChild(duanjian);
		duanjian->setPosition(320 + equ_num_me* 80, 340);
		if (!IfAI)
			Cli.MessageSending("BD");
		equ_num_me++;
	}
}

void GameScene::shop_changjian(cocos2d::Ref* pSender)
{
	if (_meMoney >= 300&& equ_num_me <= 4)
	{
		_meMoney -= 300;
		static_cast<Hero*>(this->getChildByTag(this->getMeFlag()))->changeAttackPoint(200);
		auto changjian = Sprite::create("3.png");
		this->getChildByTag(666)->addChild(changjian);
		changjian->setPosition(320 + equ_num_me * 80, 340);
		if (!IfAI)
			Cli.MessageSending("BC");
		equ_num_me++;
	}
}

void GameScene::shop_kaijia(cocos2d::Ref* pSender)
{
	if (_meMoney >= 300&& equ_num_me <= 4)
	{
		_meMoney -= 300;
		static_cast<Hero*>(this->getChildByTag(this->getMeFlag()))->changeDefensePoint(200);
		auto kaijia = Sprite::create("4.png");
		this->getChildByTag(666)->addChild(kaijia);
		kaijia->setPosition(320 + equ_num_me * 80, 340);
		if (!IfAI)
			Cli.MessageSending("BK");
		equ_num_me++;
	}
}

void GameScene::shop_hongshuijing(cocos2d::Ref* pSender)
{
	if (_meMoney >= 300&& equ_num_me <= 4)
	{
		_meMoney -= 300;
		static_cast<Hero*>(this->getChildByTag(this->getMeFlag()))->changeMaxHealthPoint(100);
		auto hong = Sprite::create("5.png");
		this->getChildByTag(666)->addChild(hong);
		hong->setPosition(320 + equ_num_me * 80, 340);
		if (!IfAI)
			Cli.MessageSending("BH");
		equ_num_me++;
	}
}

void GameScene::update(float dt)
{

}
//判断碰撞
void GameScene::collision(float dt)
{
	position_now = (this->getChildByTag(this->getMeFlag()))->getPosition();
	if (setPlayerPosition(position_now) == true)
	{
		(this->getChildByTag(this->getMeFlag()))->setPosition(position_last);
	}
	else position_last = position_now;
}

//判断碰撞
bool GameScene::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);//从像素坐标转换为瓦片坐标
	int tileGid = _collidable->getTileGIDAt(tileCoord);//获得该瓦片的GID
	if (tileGid > 0)
	{
		return true;
	}
	return false;
}



//换算坐标
Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

//判断精灵碰撞
bool GameScene::contactBegin(cocos2d::PhysicsContact& contact)
{

	//	log("contact");
	auto spriteA = (BasicSprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (BasicSprite*)contact.getShapeB()->getBody()->getNode();

	//	log("A %d ,B %d", spriteA->getTag(), spriteB->getTag());

	if (spriteA && spriteA->getTag() == OtherSkillTag)
	{
		//此时A是敌方技能 B是我方单位
		auto otherSkill = static_cast<BasicSkill*>(spriteA);
		auto meHero = static_cast<Hero*>(spriteB);
		//己方单位受到伤害
		meHero->sufferDamage(otherSkill->getDamagePoint() / (1 + meHero->getDefensePoint() / 100));
		//如果己方单位死亡
		//给对面英雄加经验和金币
		if (meHero->getHealthPoint() <= 0)
		{
			if (ID == 1)
			{
				if (meHero->getTag() == MeJinzhanSoldierTag)
				{
					this->changeOtherExp(JinzhanSoldierExp);
					this->changeOtherMoney(JinzhanSoldierMoney);
				}
				else 
				{
					if (meHero->getTag() == MeYuanchengSoldierTag)
					{
						this->changeOtherExp(YuanchengSoldierExp);
						this->changeOtherMoney(YuanchengSoldierMoney);
					}
					else 
					{
						if (meHero->getTag() == MePaocheSoldierTag)
						{
							this->changeOtherExp(PaocheSoldierExp);
							this->changeOtherMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeOtherExp(HeroExp);
							this->changeOtherMoney(HeroMoney);
						}
					}
				}
			}
			else
			{
				if (meHero->getTag() == MeJinzhanSoldierTag)
				{
					this->changeMeExp(JinzhanSoldierExp);
					this->changeMeMoney(JinzhanSoldierMoney);
				}
				else
				{
					if (meHero->getTag() == MeYuanchengSoldierTag)
					{
						this->changeMeExp(YuanchengSoldierExp);
						this->changeMeMoney(YuanchengSoldierMoney);
					}
					else
					{
						if (meHero->getTag() == MePaocheSoldierTag)
						{
							this->changeMeExp(PaocheSoldierExp);
							this->changeMeMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeMeExp(HeroExp);
							this->changeMeMoney(HeroMoney);
						}
					}
				}

			}
		}
		//如果技能为打中就消失，则让技能消失
		if (otherSkill->shouldRemove())
		{
			otherSkill->removeFromParent();
			return false;
		}
	}
	if (spriteB && spriteB->getTag() == OtherSkillTag)
	{
		//此时B是敌方技能 A是我方单位
		auto otherSkill = static_cast<BasicSkill*>(spriteB);
		auto meHero = static_cast<Hero*>(spriteA);
		meHero->sufferDamage(otherSkill->getDamagePoint() / (1 + meHero->getDefensePoint() / 100));
		//如果己方单位死亡
		//给对面英雄加经验和金币
		if (meHero->getHealthPoint() <= 0)
		{
			if (ID == 1)
			{
				if (meHero->getTag() == MeJinzhanSoldierTag)
				{
					this->changeOtherExp(JinzhanSoldierExp);
					this->changeOtherMoney(JinzhanSoldierMoney);
				}
				else
				{
					if (meHero->getTag() == MeYuanchengSoldierTag)
					{
						this->changeOtherExp(YuanchengSoldierExp);
						this->changeOtherMoney(YuanchengSoldierMoney);
					}
					else
					{
						if (meHero->getTag() == MePaocheSoldierTag)
						{
							this->changeOtherExp(PaocheSoldierExp);
							this->changeOtherMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeOtherExp(HeroExp);
							this->changeOtherMoney(HeroMoney);
						}
					}
				}
			}
			else
			{

				if (meHero->getTag() == MeJinzhanSoldierTag)
				{
					this->changeMeExp(JinzhanSoldierExp);
					this->changeMeMoney(JinzhanSoldierMoney);
				}
				else
				{
					if (meHero->getTag() == MeYuanchengSoldierTag)
					{
						this->changeMeExp(YuanchengSoldierExp);
						this->changeMeMoney(YuanchengSoldierMoney);
					}
					else
					{
						if (meHero->getTag() == MePaocheSoldierTag)
						{
							this->changeMeExp(PaocheSoldierExp);
							this->changeMeMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeMeExp(HeroExp);
							this->changeMeMoney(HeroMoney);
						}
					}
				}

			}
		}
		//如果技能为打中就消失，则让技能消失
		if (otherSkill->shouldRemove())
		{
			otherSkill->removeFromParent();
			return false;
		}
	}
	if (spriteA && spriteA->getTag() == MeSkillTag)
	{
		//此时A是我方技能 B是敌方单位
		auto meSkill = static_cast<BasicSkill*>(spriteA);
		auto otherHero = static_cast<Hero*>(spriteB);
		otherHero->sufferDamage(meSkill->getDamagePoint() / (1 + otherHero->getDefensePoint() / 100));
		//如果敌方单位死亡
		//给我方英雄加经验和金币
		if (otherHero->getHealthPoint() <= 0)
		{
			if (ID == 1)
			{
				if (otherHero->getTag() == OtherJinzhanSoldierTag)
				{
					this->changeMeExp(JinzhanSoldierExp);
					this->changeMeMoney(JinzhanSoldierMoney);
				}
				else 
				{
					if (otherHero->getTag() == OtherYuanchengSoldierTag)
					{
						this->changeMeExp(YuanchengSoldierExp);
						this->changeMeMoney(YuanchengSoldierMoney);
					}
					else 
					{
						if (otherHero->getTag() == OtherPaocheSoldierTag)
						{
							this->changeMeExp(PaocheSoldierExp);
							this->changeMeMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeMeExp(HeroExp);
							this->changeMeMoney(HeroMoney);
						}
					}
				}
			}
			else
			{
				if (otherHero->getTag() == OtherJinzhanSoldierTag)
				{
					this->changeOtherExp(JinzhanSoldierExp);
					this->changeOtherMoney(JinzhanSoldierMoney);
				}
				else
				{
					if (otherHero->getTag() == OtherYuanchengSoldierTag)
					{
						this->changeOtherExp(YuanchengSoldierExp);
						this->changeOtherMoney(YuanchengSoldierMoney);
					}
					else
					{
						if (otherHero->getTag() == OtherPaocheSoldierTag)
						{
							this->changeOtherExp(PaocheSoldierExp);
							this->changeOtherMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeOtherExp(HeroExp);
							this->changeOtherMoney(HeroMoney);
						}
					}
				}
			}
		}
		//如果技能为打中就消失，则让技能消失
		if (meSkill->shouldRemove())
		{
			meSkill->removeFromParent();
			return false;
		}
	}

	if (spriteB && spriteB->getTag() == MeSkillTag)
	{
		//此时B是我方技能 A是敌方单位
		auto meSkill = static_cast<BasicSkill*>(spriteB);
		log("B is Meskill");
		auto otherHero = static_cast<Hero*>(spriteA);
		log("A is other hero");
		otherHero->sufferDamage(meSkill->getDamagePoint() / (1 + otherHero->getDefensePoint() / 100));
		//如果敌方单位死亡
		//给我方英雄加经验和金币
		if (otherHero->getHealthPoint() <= 0)
		{
			if (ID == 1)
			{
				if (otherHero->getTag() == OtherJinzhanSoldierTag)
				{
					this->changeMeExp(JinzhanSoldierExp);
					this->changeMeMoney(JinzhanSoldierMoney);
				}
				else
				{
					if (otherHero->getTag() == OtherYuanchengSoldierTag)
					{
						this->changeMeExp(YuanchengSoldierExp);
						this->changeMeMoney(YuanchengSoldierMoney);
					}
					else
					{
						if (otherHero->getTag() == OtherPaocheSoldierTag)
						{
							this->changeMeExp(PaocheSoldierExp);
							this->changeMeMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeMeExp(HeroExp);
							this->changeMeMoney(HeroMoney);
						}
					}
				}

			}
			else
			{
				if (otherHero->getTag() == OtherJinzhanSoldierTag)
				{
					this->changeOtherExp(JinzhanSoldierExp);
					this->changeOtherMoney(JinzhanSoldierMoney);
				}
				else
				{
					if (otherHero->getTag() == OtherYuanchengSoldierTag)
					{
						this->changeOtherExp(YuanchengSoldierExp);
						this->changeOtherMoney(YuanchengSoldierMoney);
					}
					else
					{
						if (otherHero->getTag() == OtherPaocheSoldierTag)
						{
							this->changeOtherExp(PaocheSoldierExp);
							this->changeOtherMoney(PaocheSoldierMoney);
						}
						else
						{
							this->changeOtherExp(HeroExp);
							this->changeOtherMoney(HeroMoney);
						}
					}
				}
			}
		}
		//如果技能为打中就消失，则让技能消失
		if (meSkill->shouldRemove())
		{
			meSkill->removeFromParent();
			return false;
		}
	}


	return true;
}

void GameScene::heroMove(Hero* target)
{
	Vec2 touchPosition = target->getTouchPoint();
	Vec2 heroPosition = target->getPosition();
	//英雄向该点运动
	//获取英雄目前的速度
	float heroSpeed = target->getMoveSpeed();
	//10
	Vec2 relativePosition = heroPosition - touchPosition;
	//获取相对位置的模长
	float distanceSquare = relativePosition.x*relativePosition.x + relativePosition.y*relativePosition.y;
	float distance = sqrt(distanceSquare);
	//计算运动到该点所需的时间
	float timeNeeded = distance / heroSpeed;

	//先停止当前的运动动作，否则会造成运动的叠加
	target->stopActionByTag(HeroMove);

	//定义一个运动动作moveAction，运动到指定坐标touchPosition
	FiniteTimeAction * moveAction = (FiniteTimeAction*)target->runAction(MoveTo::create(timeNeeded, touchPosition));
	//给这个动作设置tag ----> HeroMove
	moveAction->setTag(HeroMove);
}

void GameScene::takeHouyiNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	HouyiNormalAttack* houyiNormalAttack = HouyiNormalAttack::createTheAttack(hero);
	Vec2 verts[]{
	Vec2(90,10),
	Vec2(100,10),
	Vec2(100,-10),
	Vec2(90,-10)
	};
	auto body = PhysicsBody::createPolygon(verts, 4);
	houyiNormalAttack->setPhysicsBody(body);
	//停止当前的移动进行普攻
	if (flag == Player1)
	{
		this->addChild(houyiNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(houyiNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	houyiNormalAttack->takeHouyiNormalAttack(startPoint, targetPoint);
	//把普攻显示在gamescene场景中
	//当普攻精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
	//重置平A等待时间
}

void GameScene::takeHouyiWSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	Vec2 verts[]{
	Vec2(90,10),
	Vec2(100,10),
	Vec2(100,-10),
	Vec2(90,-10)
	};
	//先弄他十个箭头
	HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
	//中间的箭头单独创建
	houyiWSkill[0] = HouyiWSkill::createHouyiWSkill(hero);
	houyiWSkill[0]->takeHouyiWSkill(startPoint, targetPoint, 0);
	PhysicsBody* body[HouyiWSkillArrowNumber];
	body[0] = PhysicsBody::createPolygon(verts, 4);
	houyiWSkill[0]->setPhysicsBody(body[0]);
	if (flag == Player1)
	{
		this->addChild(houyiWSkill[0], 200, MeSkillTag);
		body[0]->setContactTestBitmask(MESKILLTEST);
		body[0]->setCategoryBitmask(MESKILLCATEGORY);
		body[0]->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(houyiWSkill[0], 200, OtherSkillTag);
		body[0]->setContactTestBitmask(OTHERSKILLTEST);
		body[0]->setCategoryBitmask(OTHERSKILLCATEGORY);
		body[0]->setCollisionBitmask(OTHERSKILLCOLLISION);
	}

	//两边的箭头成对创建
	for (int i = 1; i < HouyiWSkillArrowNumber; i += 2)
	{
		houyiWSkill[i] = HouyiWSkill::createHouyiWSkill(hero);
		body[i] = PhysicsBody::createPolygon(verts, 4);
		houyiWSkill[i]->setPhysicsBody(body[i]);
		if (flag == Player1)
		{
			this->addChild(houyiWSkill[i], 200, MeSkillTag);
			body[i]->setContactTestBitmask(MESKILLTEST);
			body[i]->setCategoryBitmask(MESKILLCATEGORY);
			body[i]->setCollisionBitmask(MESKILLCOLLISION);
		}
		else
		{
			this->addChild(houyiWSkill[i], 200, OtherSkillTag);
			body[i]->setContactTestBitmask(OTHERSKILLTEST);
			body[i]->setCategoryBitmask(OTHERSKILLCATEGORY);
			body[i]->setCollisionBitmask(OTHERSKILLCOLLISION);
		}
		houyiWSkill[i]->takeHouyiWSkill(startPoint, targetPoint, i * 3.14 / 30);//根据弧度制

		houyiWSkill[i + 1] = HouyiWSkill::createHouyiWSkill(hero);
		body[i + 1] = PhysicsBody::createPolygon(verts, 4);
		houyiWSkill[i + 1]->setPhysicsBody(body[i + 1]);
		if (flag == Player1)
		{
			this->addChild(houyiWSkill[i + 1], 200, MeSkillTag);
			body[i + 1]->setContactTestBitmask(MESKILLTEST);
			body[i + 1]->setCategoryBitmask(MESKILLCATEGORY);
			body[i + 1]->setCollisionBitmask(MESKILLCOLLISION);
		}
		else
		{
			this->addChild(houyiWSkill[i + 1], 200, OtherSkillTag);
			body[i + 1]->setContactTestBitmask(OTHERSKILLTEST);
			body[i + 1]->setCategoryBitmask(OTHERSKILLCATEGORY);
			body[i + 1]->setCollisionBitmask(OTHERSKILLCOLLISION);
		}
		houyiWSkill[i + 1]->takeHouyiWSkill(startPoint, targetPoint, -i * 3.14 / 30);//根据弧度制
	}

	//当精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
}

void GameScene::takeHouyiESkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	HouyiESkill* bigBird = HouyiESkill::createHouyiESkill(hero);
	Vec2 verts[]{
	Vec2(50,0),
	Vec2(50,150),
	Vec2(200,150),
	Vec2(320,0),
	Vec2(50,-150),
	Vec2(200,-150)
	};
	auto body = PhysicsBody::createPolygon(verts, 6);

	bigBird->setPhysicsBody(body);
	bigBird->takeHouyiESkill(startPoint, targetPoint);
	if (flag == Player1)
	{
		this->addChild(bigBird, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(bigBird, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	log("%d", bigBird->getTag());
	log("%d", body->getContactTestBitmask());
	//把大招显示在gamescene场景中

	//当大招精灵运动一定距离时删除，该功能在HouyiESkill类的update函数中实现
}

void GameScene::takeYaseNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	YaseNormalAttack* yaseNormalAttack = YaseNormalAttack::createTheAttack(hero);
	Vec2 verts[]{
		Vec2(0,10),
		Vec2(10,10),
		Vec2(10,-10),
		Vec2(0,-10)
	};
	auto body = PhysicsBody::createPolygon(verts, 4);
	yaseNormalAttack->setPhysicsBody(body);
	if (flag == Player1)
	{
		this->addChild(yaseNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(yaseNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yaseNormalAttack->takeYaseNormalAttack(startPoint, targetPoint);
	//把普攻显示在gamescene场景中
	//当普攻精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
}

void GameScene::takeYaseWSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	YaseWSkill* yaseWSkill = YaseWSkill::createYaseWSkill(hero);
	Vec2 verts[] = {
		Vec2(0,0),
		Vec2(YaseWSkillRange,0),
		Vec2(YaseWSkillRange,-2),
		Vec2(0,-2)
	};
	auto body = PhysicsBody::create();
	body->addShape(PhysicsShapePolygon::create(verts, 4));
	yaseWSkill->setPhysicsBody(body);
	if (flag == Player1)
	{
		if (ID == 1)
		{
			this->getChildByTag(this->getMeFlag())->addChild(yaseWSkill, 200, MeSkillTag);
		}
		else
		{
			this->getChildByTag(601 - this->getMeFlag())->addChild(yaseWSkill, 200, OtherSkillTag);
		}
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		if (ID == 1)
		{
			this->getChildByTag(601 - this->getMeFlag())->addChild(yaseWSkill, 200, OtherSkillTag);
		}
		else
		{
			this->getChildByTag(this->getMeFlag())->addChild(yaseWSkill, 200, MeSkillTag);
		}
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yaseWSkill->takeYaseWSkill(hero);
}

void GameScene::takeYaseESkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	YaseESkill* yaseESkill = YaseESkill::createYaseESkill(hero);
	Vec2 verts[]{
	Vec2(-20,-50),
	Vec2(20,-50),
	Vec2(20,-130),
	Vec2(-20,-130)
	};
	auto body = PhysicsBody::createPolygon(verts, 4);
	yaseESkill->setPhysicsBody(body);
	if (flag == Player1)
	{
		this->addChild(yaseESkill, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(yaseESkill, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yaseESkill->takeYaseESkill(startPoint, targetPoint);
}

void GameScene::takeDajiNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	DajiNormalAttack* dajiNormalAttack = DajiNormalAttack::createTheAttack(hero);
	auto body = PhysicsBody::createCircle(dajiNormalAttack->getContentSize().width / 2);
	dajiNormalAttack->setPhysicsBody(body);
	//停止当前的移动进行普攻
	if (flag == Player1)
	{
		this->addChild(dajiNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(dajiNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	dajiNormalAttack->takeDajiNormalAttack(startPoint, targetPoint);
	//把普攻显示在gamescene场景中
	//当普攻精灵运动一定距离时删除，该功能在DajiNormalAttack类的update函数中实现
	//重置平A等待时间
}

void GameScene::takeDajiQSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	DajiQSkill* bigMoon = DajiQSkill::createDajiQSkill(hero);
	Vec2 verts[]{
	Vec2(50,0),
	Vec2(50,120),
	Vec2(200,120),
	Vec2(320,0),
	Vec2(50,-120),
	Vec2(200,-120)
	};
	auto body = PhysicsBody::createPolygon(verts, 6);

	bigMoon->setPhysicsBody(body);
	bigMoon->takeDajiQSkill(startPoint, targetPoint);
	if (flag == Player1)
	{
		this->addChild(bigMoon, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(bigMoon, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	log("%d", bigMoon->getTag());
	log("%d", body->getContactTestBitmask());
	//把大招显示在gamescene场景中

	//当Q精灵运动一定距离时删除，该功能在DajiQSkill类的update函数中实现
}

void GameScene::takeDajiWSkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	DajiWSkill* bigLove = DajiWSkill::createDajiWSkill(hero);
	auto body = PhysicsBody::createCircle(bigLove->getContentSize().height / 2);

	bigLove->setPhysicsBody(body);
	bigLove->takeDajiWSkill(startPoint, targetPoint);
	if (flag == Player1)
	{
		this->addChild(bigLove, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(bigLove, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	log("%d", bigLove->getTag());
	log("%d", body->getContactTestBitmask());
	//把大招显示在gamescene场景中

	//当W精灵运动一定距离时删除，该功能在DajiWSkill类的update函数中实现
}


void GameScene::takeDajiESkill(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	DajiESkill* bigBall[DajiESkillArrowNumber];
	Vec2 dis = targetPoint - startPoint;
	Vec2 vertical = { -dis.y,dis.x };
	Vec2 standardVertical = vertical / sqrt(pow(vertical.x, 2) + pow(vertical.y, 2));
	Vec2 verts[]{
		Vec2(0,0),
		Vec2(20,20),
		Vec2(40,0),
		Vec2(20,-20)
	};
	for (int i = 0; i < DajiESkillArrowNumber; i += 2)
	{
		bigBall[i] = DajiESkill::createDajiESkill(hero);
		auto body1 = PhysicsBody::createPolygon(verts, 4);
		bigBall[i]->setPhysicsBody(body1);
		bigBall[i]->takeDajiESkill(startPoint + (0.5 * i + 0.5) * standardVertical * DajiESkillArrowInterval, targetPoint);
		bigBall[i + 1] = DajiESkill::createDajiESkill(hero);
		auto body2 = PhysicsBody::createPolygon(verts, 4);
		bigBall[i + 1]->setPhysicsBody(body2);
		bigBall[i + 1]->takeDajiESkill(startPoint - (0.5 * i + 0.5) * standardVertical * DajiESkillArrowInterval, targetPoint);
		if (flag == Player1)
		{
			this->addChild(bigBall[i], 200, MeSkillTag);
			body1->setContactTestBitmask(MESKILLTEST);
			body1->setCategoryBitmask(MESKILLCATEGORY);
			body1->setCollisionBitmask(MESKILLCOLLISION);
			this->addChild(bigBall[i + 1], 200, MeSkillTag);
			body2->setContactTestBitmask(MESKILLTEST);
			body2->setCategoryBitmask(MESKILLCATEGORY);
			body2->setCollisionBitmask(MESKILLCOLLISION);
		}
		else
		{
			this->addChild(bigBall[i], 200, OtherSkillTag);
			body1->setContactTestBitmask(OTHERSKILLTEST);
			body1->setCategoryBitmask(OTHERSKILLCATEGORY);
			body1->setCollisionBitmask(OTHERSKILLCOLLISION);
			this->addChild(bigBall[i + 1], 200, OtherSkillTag);
			body2->setContactTestBitmask(OTHERSKILLTEST);
			body2->setCategoryBitmask(OTHERSKILLCATEGORY);
			body2->setCollisionBitmask(OTHERSKILLCOLLISION);
		}
	}
	//把大招显示在gamescene场景中
	//当大招精灵运动一定距离时删除，该功能在HouyiESkill类的update函数中实现
}

void GameScene::takeJieNormalAttack(Hero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	JieNormalAttack* jieNormalAttack = JieNormalAttack::createTheAttack(hero);
	auto body = PhysicsBody::createBox(jieNormalAttack->getContentSize());
	jieNormalAttack->setPhysicsBody(body);
	//停止当前的移动进行普攻
	if (flag == Player1)
	{
		this->addChild(jieNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(jieNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	jieNormalAttack->takeJieNormalAttack(startPoint, targetPoint);
	//把普攻显示在gamescene场景中
	//当普攻精灵运动一定距离时删除，该功能在DajiNormalAttack类的update函数中实现
	//重置平A等待时间
}

void GameScene::takeJieQSkill(JieHero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	JieQSkill* star = JieQSkill::createJieQSkill(hero);
	auto body = PhysicsBody::createCircle(star->getContentSize().height / 4);
	star->setPhysicsBody(body);
	star->takeJieQSkill(startPoint, targetPoint);
	if (flag == Player1)
	{
		this->addChild(star, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(star, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	//Wshadow飞镖
	if (hero->isWShadowOn())
	{
		JieQSkill* star = JieQSkill::createJieQSkill(hero);
		star->setScale(0.22);
		auto body = PhysicsBody::createCircle(star->getContentSize().height / 2);
		star->setPhysicsBody(body);
		star->takeJieQSkill(hero->getWShadowPoint(), targetPoint);
		if (flag == Player1)
		{
			this->addChild(star, 200, MeSkillTag);
			body->setContactTestBitmask(MESKILLTEST);
			body->setCategoryBitmask(MESKILLCATEGORY);
			body->setCollisionBitmask(MESKILLCOLLISION);
		}
		else
		{
			this->addChild(star, 200, OtherSkillTag);
			body->setContactTestBitmask(OTHERSKILLTEST);
			body->setCategoryBitmask(OTHERSKILLCATEGORY);
			body->setCollisionBitmask(OTHERSKILLCOLLISION);
		}
	}
	//Eshadow飞镖
	if (hero->isEShadowOn())
	{
		JieQSkill* star = JieQSkill::createJieQSkill(hero);
		star->setScale(0.22);
		auto body = PhysicsBody::createCircle(star->getContentSize().height / 2);
		star->setPhysicsBody(body);
		star->takeJieQSkill(hero->getEShadowPoint(), targetPoint);
		if (flag == Player1)
		{
			this->addChild(star, 200, MeSkillTag);
			body->setContactTestBitmask(MESKILLTEST);
			body->setCategoryBitmask(MESKILLCATEGORY);
			body->setCollisionBitmask(MESKILLCOLLISION);
		}
		else
		{
			this->addChild(star, 200, OtherSkillTag);
			body->setContactTestBitmask(OTHERSKILLTEST);
			body->setCategoryBitmask(OTHERSKILLCATEGORY);
			body->setCollisionBitmask(OTHERSKILLCOLLISION);
		}
	}
}

void GameScene::takeJieWSkill(JieHero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	Sprite* wShadow = Sprite::create("Ying.png");
	wShadow->setScale(0.5);
	wShadow->setPosition(targetPoint);
	wShadow->setTag(WShadowTag);
	this->addChild(wShadow, 200);
	hero->wShadowOn();
	hero->setWShadowPoint(targetPoint);
	hero->setCanWChange(true);
	this->scheduleOnce(schedule_selector(GameScene::jieWShadow), JieWSkillLastTime);

}
void GameScene::jieWShadow(float dt)
{
	static_cast<JieHero*>(this->getChildByTag(this->getMeFlag()))->wShadowOff();
	static_cast<JieHero*>(this->getChildByTag(this->getMeFlag()))->setCanWChange(false);
	this->removeChildByTag(WShadowTag);
}


void GameScene::takeJieESkill(JieHero* hero, int flag, Vec2 startPoint, Vec2 targetPoint)
{
	Sprite* eShadow = Sprite::create("Ying.png");
	eShadow->setScale(0.5);
	eShadow->setPosition(startPoint);
	eShadow->setTag(EShadowTag);
	this->addChild(eShadow, 200);

	hero->setPosition(targetPoint);
	hero->setEShadowPoint(startPoint);
	hero->setCanEChange(true);
	//hero隐身且不可抓取
	hero->getPhysicsBody()->setContactTestBitmask(0);
	hero->getPhysicsBody()->setCategoryBitmask(0);
	hero->getPhysicsBody()->setCollisionBitmask(0);
	hero->setInDisappear(true);
	hero->setVisible(false);
	hero->setAppearPoint(targetPoint);
	hero->setEShadowLastTime(JieESkillLastTime);
	hero->eShadowOn();
	this->scheduleOnce(schedule_selector(GameScene::jieEappear), JieESkillDisappearTime);
	this->scheduleOnce(schedule_selector(GameScene::jieEShadow), JieESkillLastTime);
	this->scheduleOnce(schedule_selector(GameScene::jieEDamage), JieESkillDamageTime);
}

void GameScene::jieEShadow(float dt)
{
	static_cast<JieHero*>(this->getChildByTag(this->getMeFlag()))->eShadowOff();
	static_cast<JieHero*>(this->getChildByTag(this->getMeFlag()))->setCanEChange(false);
	this->removeChildByTag(EShadowTag);
}

void GameScene::jieEappear(float dt)
{
	auto hero = static_cast<JieHero*>(this->getChildByTag(this->getMeFlag()));
	hero->setVisible(true);
	hero->setScale(0.5);
	hero->setPosition(this->getChildByTag(601 - this->getMeFlag())->getPosition());
	hero->setInDisappear(false);
	hero->getPhysicsBody()->setContactTestBitmask(MEUNITTEST);
	hero->getPhysicsBody()->setCategoryBitmask(MEUNITCATEGORY);
	hero->getPhysicsBody()->setCollisionBitmask(MEUNITCOLLISION);
}

void GameScene::jieEDamage(float dt)
{
	auto me = static_cast<JieHero*>(this->getChildByTag(this->getMeFlag()));
	auto enermy = static_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()));
	enermy->sufferDamage(JieESkillDamage / (1 + enermy->getDefensePoint() / 100));
}

void GameScene::jinzhanWulawula(float dt)
{
	//player1方近战兵
	auto meJinzhanSoldier = JinzhanSoldier::create(Player1);
	meJinzhanSoldier->setPosition(500, 500);
	meJinzhanSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(Player2)));
	this->addChild(meJinzhanSoldier, 200, MeJinzhanSoldierTag);
	meJinzhanSoldier->scheduleUpdate();
	//player2方近战兵
	auto otherJinzhanSoldier = JinzhanSoldier::create(Player2);
	otherJinzhanSoldier->setPosition(900, 900);
	otherJinzhanSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(Player1)));
	this->addChild(otherJinzhanSoldier, 200, OtherJinzhanSoldierTag);
	otherJinzhanSoldier->scheduleUpdate();
	this->scheduleOnce(schedule_selector(GameScene::yuanchengWulawula), 1);
}

void GameScene::yuanchengWulawula(float dt)
{
	//player1方远程兵
	auto meYuanchengSoldier = YuanchengSoldier::create(Player1);
	meYuanchengSoldier->setPosition(500, 500);
	meYuanchengSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(Player2)));
	this->addChild(meYuanchengSoldier, 200, MeYuanchengSoldierTag);
	meYuanchengSoldier->scheduleUpdate();
	//player2方远程兵
	auto otherYuanchengSoldier = YuanchengSoldier::create(Player2);
	otherYuanchengSoldier->setPosition(900, 900);
	otherYuanchengSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(Player1)));
	this->addChild(otherYuanchengSoldier, 200, OtherYuanchengSoldierTag);
	otherYuanchengSoldier->scheduleUpdate();
	this->scheduleOnce(schedule_selector(GameScene::paocheWulawula), 1);
}

void GameScene::paocheWulawula(float dt)
{
	//player1方炮车兵
	auto mePaocheSoldier = PaocheSoldier::create(Player1);
	mePaocheSoldier->setPosition(500, 500);
	mePaocheSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(Player2)));
	this->addChild(mePaocheSoldier, 200, MePaocheSoldierTag);
	mePaocheSoldier->scheduleUpdate();
	//player2方炮车兵
	auto otherPaocheSoldier = PaocheSoldier::create(Player2);
	otherPaocheSoldier->setPosition(900, 900);
	otherPaocheSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(Player1)));
	this->addChild(otherPaocheSoldier, 200, OtherPaocheSoldierTag);
	otherPaocheSoldier->scheduleUpdate();
}

void GameScene::EnemyEquipUpdate(float dt)
{
	if (IfEquipUpdate)
	{
		if (EnemyEquip == 'X')
		{
			static_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()))->changeMoveSpeed(30);
			auto xie = Sprite::create("1.png");
			this->getChildByTag(666)->addChild(xie);
			xie->setPosition(320 + equ_num_enemy * 80, 140);
			equ_num_enemy++;
		}
		if (EnemyEquip == 'D')
		{
			static_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()))->changeAttackSpeed(0.5);
			auto duanjian = Sprite::create("2.png");
			this->getChildByTag(666)->addChild(duanjian);
			duanjian->setPosition(320 + equ_num_enemy * 80, 140);
			equ_num_enemy++;
		}
		if (EnemyEquip == 'C')
		{
			static_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()))->changeAttackPoint(200);
			auto changjian = Sprite::create("3.png");
			this->getChildByTag(666)->addChild(changjian);
			changjian->setPosition(320 + equ_num_enemy * 80, 140);
			equ_num_enemy++;
		}
		if (EnemyEquip == 'K')
		{
			static_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()))->changeDefensePoint(200);
			auto kaijia = Sprite::create("4.png");
			this->getChildByTag(666)->addChild(kaijia);
			kaijia->setPosition(320 + equ_num_enemy * 80, 140);
			equ_num_enemy++;
		}
		if (EnemyEquip == 'H')
		{
			static_cast<Hero*>(this->getChildByTag(601 - this->getMeFlag()))->changeMaxHealthPoint(100);
			auto hong = Sprite::create("5.png");
			this->getChildByTag(666)->addChild(hong);
			hong->setPosition(320 + equ_num_enemy * 80, 140);
			equ_num_enemy++;
		}
		IfEquipUpdate = 0;
	}
}

///////////////在此处定义装备查看/////////////////////////////////////////////////////////////////////////////
void GameScene::equipmentCheck()
{
	log("check equipment");
	if (this->isChecking())
	{
		this->setUnChecking();
		this->getChildByTag(666)->setVisible(false);
		//此时按p时已经在查看装备
		//按p的作用为关闭面板
		//设置面板为不可见
	}

	else if (!this->isChecking())
	{
		this->setChecking();
		this->getChildByTag(666)->setVisible(true);
		//此时按p为开启面板
		//设置面板为可见
	}
}

void GameScene::SendPosition(float dt)
{
	HeroPosition = (this->getChildByTag(this->getMeFlag()))->getPosition();
	Cli.MessageSending(FloatToChar(HeroPosition.x, HeroPosition.y));
}

void GameScene::GetAndMove(float dt)
{
	if (Position.x == 0 && Position.y == 0)
	{
		if (ID == 1)
		{
			(this->getChildByTag(601 - this->getMeFlag()))->setPosition(Player2StartPosition);
		}
		else
		{
			(this->getChildByTag(601 - this->getMeFlag()))->setPosition(Player1StartPosition);
		}
	}
	else
	{
		(this->getChildByTag(601 - this->getMeFlag()))->setPosition(Position.x, Position.y);
	}
}

void GameScene::Zhanji(float dt)
{
	//蓝色方战绩
	this->removeChildByTag(BlueScore);
	cocos2d::__String* m1 = cocos2d::__String::createWithFormat("%d", n_BlueDeath);
	auto mm1 = LabelTTF::create(m1->getCString(), "Arial", 36);
	mm1->setPosition(80, 850);
	this->addChild(mm1, 2, BlueScore);

	//红色方战绩
	this->removeChildByTag(RedScore);
	cocos2d::__String* m2 = cocos2d::__String::createWithFormat("%d", n_RedDeath);
	auto mm2 = LabelTTF::create(m2->getCString(), "Arial", 36);
	mm2->setPosition(150, 850);
	this->addChild(mm2, 2, RedScore);
}

void GameScene::MakeMoney(float dt)
{
	this->changeMeMoney(1);
}

void GameScene::checkExp(float dt)
{
	auto EXP = (ProgressTimer*)this->getChildByTag(Expbar);
	EXP->setScale(0.5);
	EXP->setPercentage(this->getMeExp() / 2);
}
