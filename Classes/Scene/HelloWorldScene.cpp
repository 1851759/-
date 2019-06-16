#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"RoomScene.h"
#include"CrystalTower.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}



	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("123.mp3", true);


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	if (over == 0)
	{
		MenuItemFont::setFontName("Arial");
		MenuItemFont::setFontSize(100);
		auto startItem = MenuItemFont::create("start", CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
		startItem->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4);

		auto menu = Menu::create(closeItem, startItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 200);

		Sprite *bg = Sprite::create("background.jpg");
		bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		Size size_back = bg->getContentSize();
		float scale_x = (float)visibleSize.width / (float)size_back.width;
		float scale_y = (float)visibleSize.height / (float)size_back.height;
		bg->setScale(scale_x, scale_y);
		this->addChild(bg);
	}
	else
	{
		if (victory)
		{
			auto end = LabelTTF::create("Game will end in 5 sec", "Arial", 40);
			end->setPosition(800, 300);
			this->addChild(end, 200);
			auto victory = Sprite::create("VICTORY.png");
			victory->setPosition(800, 450);
			this->addChild(victory, 200);
			this->scheduleOnce(schedule_selector(HelloWorld::close), 5);
		}
		else
		{
			auto end = LabelTTF::create("Game will end in 5 sec", "Arial", 40);
			end->setPosition(800, 300);
			this->addChild(end, 200);
			auto defeat = Sprite::create("DEFEAT.png");
			defeat->setPosition(800, 450);
			this->addChild(defeat, 200);
			this->scheduleOnce(schedule_selector(HelloWorld::close), 5);
		}
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void HelloWorld::menuStartCallback(cocos2d::Ref* pSender)
{
	auto sc = RoomScene::createScene();
	Director::getInstance()->replaceScene(sc);
}

void HelloWorld::close(float dt)
{
	Director::getInstance()->end();
}