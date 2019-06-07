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
#include"YaseESkill.h"
#include"YaseWSkill.h"


#include "DajiHero.h"
//�޸ļ��ܷ�Χʱ��Ҫ�޸�Ӣ��ͷ�ļ�define�еĲ���

USING_NS_CC;
Vec2 position_last = Vec2(0, 0);
//Ӣ����ʼλ��
//ע��˴������ֱ�ʾ////////////////////////////////////////////////////////////////////////////////////////////////////
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
	//�����������������Ϊ0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto gs = GameScene::create(meHero, otherHero, isAI);
	scene->addChild(gs);
	return scene;
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

//by ������ 2019��5��27��
void GameScene::onEnter()
{
	//��onEnter������д��Scene���onEnter����
	//onExit����Ҳ��һ������
	//onEnter������һ��һ��Ҫ�����
	Layer::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��Ϸ��ͼ
	_tileMap = TMXTiledMap::create("Map.tmx");
	addChild(_tileMap, 0, 100);

	//��ʼ����ײ��
	_collidable = _tileMap->getLayer("Collidable");

	//ע����������
	//ʹ�æ˱��ʽ
	//Ŀǰֻʵ����ʹӢ��������ɿ�ʱ  �����ƶ��ٶ� �ƶ������λ�õĹ���
	//���������Ӧ���Ҽ��Ҳ���
	auto mouseListener = EventListenerTouchOneByOne::create();
	//���ʱ
	//ע��ú�����һ��bool����
	mouseListener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};

	//�����δ�ɿ����ƶ����ʱ
	mouseListener->onTouchMoved = [](Touch* touch, Event* event)
	{

	};

	//�ɿ�ʱ
	mouseListener->onTouchEnded = CC_CALLBACK_2(GameScene::touchEnded, this);

	//��û�¼���ʹ���Ĳ�����������һ��
	mouseListener->setSwallowTouches(true);
	//���ǿ���������ѧһ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////////    ���������tag
	EventDispatcher *mouseDispatcher = Director::getInstance()->getEventDispatcher(); //     ��
	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(MeHeroTag));

	//ע����̼�����
	//ʹ�æ˱��ʽ
	//Ŀǰֻʵ���� Q W E A B P������ʱӢ��������Ӧ

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//����tag��ȡӢ��
		auto target = static_cast<Hero*>(event->getCurrentTarget());
		//��ǰ���ڰ��°�������ʱ��������Ϊ����ѡ�񹥻�Ŀ�������
		//�������ƶ�
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
			//�ڴ˴���������Q
			if (target->getHeroName() == 'H')
			{

				if (target->getQSkillWaitTime() <= 0.01)
				{

					//ֹͣ�ƶ�������������
					target->stopActionByTag(HeroMove);
					//����q���ܣ�����ʱ�������Ӻ��๥���ٶȺ��ƶ��ٶ�
					target->setBuff(true);
					//����ʱ��5*q���ܵȼ�
					target->setBuffTime(HouyiQSkillLastTime * target->getQSkillLevel());
					//�ü���ʵ��Ч����HouyiHero update������ʵ��
					target->setQSkillWaitTime(target->getQSkillCdTime());
					target->setHeroAfterShake(target->getQSkillAfterShake());

				}
			}

			//�ڴ˴�������ɪQ
			if (target->getHeroName() == 'Y')
			{
				if (target->getQSkillWaitTime() <= 0.01)
				{

					//ֹͣ�ƶ�������������
					target->stopActionByTag(HeroMove);
					//����q���ܣ�����ʱ�������Ӻ��๥���ٶȺ��ƶ��ٶ�
					target->setBuff(true);
					//����ʱ��5*q���ܵȼ�
					target->setBuffTime(YaseQSkillLastTime * target->getQSkillLevel());
					//�ü���ʵ��Ч����HouyiHero update������ʵ��
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
		//�ݶ���P��ʵ�ֲ鿴װ������
		case EventKeyboard::KeyCode::KEY_P:
		{
			target->thisKeyPressed('P');
			break;
		}

		//B�����̵�
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
	//��֪���ò�����û�¼���Ҳ��֪����ô���ü�����û
	//����ûд
	//��Ҳ��֪������Ҳ������

	//������������������ѧһ��һ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////    ���������tag
	EventDispatcher *keyboardDispatcher = Director::getInstance()->getEventDispatcher();//       ��
	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(MeHeroTag));

	//ע��������ײ������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::contactBegin, this);
	contactListener->onContactPreSolve = [](PhysicsContact& contact, const PhysicsContactPreSolve& solve)
	{
		log("asdaaaaaaaaaa");
		return true;
	};
	contactListener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};
	contactListener->onContactSeparate = [](PhysicsContact& contact)
	{
		log("DSDSD");
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 1);


}

