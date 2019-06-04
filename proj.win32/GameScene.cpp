#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "GameScene.h"
#include "RoomScene.h"


#include "Hero.h"

#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"
#include "HouyiWSkill.h"

#include "DajiHero.h"
#include "DajiNormalAttack.h"
#include "DajiQSkill.h"
#include "DajiWSkill.h"
#include "DajiESkill.h"

#include "YaseHero.h"
#include "YaseNormalAttack.h"
//修改技能范围时需要修改英雄头文件define中的参数

USING_NS_CC;
Vec2 position_last = Vec2(0, 0);
//英雄起始位置
//注意此处用数字表示////////////////////////////////////////////////////////////////////////////////////////////////////
Vec2 Player1StartPosition(250, 250);
Vec2 Player2StartPosition(1300, 800);

GameScene* GameScene::create(char meName, char otherName, bool isAI)
{
	//	log("create before if");
	GameScene* gameScene = new GameScene();

	gameScene->setMeHeroTag(meName);
	gameScene->setOtherHeroTag(otherName);
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
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//将物理世界的重力设为0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto gs = GameScene::create(meHero, otherHero, isAI);
	scene->addChild(gs);
	return scene;
}
//返回初始场景函数
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{

	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
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

	//游戏地图
	_tileMap = TMXTiledMap::create("Map.tmx");
	addChild(_tileMap, 0, 100);

	//初始化碰撞层
	_collidable = _tileMap->getLayer("Collidable");

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
	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(MeHeroTag));

	//注册键盘监听器
	//使用λ表达式
	//目前只实现了 Q W E A B P键按下时英雄做出响应

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
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
					target->setBuffTime(HouyiQSkillLastTime * target->getQSkillLevel());
					//该技能实现效果在HouyiHero update函数中实现
					target->setQSkillWaitTime(target->getQSkillCdTime());
					target->setHeroAfterShake(target->getQSkillAfterShake());

				}
			}

			//在此处发动亚瑟Q
			if (target->getHeroName() == 'H')
			{
				if (target->getQSkillWaitTime() <= 0.01)
				{

					//停止移动动作发动技能
					target->stopActionByTag(HeroMove);
					//发动q技能，持续时间内增加后羿攻击速度和移动速度
					target->setBuff(true);
					//持续时间5*q技能等级
					target->setBuffTime(YaseQSkillLastTime * target->getQSkillLevel());
					//该技能实现效果在HouyiHero update函数中实现
					target->setQSkillWaitTime(target->getQSkillCdTime());
					target->setHeroAfterShake(target->getQSkillAfterShake());
				}
			}
			break;
		}

		case EventKeyboard::KeyCode::KEY_W:
		{
			target->thisKeyPressed('W');
			break;
		}

		case EventKeyboard::KeyCode::KEY_E:
		{
			target->thisKeyPressed('E');
			break;
		}
		//暂定按P键实现查看装备功能
		case EventKeyboard::KeyCode::KEY_P:
		{
			target->thisKeyPressed('P');
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

	};
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
	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(MeHeroTag));

	//注册物理碰撞监听器
	auto contactListener = EventListenerPhysicsContact::create();



	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::contactBegin, this);


	contactListener->onContactPreSolve = [](PhysicsContact& contact, const PhysicsContactPreSolve& solve)
	{
		return true;
	};

	contactListener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};

	contactListener->onContactSeparate = [](PhysicsContact& contact)
	{

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


	//根据meHeroTag设置己方英雄精灵
	switch (this->getMeHeroTag())
	{

	case 'H':
	{
		static auto hero = HouyiHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		//log("mehero test mask %d", body->getContactTestBitmask());
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		hero->setPhysicsBody(body);
		hero->setPosition(Player1StartPosition);
		hero->setHuman();
		hero->setFlag(Player1);
		addChild(hero, 100, MeHeroTag);

		//该函数为计算冷却时间和攻击间隔的函数
		hero->schedule(schedule_selector(HouyiHero::buffUpdate), 1.0 / 60.0);
		hero->scheduleUpdate();
		break;
	}
	case 'Y':
	{
		auto hero = YaseHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		//log("mehero test mask %d", body->getContactTestBitmask());
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		hero->setPhysicsBody(body);
		hero->setPosition(Player1StartPosition);
		addChild(hero, 100, MeHeroTag);
		hero->setFlag(Player1);
		hero->setHuman();
		//该函数为计算冷却时间和攻击间隔的函数
		hero->scheduleUpdate();
		break;
	}

	case 'D':
	{
		static auto hero = DajiHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		//log("mehero test mask %d", body->getContactTestBitmask());
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		hero->setPhysicsBody(body);
		hero->setPosition(Player1StartPosition);
		hero->setHuman();
		hero->setFlag(Player1);
		addChild(hero, 100, MeHeroTag);

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
		body->setContactTestBitmask(OTHERUNITTEST);
		body->setCategoryBitmask(OTHERUNITCATEGORY);
		body->setCollisionBitmask(OTHERUNITCOLLISION);
		log("otherhero test mask %d", body->getContactTestBitmask());
		otherHero->setPhysicsBody(body);
		otherHero->setPosition(Player2StartPosition);
		addChild(otherHero, 100, this->getEnermyType());
		otherHero->setAI();
		otherHero->setFlag(Player2);
		otherHero->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag)));
		otherHero->scheduleUpdate();
		otherHero->schedule(schedule_selector(HouyiHero::buffUpdate), 1.0 / 60.0);
		break;
	}

	case 'D':
	{
		auto otherHero = DajiHero::create();
		auto body = PhysicsBody::createCircle(otherHero->getContentSize().width / 2);
		body->setContactTestBitmask(OTHERUNITTEST);
		body->setCategoryBitmask(OTHERUNITCATEGORY);
		body->setCollisionBitmask(OTHERUNITCOLLISION);
		log("otherhero test mask %d", body->getContactTestBitmask());
		otherHero->setPhysicsBody(body);
		otherHero->setPosition(Player2StartPosition);
		addChild(otherHero, 100, this->getEnermyType());
		otherHero->setAI();
		otherHero->setFlag(Player2);
		otherHero->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag)));
		otherHero->scheduleUpdate();
		otherHero->schedule(schedule_selector(HouyiHero::buffUpdate), 1.0 / 60.0);
		break;
	}

	case 'Y':
	{
		break;
	}



	default:break;
	}

	//设置返回初始场景的菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(20);
	MenuItemFont* backItem = MenuItemFont::create("back", CC_CALLBACK_1(GameScene::menuBackCallback, this));
	backItem->setPosition(origin.x + visibleSize.width - backItem->getContentSize().width / 2,
		origin.y + backItem->getContentSize().height / 2);

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 200);

	//装备商店
