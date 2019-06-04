#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "GameScene.h"
#include "RoomScene.h"


#include "Hero.h"

#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"
#include "HouyiWSkill.h"

#include "YaseHero.h"
#include "YaseNormalAttack.h"
#include"client.h"
//修改技能范围时需要修改英雄头文件define中的参数

USING_NS_CC;
Vec2 position_last = Vec2(0, 0);
GameScene* GameScene::create(char meName, char otherName, bool isAI)
{
	log("create before if");
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
	log("%d", gameScene->getEnermyType());
	if (gameScene->init())
	{
		log("create after if");
		gameScene->autorelease();
		log("successful create");

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
	auto gs = GameScene::create(meHero, otherHero, isAI);

	//	log("gs get %c", gs->getMeHeroTag());


	return gs;
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
	Scene::onEnter();

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





}

void GameScene::onExit()
{
	//反正一定要加下边这句
	Scene::onExit();

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
	if (!Scene::init())
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
		hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		hero->setHuman();
		addChild(hero, 100, MeHeroTag);

		//该函数为计算冷却时间和攻击间隔的函数
		hero->scheduleUpdate();
		break;
	}
	case 'Y':
	{
		auto hero = YaseHero::create();
		hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		addChild(hero, 100, MeHeroTag);
		hero->setHuman();
		//该函数为计算冷却时间和攻击间隔的函数
		hero->scheduleUpdate();
		break;
	}

	case 'D':
	{
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
		otherHero->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height / 2);
		addChild(otherHero, 100, this->getEnermyType());
		otherHero->setAI();
		otherHero->AIcontrol(dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag)));
		otherHero->scheduleUpdate();
		break;
	}

	case 'D':
	{
		break;
	}

	case 'Y':
	{
		break;
	}



	default:break;
	}

	//获取位置发送给服务器
	/*this->schedule(schedule_selector(GameScene::get_position), 0.001f);*/
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
MenuItemImage *shop_xie = MenuItemImage::create("zhuangbei/xie.png", "zhuangbei/xie.png", CC_CALLBACK_1(GameScene::shop_xie, this));
shop_xie->setPosition(Vec2(-710,350));
MenuItemImage *shop_shoutao = MenuItemImage::create("zhuangbei/changjian.png", "zhuangbei/changjian.png", CC_CALLBACK_1(GameScene::shop_shoutao, this));
shop_shoutao->setPosition(Vec2(-710,280));
MenuItemImage *shop_changgong = MenuItemImage::create("zhuangbei/duanjian.png", "zhuangbei/duanjian.png", CC_CALLBACK_1(GameScene::shop_changgong, this));
shop_changgong->setPosition(Vec2(-710,210));
MenuItemImage *shop_kaijia = MenuItemImage::create("zhuangbei/kaijia.png", "zhuangbei/kaijia.png", CC_CALLBACK_1(GameScene::shop_kaijia, this));
shop_kaijia->setPosition(Vec2(-710,140));
MenuItemImage *shop_hongshuijing = MenuItemImage::create("zhuangbei/hongshuijing.png", "zhuangbei/hongshuijing.png", CC_CALLBACK_1(GameScene::shop_hongshuijing, this));
shop_hongshuijing->setPosition(Vec2(-710,70));
Menu *menu2 = Menu::create(shop_xie, shop_shoutao,shop_changgong,shop_kaijia,shop_hongshuijing, NULL);
this->addChild(menu2,300);

//水晶
	Sprite *shuijing1 = Sprite::create("shuijing.png");
	shuijing1->setPosition(Vec2(400,200));
	this->addChild(shuijing1,2);

	Sprite *shuijing2 = Sprite::create("shuijing2.png");
	shuijing2->setPosition(Vec2(1300,800));
	this->addChild(shuijing2,2);

	//防御塔
	Sprite *tower1 = Sprite::create("tower.png");
	tower1->setPosition(Vec2(550, 300));
	this->addChild(tower1,2);

	Sprite *tower2 = Sprite::create("tower.png");
	tower2->setPosition(Vec2(1200, 700));
	this->addChild(tower2,2);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::watchMeAndOther), 1.0 / 60.0);

	//左上角的战绩
	auto score_blue = LabelTTF::create("0 ", "Arial", 36);
	this->addChild(score_blue, 2);
	score_blue->setPosition(origin.x + 100, visibleSize.height-50);
	score_blue->setTag(BlueScore);
	auto vs = LabelTTF::create("vs", "Arial", 24);
	this->addChild(vs, 2);
	vs->setPosition(origin.x + 122, visibleSize.height-50);
	auto score_red = LabelTTF::create("0 ", "Arial", 36);
	this->addChild(score_red, 2);
	score_red->setPosition(origin.x + 150, visibleSize.height-50);
	score_blue->setTag(RedScore);

	this->schedule(schedule_selector(GameScene::updateScore), 0.001f);

	return true;
}

