#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}
//���س�ʼ��������
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}

//onEnter����
//�ڸú�����ע�������
//�ڸú������屳��֮�಻��Ҫ���в�����ֻ�����һ�εľ���

//void GameScene::onEnter()
//{
//	//��onEnter������д��Scene���onEnter����
//	//onExit����Ҳ��һ������
//	//onEnter������һ��һ��Ҫ�����
//	Scene::onEnter();
//
//	//ע����������
//	//ʹ�æ˱��ʽ
//	//Ŀǰֻʵ����ʹӢ��������ɿ�ʱ  �����ƶ��ٶ� �ƶ������λ�õĹ���
//	//���������Ӧ���Ҽ��Ҳ���
//	auto mouseListener = EventListenerTouchOneByOne::create();
//	//���ʱ
//	//ע��ú�����һ��bool����
//	mouseListener->onTouchBegan = [](Touch* touch, Event* event)
//	{
//
//		return true;
//	};
//
//	//�����δ�ɿ����ƶ����ʱ
//	mouseListener->onTouchMoved = [](Touch* touch, Event* event)
//	{
//
//	};
//
//	//�ɿ�ʱ
//	mouseListener->onTouchEnded = [](Touch* touch, Event* event)
//	{
//		//ͨ����Ӣ�����õı�ǩ��ȡӢ��
//		//����ԭ���ǻ�ȡ�¼����󶨵ľ���
//		//����ѧ��һ����Ҳ��֪����ʲôԭ��
//		//init������addChild(hero,20,tag),���е�tag���Ǹ�Ӣ�۵ı�ǩ
//		auto target = static_cast<Hero*>(event->getCurrentTarget());
//
//		//��ȡ�ɿ����ʱ�����λ��
//		Vec2 touchPosition = touch->getLocation();
//		//��ȡӢ�۵�ǰλ��
//		Vec2 heroPosition = target->getPosition();
//		//Ӣ����õ��˶�
//
//		//��ȡӢ��Ŀǰ���ٶ�
//		float heroSpeed = target->getMoveSpeed();
//		//��ȡ���λ��
//		Vec2 relativePosition = heroPosition - touchPosition;
//		//��ȡ���λ�õ�ģ��
//		float distanceSquare = relativePosition.x*relativePosition.x + relativePosition.y*relativePosition.y;
//		float distance = sqrt(distanceSquare);
//		//�����˶����õ������ʱ��
//		float timeNeeded = distance / heroSpeed;
//
//		//��ֹͣ��ǰ���˶����������������˶��ĵ���
//		target->stopActionByTag(HeroMove);
//
//		//����һ���˶�����moveAction���˶���ָ������touchPosition
//		FiniteTimeAction * moveAction = (FiniteTimeAction*)target->runAction(MoveTo::create(timeNeeded, touchPosition));
//		//�������������tag ----> HeroMove
//		moveAction->setTag(HeroMove);
//
//
//
//	};
//
//	//��û�¼���ʹ���Ĳ�����������һ��
//	mouseListener->setSwallowTouches(true);
//
//	//���ǿ���������ѧһ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////////    ���������tag
//	EventDispatcher *mouseDispatcher = Director::getInstance()->getEventDispatcher(); //     ��
//	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(Hero_Tag));
//
//
//	//ע����̼�����
//	//ʹ�æ˱��ʽ
//	//Ŀǰֻʵ���� Q W E A������ʱӢ��������Ӧ��S�����������Ե�
//
//	auto keyboardListener = EventListenerKeyboard::create();
//	keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
//	{
//		//����tag��ȡӢ��
//		auto target = static_cast<Hero*>(event->getCurrentTarget());
//		switch (keyCode)
//		{
//
//		case EventKeyboard::KeyCode::KEY_Q:
//		{
//			target->changeMoveSpeed(50);
//			break;
//		}
//
//		case EventKeyboard::KeyCode::KEY_W:
//		{
//			break;
//		}
//
//		case EventKeyboard::KeyCode::KEY_E:
//		{
//			break;
//		}
//
//		case EventKeyboard::KeyCode::KEY_A:
//		{
//			break;
//		}
//		default:break;
//
//		}
//	};
//	keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
//	{
//
//	};
//	//��֪���ò�����û�¼���Ҳ��֪����ô���ü�����û
//	//����ûд
//	//��Ҳ��֪������Ҳ������
//
//	//������������������ѧһ��һ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////    ���������tag
//	EventDispatcher *keyboardDispatcher = Director::getInstance()->getEventDispatcher();//       ��
//	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(Hero_Tag));
//}
//
//void Game::onExit()
//{
//	//	����һ��Ҫ���±����
//	Scene::onExit();
//
//	//	��onExit������ע��������
//	//	������
//	//	��֪����Ū��ʲôbug//////////////////////////////////////////////////////////////////////////////////////////////////
//	//	����Ŀǰ��ע��û��
//
//}


bool GameScene::init()
{
	/////////////////////////////
	// 1. super init first
	//��֪��ΪʲôҪ�ӵ��ǻ��Ǽ���
	//���ܸ�����û�гɹ������й�
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	////����Ӣ�۾���
	//auto hero = Hero::create();
	//hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	//addChild(hero, 100, Hero_Tag);

	////���÷��س�ʼ�����Ĳ˵�
	//MenuItemFont::setFontName("Arial");
	//MenuItemFont::setFontSize(20);
	//MenuItemFont* backItem = MenuItemFont::create("back", CC_CALLBACK_1(GameScene::menuBackCallback, this));
	//backItem->setPosition(origin.x + visibleSize.width - backItem->getContentSize().width / 2,
	//	origin.y + backItem->getContentSize().height / 2);

	//auto menu = Menu::create(backItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 200);


	//��Ϸ��ͼ
	Sprite *Map = Sprite::create("Map.jpg");
	Map->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	Size size_back = Map->getContentSize();
	float scale_x = (float)visibleSize.width / (float)size_back.width;
	float scale_y = (float)visibleSize.height / (float)size_back.height;
	Map->setScale(scale_x, scale_y);
	this->addChild(Map);


	//װ���̵�
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

	//ˮ��
	Sprite *shuijing1 = Sprite::create("shuijing.png");
	shuijing1->setPosition(Vec2(50, 30));
	this->addChild(shuijing1);

	Sprite *shuijing2 = Sprite::create("shuijing2.png");
	shuijing2->setPosition(Vec2(430, 300));
	this->addChild(shuijing2);

	//������
	Sprite *tower1 = Sprite::create("tower.png");
	tower1->setPosition(Vec2(155,105));
	this->addChild(tower1);

	Sprite *tower2 = Sprite::create("tower.png");
	tower2->setPosition(Vec2(370, 270));
	this->addChild(tower2);

	/*Sprite *houyi = Sprite::create("houyi.jpg");
	houyi->setPosition(Vec2(50, 30));
	this->addChild(houyi);
	CCMoveTo *moveTo = CCMoveTo::create(6, Vec2(430, 300));*/

	
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

void GameScene::Update(float dt)
{
	Sprite *houyi = Sprite::create("houyi.jpg");
	houyi->setPosition(Vec2(50, 30));
	this->addChild(houyi);
	CCMoveTo *moveTo = CCMoveTo::create(10, Vec2(430, 300));
	houyi->runAction(moveTo);
}