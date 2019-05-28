#include"HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"RoomScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(36);
	MenuItemFont *Start = MenuItemFont::create("Start", CC_CALLBACK_1(HelloWorld::menuOnClick, this));
	MenuItemFont *Exit = MenuItemFont::create("Exit", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	Menu* menu = Menu::create(Start, Exit, NULL);
	Start->setPosition(Vec2(origin.x- visibleSize.width / 4,origin.y- visibleSize.height / 4));
	Exit->setPosition(Vec2(origin.x+ visibleSize.width / 4,origin.y- visibleSize.height / 4));
	this->addChild(menu,1);

	Sprite *bg = Sprite::create("background.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Size size_back = bg->getContentSize();
	float scale_x = (float)visibleSize.width / (float)size_back.width;
	float scale_y = (float)visibleSize.height / (float)size_back.height;
	bg->setScale(scale_x, scale_y);
	this->addChild(bg);
 
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void HelloWorld::menuOnClick(Ref* pSender)
{
	auto rs = Room::createScene();
	Director::getInstance()->pushScene(rs);
}