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
//�޸ļ��ܷ�Χʱ��Ҫ�޸�Ӣ��ͷ�ļ�define�еĲ���

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
	Scene::onEnter();

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
			if (target->getHeroName() == 'H')
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
	log("gs init run");

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
		hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		hero->setHuman();
		addChild(hero, 100, MeHeroTag);

		//�ú���Ϊ������ȴʱ��͹�������ĺ���
		hero->scheduleUpdate();
		break;
	}
	case 'Y':
	{
		auto hero = YaseHero::create();
		hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		addChild(hero, 100, MeHeroTag);
		hero->setHuman();
		//�ú���Ϊ������ȴʱ��͹�������ĺ���
		hero->scheduleUpdate();
		break;
	}

	case 'D':
	{
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

	//��ȡλ�÷��͸�������
	/*this->schedule(schedule_selector(GameScene::get_position), 0.001f);*/
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

//ˮ��
	Sprite *shuijing1 = Sprite::create("shuijing.png");
	shuijing1->setPosition(Vec2(400,200));
	this->addChild(shuijing1,2);

	Sprite *shuijing2 = Sprite::create("shuijing2.png");
	shuijing2->setPosition(Vec2(1300,800));
	this->addChild(shuijing2,2);

	//������
	Sprite *tower1 = Sprite::create("tower.png");
	tower1->setPosition(Vec2(550, 300));
	this->addChild(tower1,2);

	Sprite *tower2 = Sprite::create("tower.png");
	tower2->setPosition(Vec2(1200, 700));
	this->addChild(tower2,2);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::watchMeAndOther), 1.0 / 60.0);

	//���Ͻǵ�ս��
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

