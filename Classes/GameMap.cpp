#include "GameMap.h"
USING_NS_CC;


Scene* GameMap::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMap::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameMap::menuCloseCallback, this));

	closeItem->setPosition(100,1050);


	auto label = Label::createWithTTF("New Unit", "fonts/Marker Felt.ttf", 40);
	auto newUnit = MenuItemLabel::create(label, CC_CALLBACK_1(GameMap::newUnitCallback, this));
	newUnit->setPosition(300, 1050);

	auto label2 = Label::createWithTTF("End turn", "fonts/Marker Felt.ttf", 40);	
	auto endTurn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameMap::endTurnCallback, this));
	endTurn->setPosition(300, 1000);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,newUnit,endTurn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);




	_tileMap = TMXTiledMap::create("map2.tmx");
	ground = _tileMap->getLayer("ground");
	assert(ground != nullptr);

	this->addChild(_tileMap);

	dealWithTouch();

	gameStatus = new GameStatus(this);

	this->scheduleUpdate();
	
	return true;
}


void GameMap::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameMap::dealWithTouch()
{
	CCLOG("ok");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Point point = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
		startPoint= point = GameHelper::SrceenToMap(point);
		if (point.y < 0)
		{
			return false;
		}

		//get the information about the map
		int id = ground->getTileGIDAt(point);
		string terrain = "";
		if (id != 0)
		{
			Value property = _tileMap->getPropertiesForGID(id);
			Value p = property.asValueMap().at("type");
			terrain = p.asString();
		}
		gameStatus->showTerrain(terrain);


		GameUnit* t = getUnitByXY(point.x, point.y);
		if (t != nullptr)
		{
			gameStatus->setCount(count);
			currentUnit = t;
			return true;
		}

		return true;
	};

	listener->onTouchMoved = [&](Touch *touch, Event *event)
	{
		if (getUnitByXY(startPoint.x, startPoint.y) != nullptr)
		{
			mode = moveUnit;
		}

	};

	
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		Point point = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
		point = GameHelper::SrceenToMap(point);
		if (point.y < 0)
		{
			return;
		}

		//get the information about the map
		int id = ground->getTileGIDAt(point);
		string terrain = "";
		if (id != 0)
		{
			Value property = _tileMap->getPropertiesForGID(id);
			Value p = property.asValueMap().at("type");
			terrain = p.asString();
		}
		gameStatus->showTerrain(terrain);

		//get unit when the key is released
		GameUnit* t = getUnitByXY(point.x, point.y);

		


		//attacking
		if (t != nullptr)
		{
			//cannot use units that don't belong to you
			if (currentUnit != nullptr&&currentUnit->owner != currentPlayer)
				return;

			if (currentUnit->owner != t->owner)
			{
				//if no stamina or distance !=1
				if (currentUnit->stamina == 0 || GameHelper::getDistance(currentUnit->getXY(), t->getXY()) != 1)
				{
					return;
				}
				currentUnit->stamina = 0;
				t->hp -= currentUnit->attack;
				if (t->hp <= 0)
				{
					delete t;
					CCLOG("delete:");
					int i=-1;
					for (std::vector<GameUnit*>::iterator it = units.begin(); it != units.end(); ++it)
					{
						i++;
						if (*it == t)
						{
							units.erase(units.begin() + i);
							break;
						}
					}
						
				}
			}
			else
			{
				return;
			}			
		}
		else//moving and creating unit
		{ 
			switch (mode)
			{
			case normal:
				currentUnit = nullptr;
				break;
			case newUnit:
				{
					GameUnit* sd = new GameUnit(currentPlayer,this);
					currentUnit = sd;
					units.push_back(sd);
					sd->setXY(point.x, point.y);
	
					CCLOG("new unit");
					count++;
					gameStatus->setCount(count);
					mode = normal;
					break;
				}
			case moveUnit:
				{
					//cannot use units that don't belong to you
					if (currentUnit != nullptr&&currentUnit->owner != currentPlayer)
						return;

					currentUnit->moveToPoint(point);
					mode = normal;
					break;
				}
			}			
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _tileMap);
}

GameUnit* GameMap::getUnitByXY(int x, int y)
{
	for (GameUnit* var : units)
	{
		if (Point(x, y) == var->getXY())
		{
			return var;
		}		
	}
	return nullptr;
}

void GameMap::update(float delta)
{
	gameStatus->showUnit(currentUnit);
	switch (currentPlayer)
	{
	case 1:
		gameStatus->showPlayer("Player1");
		break;
	case 2:
		gameStatus->showPlayer("Player2");

		break;
	}
}

void GameMap::newUnitCallback(cocos2d::Ref* pSender)
{
	mode = newUnit;
}

void GameMap::endTurnCallback(cocos2d::Ref* pSender)
{
	for (GameUnit* i : units)
	{
		if (i->owner == currentPlayer)
		{
			i->stamina = i->maxStamina;
		}
	}
	switch (currentPlayer)
	{
	case 1:
		currentPlayer = 2;
		break;
	case 2:
		currentPlayer = 1;
		break;
	}
}

