#include "RoomScene.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;

Scene* RoomScene::createScene()
{
	return RoomScene::create();
}

bool RoomScene::init()
{
	log("RoomScene init");
	if (!Scene::create())
	{
		log("false");
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Ĭ����ѡ�񼺷�Ӣ��
	this->setFlag(MeFlag);
	//��Ĭ�ϵз���human
	this->setHuman();
	//���ñ���
	Sprite *bg = Sprite::create("RoomSceneBackground.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Size size_back = bg->getContentSize();
	float scale_x = (float)visibleSize.width / (float)size_back.width;
	float scale_y = (float)visibleSize.height / (float)size_back.height;
	bg->setScale(scale_x, scale_y);
	this->addChild(bg,-1);

	//����player1�İ׿�
	Sprite *player1 = Sprite::create("WhiteImage.png");
	player1->setPosition(origin.x + visibleSize.width / 5.0, origin.y + visibleSize.height / 3 * 2);
	this->addChild(player1,1);

	//����player2�İ׿�
	Sprite *player2 = Sprite::create("WhiteImage.png");
	player2->setPosition(origin.x + visibleSize.width / 5.0*4.0, origin.y + visibleSize.height / 3.0*2.0);
	this->addChild(player2, 1);

	

	//ѡ��Ӣ�۲˵�
	MenuItemImage *houyi = MenuItemImage::create("houyi.jpg", "houyi.jpg", CC_CALLBACK_1(RoomScene::ChooseHero_h, this));
	houyi->setPosition(origin.x + visibleSize.width / 3.0, origin.y + visibleSize.height / 5.0);

	MenuItemImage *yase = MenuItemImage::create("yase.png", "yase.png", CC_CALLBACK_1(RoomScene::ChooseHero_y, this));
	yase->setPosition(Vec2(origin.x + visibleSize.width / 2.0, origin.y + visibleSize.height / 5.0));

	MenuItemImage *daji = MenuItemImage::create("daji.png", "daji.png", CC_CALLBACK_1(RoomScene::ChooseHero_d, this));
	daji->setPosition(Vec2(origin.x + visibleSize.width / 3.0 * 2.0, origin.y + visibleSize.height / 5.0));
	

	
	//���õ�����س�ʼҳ��˵� ׼���˵� ����˻��˵�
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(100);

	MenuItemFont *back = MenuItemFont::create("Back", CC_CALLBACK_1(RoomScene::menuBackToStart, this));
	back->setPosition(origin.x + visibleSize.width - back->getContentSize().width / 2,
					  origin.y + back->getContentSize().height / 2);

	MenuItemFont *ready = MenuItemFont::create("Ready", CC_CALLBACK_1(RoomScene::menuReadyCallback, this));
	ready->setPosition(origin.x + visibleSize.width / 2.0, origin.y + visibleSize.height / 3.0);

	MenuItemFont *addAI = MenuItemFont::create("AddAI", CC_CALLBACK_1(RoomScene::menuClickToAddAI, this));
	addAI->setPosition(origin.x + visibleSize.width / 5.0*4.0, 
					   origin.y + visibleSize.height / 3.0*2.0 + player2->getContentSize().height);

	MenuItemFont *addMyHero = MenuItemFont::create("AddMyHero", CC_CALLBACK_1(RoomScene::menuClickToAddMyHero, this));
	addMyHero->setPosition(origin.x + visibleSize.width / 5.0, 
					   origin.y + visibleSize.height / 3.0*2.0 + player1->getContentSize().height);

	Menu *menu = Menu::create(back, ready, addAI, addMyHero, houyi, daji, yase, NULL);
	menu->setPosition(Vec2::ZERO);
//	log("%f,%f", back->getPosition().x, back->getPosition().y);
	this->addChild(menu,1);

	return true;
}

void RoomScene::menuReadyCallback(cocos2d::Ref* pSender)
{
	log("ready get %c,%c\n", this->getMeHeroName(), this->getOtherHeroName());

	if (this->getMeHeroName() != '\0' && this->getOtherHeroName() != '\0')
	{
		auto gs = GameScene::createScene(this->getMeHeroName(),this->getOtherHeroName(),this->isAI());
		Director::getInstance()->replaceScene(gs);
	}
	
}

void RoomScene::menuBackToStart(Ref* pSender)
{
	auto sc = HelloWorld::create();
	Director::getInstance()->replaceScene(sc);
}

//ѡ�����
void RoomScene::ChooseHero_h(cocos2d::Ref* pSender)
{
	cocos2d::log("HHHH");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pic = Sprite::create("houyi.jpg");
	int flag = this->getFlag();

	//������Լ�ѡӢ��
	if (flag == MeFlag)
	{
		pic->setPosition(origin.x + visibleSize.width / 5.0, origin.y + visibleSize.height / 3 * 2);
		this->setMeHeroName('H');
	}
	//��AIѡӢ��
	else if (flag == OtherFlag)
	{
		pic->setPosition(origin.x + visibleSize.width / 5.0*4.0, origin.y + visibleSize.height / 3.0*2.0);
		this->setOtherHeroName('H');
	}
	this->addChild(pic, 2);
}

//ѡ����ɪ
void RoomScene::ChooseHero_y(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pic = Sprite::create("yase.png");
	int flag = this->getFlag();

	//������Լ�ѡӢ��
	if (flag == MeFlag)
	{
		pic->setPosition(origin.x + visibleSize.width / 5.0, origin.y + visibleSize.height / 3 * 2);
		this->setMeHeroName('Y');
	}
	//��AIѡӢ��
	else if (flag == OtherFlag)
	{
		pic->setPosition(origin.x + visibleSize.width / 5.0*4.0, origin.y + visibleSize.height / 3.0*2.0);
		this->setOtherHeroName('Y');
	}
	this->addChild(pic, 2);
}

//ѡ��槼�
void RoomScene::ChooseHero_d(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pic = Sprite::create("daji.png");
	int flag = this->getFlag();

	//������Լ�ѡӢ��
	if (flag == MeFlag)
	{
		pic->setPosition(origin.x + visibleSize.width / 5.0, origin.y + visibleSize.height / 3 * 2);
		this->setMeHeroName('D');
	}
	//��AIѡӢ��
	else if (flag == OtherFlag)
	{
		pic->setPosition(origin.x + visibleSize.width / 5.0*4.0, origin.y + visibleSize.height / 3.0*2.0);
		this->setOtherHeroName('D');
	}
	this->addChild(pic, 2);
}
void RoomScene::menuClickToAddAI(Ref* pSender)
{
	this->setFlag(OtherFlag);
	this->setAI();
	log("flag is %d", this->getFlag());
}

void RoomScene::menuClickToAddMyHero(cocos2d::Ref* pSender)
{
	this->setFlag(MeFlag);
}