/*MenuItemImage *shop_xie = MenuItemImage::create("shop_xie.png", "shop_xie.png", CC_CALLBACK_1(GameScene::shop_xie, this));
shop_xie->setPosition(Vec2(0,75));
MenuItemImage *shop_shoutao = MenuItemImage::create("shop_shoutao.png", "shop_shoutao.png", CC_CALLBACK_1(GameScene::shop_shoutao, this));
shop_shoutao->setPosition(Vec2(0,45));
MenuItemImage *shop_changgong = MenuItemImage::create("shop_changgong.png", "shop_changgong.png", CC_CALLBACK_1(GameScene::shop_changgong, this));
shop_changgong->setPosition(Vec2(0,15));
MenuItemImage *shop_kaijia = MenuItemImage::create("shop_kaijia.png", "shop_kaijia.png", CC_CALLBACK_1(GameScene::shop_kaijia, this));
shop_kaijia->setPosition(Vec2(0,-15));
MenuItemImage *shop_hongshuijing = MenuItemImage::create("shop_hongshuijing.png", "shop_hongshuijing.png", CC_CALLBACK_1(GameScene::shop_hongshuijing, this));
shop_hongshuijing->setPosition(Vec2(0,-45));
MenuItemImage *shop_lanshuijing = MenuItemImage::create("shop_lanshuijing.png", "shop_lanshuijing.png", CC_CALLBACK_1(GameScene::shop_lanshuijing, this));
shop_lanshuijing->setPosition(Vec2(0,-75));
Menu *menu = Menu::create(shop_xie, shop_shoutao,shop_changgong,shop_kaijia,shop_hongshuijing,shop_lanshuijing, NULL);
this->addChild(menu,1);*/