void GameScene::onExit()
{
	//����һ��Ҫ���±����
	Layer::onExit();

	//��onExit������ע��������
	//������
	//��֪����Ū��ʲôbug//////////////////////////////////////////////////////////////////////////////////////////////////
	//����Ŀǰ��ע��û��

}

bool GameScene::init()
{
	log("gs init run");

	/////////////////////////////
	// 1. super init first
	//��֪��ΪʲôҪ�ӵ��ǻ��Ǽ���
	//���ܸ�����û�гɹ������й�
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��Ϸ��ͼ
	_tileMap = TMXTiledMap::create("Map.tmx");
	addChild(_tileMap, 0, 100);

	//��ʼ����ײ��
	_collidable = _tileMap->getLayer("Collidable");


	//����meHeroTag���ü���Ӣ�۾���
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

		//�ú���Ϊ������ȴʱ��͹�������ĺ���
		hero->schedule(schedule_selector(HouyiHero::buffUpdate), 1.0 / 60.0);
		hero->scheduleUpdate();
		break;
	}
	case 'Y':
	{
		auto hero = YaseHero::create();
		auto body = PhysicsBody::createCircle(hero->getContentSize().width / 2);
		body->setContactTestBitmask(MEUNITTEST);
		log("mehero test mask %d", body->getContactTestBitmask());
		body->setCategoryBitmask(MEUNITCATEGORY);
		body->setCollisionBitmask(MEUNITCOLLISION);
		hero->setPhysicsBody(body);
		hero->setPosition(Player1StartPosition);
		hero->setFlag(Player1);
		hero->setHuman();
		addChild(hero, 100, MeHeroTag);
		//�ú���Ϊ������ȴʱ��͹�������ĺ���
		hero->schedule(schedule_selector(YaseHero::buffUpdate), 1.0 / 60.0);
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
		//�ú���Ϊ������ȴʱ��͹�������ĺ���
		hero->scheduleUpdate();
		break;
	}

	default:break;
	}

	//���õз�Ӣ��
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
		break;
	}

	case 'Y':
	{
		break;
	}



	default:break;
	}

	//���÷��س�ʼ�����Ĳ˵�
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(20);
	MenuItemFont* backItem = MenuItemFont::create("back", CC_CALLBACK_1(GameScene::menuBackCallback, this));
	backItem->setPosition(origin.x + visibleSize.width - backItem->getContentSize().width / 2,
		origin.y + backItem->getContentSize().height / 2);

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 200);

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
	tower1->setPosition(Vec2(155, 105));
	this->addChild(tower1);

	Sprite *tower2 = Sprite::create("tower.png");
	tower2->setPosition(Vec2(370, 270));
	this->addChild(tower2);
	this->schedule(schedule_selector(GameScene::watchMeAndOther), 1.0 / 60.0);
//	this->schedule(schedule_selector(GameScene::wulawula), WulaWulaCD);
	return true;
}

