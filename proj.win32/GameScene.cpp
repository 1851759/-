#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "StartScene.h"
#include "GameScene.h"

#include "Hero.h"


#include "HouyiHero.h"
#include "HouyiNormalAttack.h"
#include "HouyiESkill.h"
#include "HouyiWSkill.h"


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
	
	//////////����Ĭ�ϼ���Ӣ��Ϊ���࣬���ڵ���////////////////////////////////////////////////////////////////
	



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
	mouseListener->onTouchEnded = CC_CALLBACK_2(GameScene::touchEnded, this);
	


	//��û�¼���ʹ���Ĳ�����������һ��
	mouseListener->setSwallowTouches(true);

	//���ǿ���������ѧһ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////////    ���������tag
	EventDispatcher *mouseDispatcher = Director::getInstance()->getEventDispatcher(); //     ��
	mouseDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, getChildByTag(HeroTag));


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
			if (target->getHeroName() == 'H')
			{
				if (target->getQSkillWaitTime() <= 0.01)
				{
					//ֹͣ�ƶ�������������
					target->stopActionByTag(HeroMove);
					//����q���ܣ�����ʱ�������Ӻ��๥���ٶ�
					target->setBuff(true);
					//����ʱ��5*q���ܵȼ�
					target->setBuffTime(5 * target->getQSkillLevel());
					//�ü���ʵ��Ч����update������ʵ��
					target->setQSkillWaitTime(target->getQSkillCdTime());
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
		default : break;
		}
		
	};
	keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		auto target = static_cast<Hero*>(event->getCurrentTarget());
		target->setUnPressingKeyboard();
	};
	//��֪���ò�����û�¼���Ҳ��֪����ô���ü�����û
	//����ûд
	//��Ҳ��֪������Ҳ������

	//������������������ѧһ��һ����ͨ���ⲽ������������Ӣ�۵�tag/////////////////////////////    ���������tag
	EventDispatcher *keyboardDispatcher = Director::getInstance()->getEventDispatcher();//       ��
	keyboardDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, getChildByTag(HeroTag));
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
	////////ĿǰĬ������Ϊ����//////////////////////////////////////////////////////���Ҫ�����///////////////////////////
	this->setMeHeroTag('H');

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	//ʱ����Ⱥ���
	this->scheduleUpdate();

	
	//����meHeroTag����Ӣ�۾���
	switch (this->getMeHeroTag())
	{

	case 'H':
	{
		auto hero = HouyiHero::create();
		hero->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		addChild(hero, 100, HeroTag);
		//�ú���Ϊ������ȴʱ��͹�������ĺ���
		hero->scheduleUpdate();
		break;
	}
	case 'Y':
	{
		break;
	}

	case 'D':
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

	return true;
}


void GameScene::touchEnded(cocos2d::Touch* touch,cocos2d:: Event* event)
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
				HouyiNormalAttack* houyiNormalAttack = HouyiNormalAttack::createTheAttack();

				//ֹͣ��ǰ���ƶ������չ�
				target->stopActionByTag(HeroMove);
				houyiNormalAttack->takeHouyiNormalAttack(target);
				//���չ���ʾ��gamescene������
				this->addChild(houyiNormalAttack, 200);
				//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
				//����ƽA�ȴ�ʱ��
				target->setAttackWaitTime(1.0/target->getAttackSpeed());
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
				HouyiWSkill* houyiWSkill[13];
				//�м�ļ�ͷ��������
				houyiWSkill[0] = HouyiWSkill::createHouyiWSkill();
				houyiWSkill[0]->takeHouyiWSkill(target, 0);
				this->addChild(houyiWSkill[0], 200);
				//���ߵļ�ͷ�ɶԴ���
				for (int i = 1; i < 13; i+=2)
				{
					houyiWSkill[i] = HouyiWSkill::createHouyiWSkill();
					houyiWSkill[i]->takeHouyiWSkill(target,i * 3.14 / 30);//���ݻ�����
					houyiWSkill[i+1] = HouyiWSkill::createHouyiWSkill();//i�˵���Ϊ����ͷ�н�
					houyiWSkill[i+1]->takeHouyiWSkill(target, -i * 3.14 / 30);
					//�Ѽ�ͷ��ʾ��gamescene������
					this->addChild(houyiWSkill[i], 200);
					this->addChild(houyiWSkill[i+1], 200);
				}
				
				//���չ������˶�һ������ʱɾ�����ù�����HouyiNormalAttack���update������ʵ��
				//����ƽA�ȴ�ʱ��
				target->setWSkillWaitTime(target->getWSkillCdTime());
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
				this->addChild(bigBird, 200);
				//�����о����˶�һ������ʱɾ�����ù�����HouyiESkill���update������ʵ��
				//���ô��еȴ�ʱ��
				target->setESkillWaitTime(target->getESkillCdTime());
				
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

	}

	//�����ǰӢ��Ϊ槼�
	if (this->meHeroTag == 'D')
	{

	}
	
	

	
	
	


}