//水晶
	Sprite *shuijing1 = Sprite::create("shuijing.png");
	shuijing1->setPosition(Vec2(50, 30));
	this->addChild(shuijing1);

	Sprite *shuijing2 = Sprite::create("shuijing2.png");
	shuijing2->setPosition(Vec2(430, 300));
	this->addChild(shuijing2);

	//防御塔
	Sprite *tower1 = Sprite::create("tower.png");
	tower1->setPosition(Vec2(155, 105));
	this->addChild(tower1);

	Sprite *tower2 = Sprite::create("tower.png");
	tower2->setPosition(Vec2(370, 270));
	this->addChild(tower2);
	this->schedule(schedule_selector(GameScene::watchMeAndOther), 1.0 / 60.0);
	return true;
}

//控制AI的函数
//by 王文政 2019年6月2日
void GameScene::watchMeAndOther(float dt)
{
	Hero* meHero = dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag));
	Hero* otherHero = dynamic_cast<Hero*>(this->getChildByTag(this->getEnermyType()));
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
				takeHouyiNormalAttack(otherHero, false, otherHeroPoint, meHeroPoint);
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
				takeHouyiWSkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W

			//判断并放大
			if (length <= HouyiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				takeHouyiESkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E

		}

		//如果AI控制亚瑟
		if (this->getOtherHeroTag() == 'Y')
		{

		}
		//如果AI控制妲己
		if (this->getOtherHeroTag() == 'D')
		{
			//判断并进行普攻
			if (length <= DajiNormalAttackRange && otherHero->getAttackWaitTime() <= 0.01)
			{
				takeDajiNormalAttack(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setAttackWaitTime(1.0 / otherHero->getAttackSpeed());
				otherHero->setHeroAfterShake(otherHero->getNormalAttackAfterShake());
			}//end 普攻
			//判断并Q技能
			if (length <= DajiQSkillRange && otherHero->getQSkillWaitTime() <= 0.01)
			{
				takeDajiQSkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setQSkillWaitTime(otherHero->getQSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getQSkillAfterShake());
			}//end Q
			//判断并W技能
			if (length <= DajiWSkillRange && otherHero->getWSkillWaitTime() <= 0.01)
			{
				takeDajiWSkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W
			//判断并放大
			if (length <= DajiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				takeDajiESkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E

		}
	}
}

//by 王文政 2019年5月20日
//λ表达式无法使用this，故单独把touchEnded函数拿出来写
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
					takeHouyiNormalAttack(target, true, heroPosition, touchPosition);
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
					takeHouyiWSkill(target, true, heroPosition, touchPosition);
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
					takeHouyiESkill(target, true, heroPosition, touchPosition);
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
					takeYaseNormalAttack(true, heroPosition, touchPosition);
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
				break;
			}

			case 'E':
			{
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
					takeDajiNormalAttack(target, true, heroPosition, touchPosition);
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
					takeDajiQSkill(target, true, heroPosition, touchPosition);
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
					takeDajiWSkill(target, true, heroPosition, touchPosition);
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
					takeDajiESkill(target, true, heroPosition, touchPosition);
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
	this->schedule(schedule_selector(GameScene::collision), 0.001f);
}

