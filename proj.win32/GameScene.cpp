#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"
#include "GameScene.h"
#include "Hero.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
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

void GameScene::onEnter()
{
	//该onEnter函数重写了Scene类的onEnter函数
	//onExit函数也是一个道理
	//onEnter函数第一行一定要加这句
	Scene::onEnter();
	
	//注册鼠标监听器
	//使用λ表达式
	//目前只实现了使英雄在鼠标松开时  根据移动速度 移动到鼠标位置的功能
	//根据左键响应，右键我不会
	auto mouseListener = EventListenerTouchOneByOne::create();													
	//点击时
	//注意该函数是一个bool类型
	mouseListener->onTouchBegan = [](Touch* touch , Event* event) 
	{
		
		return true;
	};

	//点击后未松开并移动鼠标时
	mouseListener->onTouchMoved = [](Touch* touch , Event* event)
	{

	};

	//松开时
	mouseListener->onTouchEnded = [](Touch* touch , Event* event)
	{
		//通过给英雄设置的标签获取英雄
		//书上原话是获取事件所绑定的精灵
		//很玄学的一步我也不知道是什么原理
		//init函数中addChild(hero,20,tag),其中的tag就是该英雄的标签
		auto target = static_cast<Hero*>(event->getCurrentTarget());

		//获取松开鼠标时的鼠标位置
		Vec2 touchPosition = touch->getLocation();
		//获取英雄当前位置
		Vec2 heroPosition = target->getPosition();
		//英雄向该点运动

		//获取英雄目前的速度
		float heroSpeed = target->getMoveSpeed();
		//获取相对位置
		Vec2 relativePosition = heroPosition - touchPosition;
		//获取相对位置的模长
		float distanceSquare = relativePosition.x*relativePosition.x + relativePosition.y*relativePosition.y;
		float distance = sqrt(distanceSquare);
		//计算运动到该点所需的时间
		float timeNeeded = distance / heroSpeed;

		//先停止当前的运动动作，否则会造成运动的叠加
		target->stopActionByTag(HeroMove);

		//定义一个运动动作moveAction，运动到指定坐标touchPosition
		FiniteTimeAction * moveAction =(FiniteTimeAction*)target->runAction(MoveTo::create(timeNeeded,touchPosition));
		//给这个动作设置tag ----> HeroMove
		moveAction->setTag(HeroMove);



	};

	//吞没事件，使鼠标的操作不传给下一层
	mouseListener->setSwallowTouches(true);

	//又是看不懂的玄学一步，通过这步给鼠标监听器绑定英雄的tag/////////////////////////////////    ↓这个就是tag
	EventDispatcher *mouseDispatcher = Director::getInstance()->getEventDispatcher(); //     ↓
	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(Hero_Tag));


	//注册键盘监听器
	//使用λ表达式
	//目前只实现了 Q W E A键按下时英雄做出响应，S键是用来测试的

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) 
	{
		//根据tag获取英雄
		auto target = static_cast<Hero*>(event->getCurrentTarget());
		switch (keyCode)
		{
		
		case EventKeyboard::KeyCode::KEY_Q :
			{
			target->changeMoveSpeed(50);
			break;
			}

		case EventKeyboard::KeyCode::KEY_W:
		{
			break;
		}

		case EventKeyboard::KeyCode::KEY_E:
		{
			break;
		}

		case EventKeyboard::KeyCode::KEY_A:
		{
			break;
		}
		default:break;
			
		}
	};
	keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
	{

	};
	//不知道该不该吞没事件，也不知道怎么设置键盘吞没
	//书上没写
	//咱也不知道，咱也不敢问

	//跟鼠标监听看不懂的玄学一步一样，通过这步给鼠标监听器绑定英雄的tag/////////////////////////////    ↓这个就是tag
	EventDispatcher *keyboardDispatcher = Director::getInstance()->getEventDispatcher();//       ↓
	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(Hero_Tag));
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

	//设置英雄精灵
	auto hero = Hero::create();
	hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(hero, 100, Hero_Tag);

	//设置返回初始场景的菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(20);
	MenuItemFont* backItem = MenuItemFont::create("back", CC_CALLBACK_1(GameScene::menuBackCallback, this));
	backItem->setPosition(origin.x + visibleSize.width - backItem->getContentSize().width / 2,
		origin.y + backItem->getContentSize().height / 2);

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 200);

	return true;
}