//����AI�ĺ���
//by ������ 2019��6��2��
void GameScene::watchMeAndOther(float dt)
{
	Hero* meHero = dynamic_cast<Hero*>(this->getChildByTag(MeHeroTag));
	Hero* otherHero = dynamic_cast<Hero*>(this->getChildByTag(this->getEnermyType()));

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
			if (length <= HouyiNormalAttackRange && otherHero->getAttackWaitTime() <= 0.01)
			{
				HouyiNormalAttack* attack = HouyiNormalAttack::createTheAttack();
				//ע�����ﲻҪ���˳��////////////////��//////////////��
				attack->takeHouyiNormalAttack(otherHeroPoint, meHeroPoint);
				this->addChild(attack, 200, OtherSkillTag);
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
				//��Ū��������ͷ

				HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
				//�м�ļ�ͷ��������
				houyiWSkill[0] = HouyiWSkill::createHouyiWSkill();
				houyiWSkill[0]->takeHouyiWSkill(otherHeroPoint, meHeroPoint, 0);
				this->addChild(houyiWSkill[0], 200, OtherSkillTag);
				//���ߵļ�ͷ�ɶԴ���
				for (int i = 1; i < HouyiWSkillArrowNumber; i += 2)
				{
					houyiWSkill[i] = HouyiWSkill::createHouyiWSkill();
					houyiWSkill[i]->takeHouyiWSkill(otherHeroPoint, meHeroPoint, i * 3.14 / 30);//���ݻ�����
					houyiWSkill[i + 1] = HouyiWSkill::createHouyiWSkill();//i�˵���Ϊ����ͷ�н�
					houyiWSkill[i + 1]->takeHouyiWSkill(otherHeroPoint, meHeroPoint, -i * 3.14 / 30);
					//�Ѽ�ͷ��ʾ��gamescene������
					this->addChild(houyiWSkill[i], 200, OtherSkillTag);
					this->addChild(houyiWSkill[i + 1], 200, OtherSkillTag);
				}

				//���չ������˶�һ������ʱɾ�����ù�����HouyiWSkill���update������ʵ��
				//����W�ȴ�ʱ��
				otherHero->setWSkillWaitTime(otherHero->getWSkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getWSkillAfterShake());
			}//end W

			//�жϲ��Ŵ�
			if (length <= HouyiESkillRange && otherHero->getESkillWaitTime() <= 0.01)
			{
				HouyiESkill* bigBird = HouyiESkill::createHouyiESkill();

				//ֹͣ��ǰ���ƶ����д���
				bigBird->takeHouyiESkill(otherHeroPoint, meHeroPoint);
				//�Ѵ�����ʾ��gamescene������
				this->addChild(bigBird, 200, OtherSkillTag);
				//�����о����˶�һ������ʱɾ�����ù�����HouyiESkill���update������ʵ��
				//���ô��еȴ�ʱ��
				otherHero->setESkillWaitTime(otherHero->getESkillCdTime());
				otherHero->setHeroAfterShake(otherHero->getESkillAfterShake());
			}//end E
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
					HouyiNormalAttack* houyiNormalAttack = HouyiNormalAttack::createTheAttack();
					//ֹͣ��ǰ���ƶ������չ�
					target->stopActionByTag(HeroMove);
					houyiNormalAttack->takeHouyiNormalAttack(target);
					//���չ���ʾ��gamescene������
					this->addChild(houyiNormalAttack, 200, MeSkillTag);
					//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
					//����ƽA�ȴ�ʱ��
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
					//ֹͣ��ǰ���ƶ������չ�
					target->stopActionByTag(HeroMove);

					//��Ū��ʮ����ͷ
					//�޸ļ�ͷ���ǵ��޸�forѭ��
					HouyiWSkill* houyiWSkill[HouyiWSkillArrowNumber];
					//�м�ļ�ͷ��������
					houyiWSkill[0] = HouyiWSkill::createHouyiWSkill();
					houyiWSkill[0]->takeHouyiWSkill(target, 0);
					this->addChild(houyiWSkill[0], 200, MeSkillTag);
					//���ߵļ�ͷ�ɶԴ���
					for (int i = 1; i < HouyiWSkillArrowNumber; i += 2)
					{
						houyiWSkill[i] = HouyiWSkill::createHouyiWSkill();
						houyiWSkill[i]->takeHouyiWSkill(target, i * 3.14 / 30);//���ݻ�����
						houyiWSkill[i + 1] = HouyiWSkill::createHouyiWSkill();//i�˵���Ϊ����ͷ�н�
						houyiWSkill[i + 1]->takeHouyiWSkill(target, -i * 3.14 / 30);
						//�Ѽ�ͷ��ʾ��gamescene������
						this->addChild(houyiWSkill[i], 200, MeSkillTag);
						this->addChild(houyiWSkill[i + 1], 200, MeSkillTag);
					}

					//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
					//����ƽA�ȴ�ʱ��
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

					//ֹͣ��ǰ���ƶ����д���
					target->stopActionByTag(HeroMove);
					bigBird->takeHouyiESkill(target);

					//�Ѵ�����ʾ��gamescene������
					this->addChild(bigBird, 200, MeSkillTag);
					//�����о����˶�һ������ʱɾ�����ù�����HouyiESkill���update������ʵ��
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
					YaseNormalAttack* yaseNormalAttack = YaseNormalAttack::createTheAttack();

					//ֹͣ��ǰ���ƶ������չ�
					target->stopActionByTag(HeroMove);
					yaseNormalAttack->takeYaseNormalAttack(heroPosition, touchPosition);
					//���չ���ʾ��gamescene������
					this->addChild(yaseNormalAttack, 200, MeSkillTag);
					//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
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

	//�����ǰӢ��Ϊ槼�
	if (this->meHeroTag == 'D')
	{

	}
	this->schedule(schedule_selector(GameScene::collision), 0.001f);
}



void GameScene::shop_xie(cocos2d::Ref* pSender)
{
	//setMoney(���-300)
	//��������
	//װ����������Ь��
	Director::getInstance()->end();
}

void GameScene::shop_shoutao(cocos2d::Ref* pSender)
{
	//setMoney(���-300)
	//���ӹ������ͷ�ǿ
	//װ��������������
	Director::getInstance()->end();
}

void GameScene::shop_changgong(cocos2d::Ref* pSender)
{
	//setMoney�����-300��
	//���ӹ���
	//װ���������ӳ���
	Director::getInstance()->end();
}

void GameScene::shop_kaijia(cocos2d::Ref* pSender)
{
	//setMoney�����-300��
	//���ӷ���
	//װ��������������
	Director::getInstance()->end();
}

void GameScene::shop_hongshuijing(cocos2d::Ref* pSender)
{
	//setMoney�����-300��
	//����Ѫ��
	//װ���������Ӻ�ˮ��
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

void GameScene::updateScore(float dt)
{
	
}

//void GameScene::get_position(float dt)
//{
//	Client a;
//	position_client = (this->getChildByTag(MeHeroTag))->getPosition();
//	a.SendMes(FloatToChar(position_client.x, position_client.y));
//}