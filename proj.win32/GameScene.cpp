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
//���س�ʼ��������
void GameScene::menuBackCallback(cocos2d::Ref* pSender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}

//onEnter����
//�ڸú�����ע�������
//�ڸú������屳��֮�಻��Ҫ���в�����ֻ�����һ�εľ���

void GameScene::onEnter()
{
	//��onEnter������д��Scene���onEnter����
	//onExit����Ҳ��һ������
	//onEnter������һ��һ��Ҫ�����
	Scene::onEnter();
	
	//ע����������
	//ʹ�æ˱��ʽ
	//Ŀǰֻʵ����ʹӢ��������ɿ�ʱ  �����ƶ��ٶ� �ƶ������λ�õĹ���
	//���������Ӧ���Ҽ��Ҳ���
	auto mouseListener = EventListenerTouchOneByOne::create();													
	//���ʱ
	//ע��ú�����һ��bool����
	mouseListener->onTouchBegan = [](Touch* touch , Event* event) 
	{
		
		return true;
	};

	//�����δ�ɿ����ƶ����ʱ
	mouseListener->onTouchMoved = [](Touch* touch , Event* event)
	{

	};

	//�ɿ�ʱ
	mouseListener->onTouchEnded = [](Touch* touch , Event* event)
	{
		//ͨ����Ӣ�����õı�ǩ��ȡӢ��
		//����ԭ���ǻ�ȡ�¼����󶨵ľ���
		//����ѧ��һ����Ҳ��֪����ʲôԭ��
		//init������addChild(hero,20,tag),���е�tag���Ǹ�Ӣ�۵ı�ǩ
		auto target = static_cast<Hero*>(event->getCurrentTarget());

		//��ȡ�ɿ����ʱ�����λ��
		Vec2 touchPosition = touch->getLocation();
		//��ȡӢ�۵�ǰλ��
		Vec2 heroPosition = target->getPosition();
		//Ӣ����õ��˶�

		//��ȡӢ��Ŀǰ���ٶ�
		float heroSpeed = target->getMoveSpeed();
		//��ȡ���λ��
		Vec2 relativePosition = heroPosition - touchPosition;
		//��ȡ���λ�õ�ģ��
		float distanceSquare = relativePosition.x*relativePosition.x + relativePosition.y*relativePosition.y;
		float distance = sqrt(distanceSquare);
		//�����˶����õ������ʱ��
		float timeNeeded = distance / heroSpeed;

		//��ֹͣ��ǰ���˶����������������˶��ĵ���
		target->stopActionByTag(HeroMove);

		//����һ���˶�����moveAction���˶���ָ������touchPosition
		FiniteTimeAction * moveAction =(FiniteTimeAction*)target->runAction(MoveTo::create(timeNeeded,touchPosition));
		//�������������tag ----> HeroMove
		moveAction->setTag(HeroMove);



	};

	//��û�¼���ʹ���Ĳ�����������һ��
	mouseListener->setSwallowTouches(true);

	//���ǿ���������ѧһ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////////    ���������tag
	EventDispatcher *mouseDispatcher = Director::getInstance()->getEventDispatcher(); //     ��
	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(Hero_Tag));


	//ע����̼�����
	//ʹ�æ˱��ʽ
	//Ŀǰֻʵ���� Q W E A������ʱӢ��������Ӧ��S�����������Ե�

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) 
	{
		//����tag��ȡӢ��
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
	//��֪���ò�����û�¼���Ҳ��֪����ô���ü�����û
	//����ûд
	//��Ҳ��֪������Ҳ������

	//������������������ѧһ��һ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////    ���������tag
	EventDispatcher *keyboardDispatcher = Director::getInstance()->getEventDispatcher();//       ��
	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(Hero_Tag));
}

void GameScene::onExit()
{
	//����һ��Ҫ���±����
	Scene::onExit();
	
	//��onExit������ע��������
	//������
	//��֪����Ū��ʲôbug//////////////////////////////////////////////////////////////////////////////////////////////////
	//����Ŀǰ��ע��û��
	
}

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

	//����Ӣ�۾���
	auto hero = Hero::create();
	hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(hero, 100, Hero_Tag);

	//���÷��س�ʼ�����Ĳ˵�
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
