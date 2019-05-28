#include"HelloWorldScene.h"
#include"GameScene.h"
USING_NS_CC;

int cnt = 1;

bool Room::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite *bg = Sprite::create("bg.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Size size_back = bg->getContentSize();
	float scale_x = (float)visibleSize.width / (float)size_back.width;
	float scale_y = (float)visibleSize.height / (float)size_back.height;
	bg->setScale(scale_x, scale_y);
	this->addChild(bg);

	Sprite *Hero = Sprite::create("Hero.png");
	Hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 5);
	this->addChild(Hero);

	Sprite *ChooseHero_p1 = Sprite::create("ChooseHero.png");
	ChooseHero_p1->setPosition(Vec2(origin.x+visibleSize.width/7,origin.y+visibleSize.height*3/5));
	this->addChild(ChooseHero_p1);

	MenuItemImage *houyi = MenuItemImage::create("houyi.jpg", "houyi.jpg", CC_CALLBACK_1(Room::ChooseHero_h, this));
	houyi->setPosition(Vec2(origin.x, origin.y + visibleSize.height / 10));
	houyi->setAnchorPoint(Vec2(0.7,0.5));
	MenuItemImage *yase = MenuItemImage::create("yase.png", "yase.png", CC_CALLBACK_1(Room::ChooseHero_y, this));
	yase->setPosition(Vec2(origin.x-visibleSize.width/5,origin.y+visibleSize.height/10));
	MenuItemImage *daji = MenuItemImage::create("daji.png", "daji.png", CC_CALLBACK_1(Room::ChooseHero_d, this));
	daji->setPosition(Vec2(origin.x +visibleSize.width / 5, origin.y + visibleSize.height / 10));
	daji->setAnchorPoint(Vec2(1, 0.5));

	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(24);
	MenuItemFont *Back = MenuItemFont::create("Back", CC_CALLBACK_1(Room::menuBackToStart, this));
	MenuItemFont *Next = MenuItemFont::create("Next", CC_CALLBACK_1(Room::menuGoToGame, this));
	MenuItemFont *Add = MenuItemFont::create("Add", CC_CALLBACK_1(Room::menuClickToAdd, this));
	MenuItemFont *Player1 = MenuItemFont::create("Player1", CC_CALLBACK_1(Room::ChooosePlayer, this));
	
	Menu *menu = Menu::create(Player1,Back, Add, Next,houyi,yase,daji,NULL);
	Back->setPosition(Vec2(-150, -100));
	Add->setPosition(Vec2(0, -100));
	Next->setPosition(Vec2(150, -100));
	Player1->setPosition(Vec2(-160,90));
	this->addChild(menu, 1);

	return true;
}
void Room::menuBackToStart(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void Room::menuClickToAdd(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto Player2 = Label::createWithSystemFont("Player2", "Arial", 24);
	Player2->setPosition(Vec2(visibleSize.width-50,250));
	this->addChild(Player2);

	Sprite *ChooseHero_p2 = Sprite::create("ChooseHero.png");
	ChooseHero_p2->setPosition(Vec2(visibleSize.width - 50, 200));
	this->addChild(ChooseHero_p2);
}

void Room::menuGoToGame(Ref* pSender)
{
	auto gs = GameScene::createScene();
	Director::getInstance()->pushScene(gs);
	/*Director::getInstance()->end();*/
}

void Room::ChooseHero_h(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *houyi_p = Sprite::create("houyi.jpg");
	if (cnt == 1)
		houyi_p->setPosition(Vec2(80, 200)); else houyi_p->setPosition(Vec2(visibleSize.width - 50, 200));
	this->addChild(houyi_p);

}

void Room::ChooseHero_y(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *yase_p= Sprite::create("yase.png");
	if (cnt == 1)
		yase_p->setPosition(Vec2(80, 200)); else yase_p->setPosition(Vec2(visibleSize.width - 50, 200));
	this->addChild(yase_p);

}

void Room::ChooseHero_d(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *daji_p = Sprite::create("daji.png");
	if (cnt == 1)
		daji_p->setPosition(Vec2(80, 200)); else daji_p->setPosition(Vec2(visibleSize.width - 50, 200));
	this->addChild(daji_p);

}

void Room::ChooosePlayer(cocos2d::Ref* pSender)
{
	cnt = 3 - cnt;
}