//����AI�ĺ���
//by ������ 2019��6��2��
void GameScene::watchMeAndOther(float dt)
{
	Hero* meHero = dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag));
	Hero* otherHero = dynamic_cast<Hero*>(this->getChildByTag(this->getEnermyType()));
	//����ҷ�������
	meHero->setMoney(this->getMeMoney());
	meHero->setExpPoint(this->getMeExp());
	if (this->getMeExp() >= ExpPerLevel)
	{
		this->changeMeExp(-ExpPerLevel);
	}
	//��صз�������
	otherHero->setMoney(this->getOtherMoney());
	otherHero->setExpPoint(this->getOtherExp());
	if (this->getOtherExp() >= ExpPerLevel)
	{
		this->changeOtherExp(-ExpPerLevel);
	}

	//��ȡ˫��Ӣ�۵�λ��
	Vec2 meHeroPoint = meHero->getPosition();
	Vec2 otherHeroPoint = otherHero->getPosition();
	
	//�����AI ��AI���п���
	if (this->getEnermyType() == AIHeroTag)
	{
		Vec2 distance = otherHeroPoint - meHeroPoint;
		//��ȡ˫������
		float length = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
		//���AI���ƺ���
		if (this->getOtherHeroTag() == 'H')
		{
			//�жϲ������չ�
		/*	if (length <= HouyiNormalAttackRange && otherHero->getAttackWaitTime() <= 0.01)
			{
				takeHouyiNormalAttack(otherHero,false, otherHeroPoint, meHeroPoint);
				otherHero->setAttackWaitTime(1.0 / otherHero->getAttackSpeed());
				otherHero->setHeroAfterShake(otherHero->getNormalAttackAfterShake());
			}//end �չ�

			//�жϲ�Q���ܿ�buff
			if (length <= 200.0 && otherHero->getQSkillWaitTime() <= 0.01)
			{
				//����q���ܣ�����ʱ�������Ӻ��๥���ٶ�
				otherHero->setBuff(true);
				//����ʱ��k*q���ܵȼ�
				otherHero->setBuffTime(HouyiQSkillLastTime * otherHero->getQSkillLevel());
				//�ü���ʵ��Ч����update������ʵ��
				otherHero->setQSkillWaitTime(otherHero->getQSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getQSkillAfterShake());
			}//end buff
		
			//�жϲ�W����
			if (length <= HouyiWSkillRange - 20 && otherHero->getWSkillWaitTime() <= 0.01)
			{
				takeHouyiWSkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W
		
			//�жϲ��Ŵ�
			if (length <= HouyiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				takeHouyiESkill(otherHero, false, otherHeroPoint, meHeroPoint);
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E
		*/	
		}
		
		//���AI������ɪ
		if (this->getOtherHeroTag() == 'Y')
		{

		}
		//���AI����槼�
		if (this->getOtherHeroTag() == 'D')
		{

		}
	}
}