void GameScene::shop_xie(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GameScene::shop_shoutao(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GameScene::shop_changgong(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GameScene::shop_kaijia(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GameScene::shop_hongshuijing(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GameScene::shop_lanshuijing(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void GameScene::update(float dt)
{

}
//判断碰撞
void GameScene::collision(float dt)
{
	position_now = (this->getChildByTag(MeHeroTag))->getPosition();
	if (setPlayerPosition(position_now) == true)
	{
		(this->getChildByTag(MeHeroTag))->setPosition(position_last);
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

		log("contact");
	auto spriteA = (BasicSprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (BasicSprite*)contact.getShapeB()->getBody()->getNode();

	//	log("A %d ,B %d", spriteA->getTag(), spriteB->getTag());

	if (spriteA->getTag() == OtherSkillTag)
	{
		//此时A是敌方技能 B是我方单位
		auto otherSkill = static_cast<BasicSkill*>(spriteA);
		auto meHero = static_cast<Hero*>(spriteB);
		//己方单位受到伤害
		meHero->sufferDamage(otherSkill->getDamagePoint());
		//如果己方单位死亡
		//给对面英雄加经验和金币
		if (meHero->getHealthPoint() <= 0)
		{
			this->changeOtherExp(HeroExp);
			this->changeOtherMoney(HeroMoney);
		}
		//如果技能为打中就消失，则让技能消失
		if (otherSkill->shouldRemove())
		{
			otherSkill->removeFromParent();
			return false;
		}
	}
	if (spriteB->getTag() == OtherSkillTag)
	{
		//此时B是敌方技能 A是我方单位
		auto otherSkill = static_cast<BasicSkill*>(spriteB);
		auto meHero = static_cast<Hero*>(spriteA);
		meHero->sufferDamage(otherSkill->getDamagePoint());
		//如果己方单位死亡
		//给对面英雄加经验和金币
		if (meHero->getHealthPoint() <= 0)
		{
			this->changeOtherExp(HeroExp);
			this->changeOtherMoney(HeroMoney);
		}
		//如果技能为打中就消失，则让技能消失
		if (otherSkill->shouldRemove())
		{
			otherSkill->removeFromParent();
			return false;
		}
	}
	if (spriteA->getTag() == MeSkillTag)
	{
		//此时A是我方技能 B是敌方单位
		auto meSkill = static_cast<BasicSkill*>(spriteA);
		auto otherHero = static_cast<Hero*>(spriteB);
		otherHero->sufferDamage(meSkill->getDamagePoint());
		//如果敌方单位死亡
		//给我方英雄加经验和金币
		if (otherHero->getHealthPoint() <= 0)
		{
			this->changeMeExp(HeroExp);
			this->changeMeMoney(HeroMoney);
		}
		//如果技能为打中就消失，则让技能消失
		if (meSkill->shouldRemove())
		{
			meSkill->removeFromParent();
			return false;
		}
	}

	if (spriteB->getTag() == MeSkillTag)
	{
		//此时B是我方技能 A是敌方单位
		auto meSkill = static_cast<BasicSkill*>(spriteB);
		log("B is Meskill");
		auto otherHero = static_cast<Hero*>(spriteA);
		log("A is other hero");
		otherHero->sufferDamage(meSkill->getDamagePoint());
		//如果敌方单位死亡
		//给我方英雄加经验和金币
		if (otherHero->getHealthPoint() <= 0)
		{
			this->changeMeExp(HeroExp);
			this->changeMeMoney(HeroMoney);
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

void GameScene::takeHouyiNormalAttack(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	HouyiNormalAttack* houyiNormalAttack = HouyiNormalAttack::createTheAttack(hero);
	auto body = PhysicsBody::createBox(houyiNormalAttack->getContentSize());
	houyiNormalAttack->setPhysicsBody(body);
	//停止当前的移动进行普攻
	if (isMe)
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

void GameScene::takeHouyiWSkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	//先弄他十个箭头
					//修改箭头数记得修改for循环
	HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
	//中间的箭头单独创建
	houyiWSkill[0] = HouyiWSkill::createHouyiWSkill(hero);
	houyiWSkill[0]->takeHouyiWSkill(startPoint, targetPoint, 0);
	PhysicsBody* body[HouyiWSkillArrowNumber];
	body[0] = PhysicsBody::createBox(houyiWSkill[0]->getContentSize());
	houyiWSkill[0]->setPhysicsBody(body[0]);
	if (isMe)
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
		body[i] = PhysicsBody::createBox(houyiWSkill[i]->getContentSize());
		houyiWSkill[i]->setPhysicsBody(body[i]);
		if (isMe)
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
		body[i + 1] = PhysicsBody::createBox(houyiWSkill[i + 1]->getContentSize());
		houyiWSkill[i + 1]->setPhysicsBody(body[i + 1]);
		if (isMe)
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

void GameScene::takeHouyiESkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	HouyiESkill* bigBird = HouyiESkill::createHouyiESkill(hero);
	auto body = PhysicsBody::createCircle(bigBird->getContentSize().height / 2);

	bigBird->setPhysicsBody(body);
	bigBird->takeHouyiESkill(startPoint, targetPoint);
	if (isMe)
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

void GameScene::takeYaseNormalAttack(bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	YaseNormalAttack* yaseNormalAttack = YaseNormalAttack::createTheAttack();
	/*	auto body = PhysicsBody::createBox(yaseNormalAttack->getContentSize());
		if (isMe)
		{
			body->setContactTestBitmask(MESKILLMASK);
		}
		else
		{
			body->setContactTestBitmask(OTHERSKILLMASK);
		}
		body->setCategoryBitmask(CATEGORY);
		body->setCollisionBitmask(COLLISION);
		yaseNormalAttack->setPhysicsBody(body);
		*/
	yaseNormalAttack->takeYaseNormalAttack(startPoint, targetPoint);
	//把普攻显示在gamescene场景中
	this->addChild(yaseNormalAttack, 200, MeSkillTag);
	//当普攻精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
}

void GameScene::takeDajiNormalAttack(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	DajiNormalAttack* dajiNormalAttack = DajiNormalAttack::createTheAttack(hero);
	auto body = PhysicsBody::createBox(dajiNormalAttack->getContentSize());
	dajiNormalAttack->setPhysicsBody(body);
	//停止当前的移动进行普攻
	if (isMe)
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

void GameScene::takeDajiQSkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	DajiQSkill* bigMoon = DajiQSkill::createDajiQSkill(hero);
	auto body = PhysicsBody::createCircle(bigMoon->getContentSize().height / 2);

	bigMoon->setPhysicsBody(body);
	bigMoon->takeDajiQSkill(startPoint, targetPoint);
	if (isMe)
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

void GameScene::takeDajiWSkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	DajiWSkill* bigLove = DajiWSkill::createDajiWSkill(hero);
	auto body = PhysicsBody::createCircle(bigLove->getContentSize().height / 2);

	bigLove->setPhysicsBody(body);
	bigLove->takeDajiWSkill(startPoint, targetPoint);
	if (isMe)
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

void GameScene::takeDajiESkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	DajiESkill* bigBall = DajiESkill::createDajiESkill(hero);
	auto body = PhysicsBody::createCircle(bigBall->getContentSize().height / 2);

	bigBall->setPhysicsBody(body);
	bigBall->takeDajiESkill(startPoint, targetPoint);
	if (isMe)
	{
		this->addChild(bigBall, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(bigBall, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	log("%d", bigBall->getTag());
	log("%d", body->getContactTestBitmask());
	//把大招显示在gamescene场景中

	//当大招精灵运动一定距离时删除，该功能在HouyiESkill类的update函数中实现
}