//控制AI的函数
//by 王文政 2019年6月2日
void GameScene::watchMeAndOther(float dt)
{
	Hero* meHero = dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag));
	Hero* otherHero = dynamic_cast<Hero*>(this->getChildByTag(this->getEnermyType()));

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
				HouyiNormalAttack* attack = HouyiNormalAttack::createTheAttack();
				//注意这里不要搞混顺序////////////////↓//////////////↓
				attack->takeHouyiNormalAttack(otherHeroPoint, meHeroPoint);
				this->addChild(attack, 200, OtherSkillTag);
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
				//先弄他几个箭头

				HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
				//中间的箭头单独创建
				houyiWSkill[0] = HouyiWSkill::createHouyiWSkill();
				houyiWSkill[0]->takeHouyiWSkill(otherHeroPoint, meHeroPoint, 0);
				this->addChild(houyiWSkill[0], 200, OtherSkillTag);
				//两边的箭头成对创建
				for (int i = 1; i < HouyiWSkillArrowNumber; i += 2)
				{
					houyiWSkill[i] = HouyiWSkill::createHouyiWSkill();
					houyiWSkill[i]->takeHouyiWSkill(otherHeroPoint, meHeroPoint, i * 3.14 / 30);//根据弧度制
					houyiWSkill[i + 1] = HouyiWSkill::createHouyiWSkill();//i乘的数为两箭头夹角
					houyiWSkill[i + 1]->takeHouyiWSkill(otherHeroPoint, meHeroPoint, -i * 3.14 / 30);
					//把箭头显示在gamescene场景中
					this->addChild(houyiWSkill[i], 200, OtherSkillTag);
					this->addChild(houyiWSkill[i + 1], 200, OtherSkillTag);
				}

				//当普攻精灵运动一定距离时删除，该功能在HouyiWSkill类的update函数中实现
				//重置W等待时间
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W

			//判断并放大
			if (length <= HouyiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				HouyiESkill* bigBird = HouyiESkill::createHouyiESkill();

				//停止当前的移动进行大招
				bigBird->takeHouyiESkill(otherHeroPoint, meHeroPoint);
				//把大招显示在gamescene场景中
				this->addChild(bigBird, 200, OtherSkillTag);
				//当大招精灵运动一定距离时删除，该功能在HouyiESkill类的update函数中实现
				//重置大招等待时间
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
					HouyiNormalAttack* houyiNormalAttack = HouyiNormalAttack::createTheAttack();
					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);
					houyiNormalAttack->takeHouyiNormalAttack(target);
					//把普攻显示在gamescene场景中
					this->addChild(houyiNormalAttack, 200, MeSkillTag);
					//当普攻精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
					//重置平A等待时间
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
					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);

					//先弄他十个箭头
					//修改箭头数记得修改for循环
					HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
					//中间的箭头单独创建
					houyiWSkill[0] = HouyiWSkill::createHouyiWSkill();
					houyiWSkill[0]->takeHouyiWSkill(target, 0);
					this->addChild(houyiWSkill[0], 200, MeSkillTag);
					//两边的箭头成对创建
					for (int i = 1; i < HouyiWSkillArrowNumber; i += 2)
					{
						houyiWSkill[i] = HouyiWSkill::createHouyiWSkill();
						houyiWSkill[i]->takeHouyiWSkill(target, i * 3.14 / 30);//根据弧度制
						houyiWSkill[i + 1] = HouyiWSkill::createHouyiWSkill();//i乘的数为两箭头夹角
						houyiWSkill[i + 1]->takeHouyiWSkill(target, -i * 3.14 / 30);
						//把箭头显示在gamescene场景中
						this->addChild(houyiWSkill[i], 200, MeSkillTag);
						this->addChild(houyiWSkill[i + 1], 200, MeSkillTag);
					}

					//当普攻精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
					//重置平A等待时间
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}

			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					HouyiESkill* bigBird = HouyiESkill::createHouyiESkill();

					//停止当前的移动进行大招
					target->stopActionByTag(HeroMove);
					bigBird->takeHouyiESkill(target);

					//把大招显示在gamescene场景中
					this->addChild(bigBird, 200, MeSkillTag);
					//当大招精灵运动一定距离时删除，该功能在HouyiESkill类的update函数中实现
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
					YaseNormalAttack* yaseNormalAttack = YaseNormalAttack::createTheAttack();

					//停止当前的移动进行普攻
					target->stopActionByTag(HeroMove);
					yaseNormalAttack->takeYaseNormalAttack(heroPosition, touchPosition);
					//把普攻显示在gamescene场景中
					this->addChild(yaseNormalAttack, 200, MeSkillTag);
					//当普攻精灵运动一定距离时删除，该功能在HouyiNormalAttack类的update函数中实现
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

	}
	this->schedule(schedule_selector(GameScene::collision), 0.001f);
}



void GameScene::shop_xie(cocos2d::Ref* pSender)
{
	//setMoney(金币-300)
	//移速增加
	//装备栏里增加鞋子
	Director::getInstance()->end();
}

void GameScene::shop_shoutao(cocos2d::Ref* pSender)
{
	//setMoney(金币-300)
	//增加攻击力和法强
	//装备栏里增加手套
	Director::getInstance()->end();
}

void GameScene::shop_changgong(cocos2d::Ref* pSender)
{
	//setMoney（金币-300）
	//增加攻速
	//装备栏里增加长弓
	Director::getInstance()->end();
}

void GameScene::shop_kaijia(cocos2d::Ref* pSender)
{
	//setMoney（金币-300）
	//增加防御
	//装备栏里增加铠甲
	Director::getInstance()->end();
}

void GameScene::shop_hongshuijing(cocos2d::Ref* pSender)
{
	//setMoney（金币-300）
	//增加血量
	//装备栏里增加红水晶
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

void GameScene::updateScore(float dt)
{
	
}

//void GameScene::get_position(float dt)
//{
//	Client a;
//	position_client = (this->getChildByTag(MeHeroTag))->getPosition();
//	a.SendMes(FloatToChar(position_client.x, position_client.y));
//}