//by ������ 2019��5��20��
//�˱��ʽ�޷�ʹ��this���ʵ�����touchEnded�����ó���д
void GameScene::touchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//ͨ����Ӣ�����õı�ǩ��ȡӢ��
	//����ԭ���ǻ�ȡ�¼����󶨵ľ���
	//����ѧ��һ����Ҳ��֪����ʲôԭ��
	//init������addChild(hero,20,tag),���е�tag���Ǹ�Ӣ�۵ı�ǩ

	//��ȡ�ɿ����ʱ�����λ��
	Vec2 touchPosition = touch->getLocation();
	//�����ǰӢ��Ϊ����
	if (this->meHeroTag == 'H')
	{
		auto target = static_cast<HouyiHero*>(event->getCurrentTarget());
		//��Ӣ�۵ĳ�Ա����touchPoint��ֵΪtouchPosition
		target->setTouchPoint(touchPosition);
		//��ȡӢ�۵�ǰλ��
		Vec2 heroPosition = target->getPosition();

		//���������ʱδ����������������Ϊ��õ��ƶ�
		if (!target->isPressingKeyboard() && target->getHeroAfterShake() <= 0.01)
		{
			heroMove(target);
		}
		//���������ʱ����������ݰ������м����ͷ�
		//��ʱ���ĵ��Ӧ�ڼ����ͷŵĵ�
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ������չ�
					target->stopActionByTag(HeroMove);
					takeHouyiNormalAttack(target,true,heroPosition, touchPosition);
					//�����չ�����͹�����ҡ
					target->setAttackWaitTime(1.0 / target->getAttackSpeed());
					target->setHeroAfterShake(target->getNormalAttackAfterShake());
				}
				break;
			}

			case 'Q':
			{
				//�����q����Ϊδ������ʱʹ��
				//�ڼ��̼����ж���
				break;
			}
			case 'W':
			{
				if (target->getWSkillWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ�����W
					target->stopActionByTag(HeroMove);
					takeHouyiWSkill(target,true,heroPosition, touchPosition);
					//����W CD�ͼ��ܺ�ҡ
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}
			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ����д���
					target->stopActionByTag(HeroMove);
					takeHouyiESkill(target,true,heroPosition, touchPosition);
					//���ô��еȴ�ʱ��
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

	//�����ǰӢ��Ϊ��ɪ
	if (this->meHeroTag == 'Y')
	{
		auto target = static_cast<YaseHero*>(event->getCurrentTarget());
		//��Ӣ�۵ĳ�Ա����touchPoint��ֵΪtouchPosition
		target->setTouchPoint(touchPosition);
		//��ȡӢ�۵�ǰλ��
		Vec2 heroPosition = target->getPosition();

		//���������ʱδ����������������Ϊ��õ��ƶ�
		if (!target->isPressingKeyboard())
		{
			heroMove(target);
		}

		//���������ʱ����������ݰ������м����ͷ�
		//��ʱ���ĵ��Ӧ�ڼ����ͷŵĵ�
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ������չ�
					target->stopActionByTag(HeroMove);
					takeYaseNormalAttack(target, true, heroPosition, touchPosition);
					//����ƽA�ȴ�ʱ��
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
				if (target->getWSkillWaitTime() <= 0.01)
				{
					//���ƶ�����ת
					takeYaseWSkill(target, true, heroPosition, touchPosition);
					//����CD�ͼ��ܺ�ҡ
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}

			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ����д���
					target->stopActionByTag(HeroMove);
					takeYaseESkill(target, true, heroPosition, touchPosition);
					//���ô��еȴ�ʱ��
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

	//�����ǰӢ��Ϊ槼�
	if (this->meHeroTag == 'D')
	{
		auto target = static_cast<DajiHero*>(event->getCurrentTarget());
		//��Ӣ�۵ĳ�Ա����touchPoint��ֵΪtouchPosition
		target->setTouchPoint(touchPosition);
		//��ȡӢ�۵�ǰλ��
		Vec2 heroPosition = target->getPosition();

		//���������ʱδ����������������Ϊ��õ��ƶ�
		if (!target->isPressingKeyboard() && target->getHeroAfterShake() <= 0.01)
		{
			heroMove(target);
		}
		//���������ʱ����������ݰ������м����ͷ�
		//��ʱ���ĵ��Ӧ�ڼ����ͷŵĵ�
		if (target->isPressingKeyboard())
		{

			char key = target->pressThisKey();
			switch (key)
			{
			case 'A':
			{
				if (target->getAttackWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ������չ�
					target->stopActionByTag(HeroMove);
					takeHouyiNormalAttack(target, true, heroPosition, touchPosition);
					//�����չ�����͹�����ҡ
					target->setAttackWaitTime(1.0 / target->getAttackSpeed());
					target->setHeroAfterShake(target->getNormalAttackAfterShake());
				}
				break;
			}

			case 'Q':
			{
				//�����q����Ϊδ������ʱʹ��
				//�ڼ��̼����ж���
				break;
			}
			case 'W':
			{
				if (target->getWSkillWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ�����W
					target->stopActionByTag(HeroMove);
					takeHouyiWSkill(target, true, heroPosition, touchPosition);
					//����W CD�ͼ��ܺ�ҡ
					target->setWSkillWaitTime(target->getWSkillCdTime());
					target->setHeroAfterShake(target->getWSkillAfterShake());
				}
				break;
			}
			case 'E':
			{
				if (target->getESkillWaitTime() <= 0.01)
				{
					//ֹͣ��ǰ���ƶ����д���
					target->stopActionByTag(HeroMove);
					takeHouyiESkill(target, true, heroPosition, touchPosition);
					//���ô��еȴ�ʱ��
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
//�ж���ײ
void GameScene::collision(float dt)
{
	position_now = (this->getChildByTag(MeHeroTag))->getPosition();
	if (setPlayerPosition(position_now) == true)
	{
		(this->getChildByTag(MeHeroTag))->setPosition(position_last);
	}
	else position_last = position_now;
}

//�ж���ײ
bool GameScene::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);//����������ת��Ϊ��Ƭ����
	int tileGid = _collidable->getTileGIDAt(tileCoord);//��ø���Ƭ��GID
	if (tileGid > 0)
	{
		return true;
	}
	return false;
}



//��������
Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

//�жϾ�����ײ
bool GameScene::contactBegin(cocos2d::PhysicsContact& contact)
{

//	log("contact");
	auto spriteA = (BasicSprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (BasicSprite*)contact.getShapeB()->getBody()->getNode();

//	log("A %d ,B %d", spriteA->getTag(), spriteB->getTag());

	if (spriteA && spriteA->getTag() == OtherSkillTag)
	{
		//��ʱA�ǵз����� B���ҷ���λ
		auto otherSkill = static_cast<BasicSkill*>(spriteA);
		auto meHero = static_cast<Hero*>(spriteB);
		//������λ�ܵ��˺�
		meHero->sufferDamage(otherSkill->getDamagePoint());
		//���������λ����
		//������Ӣ�ۼӾ���ͽ��
		if (meHero->getHealthPoint() <= 0)
		{
			this->changeOtherExp(HeroExp);
			this->changeOtherMoney(HeroMoney);
		}
		//�������Ϊ���о���ʧ�����ü�����ʧ
		if (otherSkill->shouldRemove())
		{
			otherSkill->removeFromParent();
			return false;
		}	
	}
	if (spriteB && spriteB->getTag() == OtherSkillTag)
	{
		//��ʱB�ǵз����� A���ҷ���λ
		auto otherSkill = static_cast<BasicSkill*>(spriteB);
		auto meHero = static_cast<Hero*>(spriteA);
		meHero->sufferDamage(otherSkill->getDamagePoint());
		//���������λ����
		//������Ӣ�ۼӾ���ͽ��
		if (meHero->getHealthPoint() <= 0)
		{
			this->changeOtherExp(HeroExp);
			this->changeOtherMoney(HeroMoney);
		}
		//�������Ϊ���о���ʧ�����ü�����ʧ
		if (otherSkill->shouldRemove())
		{
			otherSkill->removeFromParent();
			return false;
		}
	}
	if (spriteA && spriteA->getTag() == MeSkillTag)
	{
		//��ʱA���ҷ����� B�ǵз���λ
		auto meSkill = static_cast<BasicSkill*>(spriteA);
		auto otherHero = static_cast<Hero*>(spriteB);
		otherHero->sufferDamage(meSkill->getDamagePoint());
		//����з���λ����
		//���ҷ�Ӣ�ۼӾ���ͽ��
		if (otherHero->getHealthPoint() <= 0)
		{
			this->changeMeExp(HeroExp);
			this->changeMeMoney(HeroMoney);
		}
		//�������Ϊ���о���ʧ�����ü�����ʧ
		if (meSkill->shouldRemove())
		{
			meSkill->removeFromParent();
			return false;
		}
	}
	
	if (spriteB && spriteB->getTag() == MeSkillTag)
	{
		//��ʱB���ҷ����� A�ǵз���λ
		auto meSkill = static_cast<BasicSkill*>(spriteB);
		log("B is Meskill");
		auto otherHero = static_cast<Hero*>(spriteA);
		log("A is other hero");
		otherHero->sufferDamage(meSkill->getDamagePoint());
		//����з���λ����
		//���ҷ�Ӣ�ۼӾ���ͽ��
		if (otherHero->getHealthPoint() <= 0)
		{
			this->changeMeExp(HeroExp);
			this->changeMeMoney(HeroMoney);
		}
		//�������Ϊ���о���ʧ�����ü�����ʧ
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
	//Ӣ����õ��˶�
	//��ȡӢ��Ŀǰ���ٶ�
	float heroSpeed = target->getMoveSpeed();
	//10
	Vec2 relativePosition = heroPosition - touchPosition;
	//��ȡ���λ�õ�ģ��
	float distanceSquare = relativePosition.x*relativePosition.x + relativePosition.y*relativePosition.y;
	float distance = sqrt(distanceSquare);
	//�����˶����õ������ʱ��
	float timeNeeded = distance / heroSpeed;

	//��ֹͣ��ǰ���˶����������������˶��ĵ���
	target->stopActionByTag(HeroMove);

	//����һ���˶�����moveAction���˶���ָ������touchPosition
	FiniteTimeAction * moveAction = (FiniteTimeAction*)target->runAction(MoveTo::create(timeNeeded, touchPosition));
	//�������������tag ----> HeroMove
	moveAction->setTag(HeroMove);
}

void GameScene::takeHouyiNormalAttack(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	HouyiNormalAttack* houyiNormalAttack = HouyiNormalAttack::createTheAttack(hero);
	auto body = PhysicsBody::createBox(houyiNormalAttack->getContentSize());
	houyiNormalAttack->setPhysicsBody(body);
	//ֹͣ��ǰ���ƶ������չ�
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
	houyiNormalAttack->takeHouyiNormalAttack(startPoint,targetPoint);
	//���չ���ʾ��gamescene������
	//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
	//����ƽA�ȴ�ʱ��
}

void GameScene::takeHouyiWSkill(Hero* hero,bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	//��Ū��ʮ����ͷ
					//�޸ļ�ͷ���ǵ��޸�forѭ��
	HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
	//�м�ļ�ͷ��������
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

	//���ߵļ�ͷ�ɶԴ���
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
		houyiWSkill[i]->takeHouyiWSkill(startPoint, targetPoint, i * 3.14 / 30);//���ݻ�����

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
		houyiWSkill[i + 1]->takeHouyiWSkill(startPoint, targetPoint, -i * 3.14 / 30);//���ݻ�����
	}

	//�������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
}

void GameScene::takeHouyiESkill(Hero* hero,bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	HouyiESkill* bigBird = HouyiESkill::createHouyiESkill(hero);
	auto body = PhysicsBody::createCircle(bigBird->getContentSize().height/2);
	
	bigBird->setPhysicsBody(body);
	bigBird->takeHouyiESkill(startPoint,targetPoint);
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
	//�Ѵ�����ʾ��gamescene������
	
	//�����о����˶�һ������ʱɾ�����ù�����HouyiESkill���update������ʵ��
}

void GameScene::takeYaseNormalAttack(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	YaseNormalAttack* yaseNormalAttack = YaseNormalAttack::createTheAttack(hero);
	auto body = PhysicsBody::createBox(yaseNormalAttack->getContentSize());
	yaseNormalAttack->setPhysicsBody(body);
	if (isMe)
	{
		this->addChild(yaseNormalAttack, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(yaseNormalAttack, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yaseNormalAttack->takeYaseNormalAttack(startPoint, targetPoint);
	//���չ���ʾ��gamescene������
	//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
}

void GameScene::takeYaseWSkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	YaseWSkill* yaseWSkill = YaseWSkill::createYaseWSkill(hero);
	Vec2 verts[] = {
		Vec2(0,0),
		Vec2(YaseWSkillRange,0),
		Vec2(YaseWSkillRange,-2),
		Vec2(0,-2)
	};
	auto body = PhysicsBody::create();
	body->addShape(PhysicsShapePolygon::create(verts, 4));
	yaseWSkill->setPhysicsBody(body);
	if (isMe)
	{
		this->getChildByTag(MeHeroTag)->addChild(yaseWSkill, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->getChildByTag(this->getEnermyType())->addChild(yaseWSkill, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yaseWSkill->takeYaseWSkill(hero);
}

void GameScene::takeYaseESkill(Hero* hero, bool isMe, Vec2 startPoint, Vec2 targetPoint)
{
	YaseESkill* yaseESkill = YaseESkill::createYaseESkill(hero);
	auto body = PhysicsBody::createBox(yaseESkill->getContentSize());
	yaseESkill->setPhysicsBody(body);
	if (isMe)
	{
		this->addChild(yaseESkill, 200, MeSkillTag);
		body->setContactTestBitmask(MESKILLTEST);
		body->setCategoryBitmask(MESKILLCATEGORY);
		body->setCollisionBitmask(MESKILLCOLLISION);
	}
	else
	{
		this->addChild(yaseESkill, 200, OtherSkillTag);
		body->setContactTestBitmask(OTHERSKILLTEST);
		body->setCategoryBitmask(OTHERSKILLCATEGORY);
		body->setCollisionBitmask(OTHERSKILLCOLLISION);
	}
	yaseESkill->takeYaseESkill(startPoint, targetPoint);
}

void GameScene::wulawula(float dt)
{
	//������ս��
	auto meJinzhanSoldier = JinzhanSoldier::create(MeSoldier);
	meJinzhanSoldier->setPosition(500, 500);
	meJinzhanSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(AIHeroTag)));
	this->addChild(meJinzhanSoldier, 200, MeJinzhanSoldierTag);
	meJinzhanSoldier->scheduleUpdate();
	//�з���ս��
	auto otherJinzhanSoldier = JinzhanSoldier::create(OtherSoldier);
	otherJinzhanSoldier->setPosition(900, 900);
	otherJinzhanSoldier->AIcontrol(static_cast<Hero*>(this->getChildByTag(MeHeroTag)));
	this->addChild(otherJinzhanSoldier, 200, OtherJinzhanSoldierTag);
	otherJinzhanSoldier->scheduleUpdate();
}