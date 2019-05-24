#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Hero.h"
#include "GameScene.h"
//#include "Hero.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	
	

	///////////////////////////////////////////

	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(20);

	MenuItemFont* backItem = MenuItemFont::create("back", CC_CALLBACK_1(StartScene::menuBackCallback, this));
	backItem->setPosition(origin.x + visibleSize.width-backItem->getContentSize().width/2, 
						  origin.y + backItem->getContentSize().height/2);

	MenuItemFont* starttestItem = MenuItemFont::create("starttest", CC_CALLBACK_1(StartScene::menuStarttestCallback, this));
	starttestItem->setPosition(origin.x + visibleSize.width/2,origin.y+visibleSize.height/2);


	auto menu = Menu::create(backItem, starttestItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,200);

	




	return true;
}


void StartScene::menuStarttestCallback(cocos2d::Ref* pSender)
{
	auto sc = GameScene::createScene();
	Director::getInstance()->replaceScene(sc);
}

void StartScene::menuBackCallback(cocos2d::Ref* pSender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}



