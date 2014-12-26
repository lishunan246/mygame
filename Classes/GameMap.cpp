#include "GameMap.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

GameMap::GameMap()
{
	for (int i = 0; i < 3; i++)
		money[i] = 200;
}

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

	closeItem->setPosition(100,1025);

	auto label = Label::createWithTTF("New Unit", "fonts/Marker Felt.ttf", 50);
	auto newUnit = MenuItemLabel::create(label, CC_CALLBACK_1(GameMap::newUnitCallback, this));
	newUnit->setPosition(300, 1025);

	auto label2 = Label::createWithTTF("End turn", "fonts/Marker Felt.ttf", 50);	
	auto endTurn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameMap::endTurnCallback, this));
	endTurn->setPosition(500, 1025);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,newUnit,endTurn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	int t = random(1, 3);
	
	string mapName = "map"+GameHelper::intToString(t)+".tmx";
	CCLOG(mapName.c_str());
	_tileMap = TMXTiledMap::create(mapName);
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

		gameStatus->showTerrain(getType(point));

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
		GameUnit* t = getUnitByXY(startPoint.x, startPoint.y);
		if ( t!= nullptr&&t->owner==currentPlayer&&t->stamina!=0)
		{
			mode = moveUnit;
			t->getSprite()->setPosition(Director::getInstance()->convertToGL(touch->getPreviousLocationInView()));
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
		if (currentUnit != nullptr)
			currentUnit->resetLocation();

		gameStatus->showTerrain(getType(point));

		//get unit when the key is released
		GameUnit* t = getUnitByXY(point.x, point.y);

		//attacking
		if (t != nullptr)
		{
			if (currentUnit == nullptr)
				return;
			//cannot use units that don't belong to you
			if (currentUnit->owner != currentPlayer)
				return;

			if (currentUnit->owner != t->owner)
			{
				//if no stamina or distance !=1
				if (currentUnit->stamina == 0 || GameHelper::getDistance(currentUnit->getXY(), t->getXY()) != 1)
				{
					return;
				}

				//fight
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
				currentUnit->stamina = 0;
				t->hp -= currentUnit->attack;


				if (t->hp <= 0)
				{
					kill(t);						
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

			case moveUnit:
				{
					//cannot use units that don't belong to you
					if (currentUnit != nullptr&&currentUnit->owner != currentPlayer)
						return;

					if (currentUnit->moveToPoint(point))
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("moved.wav");
						if (currentPlayer == 1)
						{
							if (getType(point)=="base2")
							{
								CCLOG("player1 win");
								Director::getInstance()->replaceScene(GameEndScene::createScene());
							}
						}
						else
						{
							if (getType(point) == "base1")
							{
								CCLOG("player2 win");
								Director::getInstance()->replaceScene(GameEndScene1::createScene());
							}
						}
					}				
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
	for (Sprite *t : oks)
	{
		this->removeChild(t);
	}
	oks.clear();

	gameStatus->showMoney(money[currentPlayer]);
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

	if (currentUnit==nullptr||currentUnit->stamina == 0||currentUnit->owner!=currentPlayer)
		return;

	Point p = currentUnit->getXY();

	for (int i = 0; i < GameHelper::col; i++)
		for (int j = 0; j < GameHelper::row; j++)
		{
			int num = GameHelper::getDistance(p, Point(i, j));
			if ((0<num)&&(num <= currentUnit->stamina))
			{
				Sprite *s;
				if (num == 1)
				{
					s = Sprite::create("fight.png");
				}
				else
				{
					s = Sprite::create("ok.png");
				}
				 
				s->setPosition(GameHelper::MapToScreen(Point(i, j)));
				this->addChild(s);
				oks.push_back(s);
			}
		}
}

void GameMap::newUnitCallback(cocos2d::Ref* pSender)
{
	newUnit();
}

void GameMap::endTurnCallback(cocos2d::Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("endturn.wav");
	money[currentPlayer] += 25;
	for (GameUnit* i : units)
	{
		if (i->owner == currentPlayer)
		{
			i->stamina = i->hp/20+1;
			Point p = i->getXY();
			if (getType(p) == "sign")
			{
				money[currentPlayer] += 50;
			}
			else if (getType(p) == "plant")
			{
				i->hp += 20;
				if (i->hp > maxHP)
					i->hp = maxHP;
			}
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

string GameMap::getType(Point point)
{
	int id = ground->getTileGIDAt(point);

	if (id != 0)
	{
		Value property = _tileMap->getPropertiesForGID(id);
		Value p = property.asValueMap().at("type");
		return p.asString();
	}
	else
		return "";
}

bool GameMap::newUnit()
{
	if (money[currentPlayer] < GameUnit::price)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("noMoney.wav");
		CCLOG("no money");
		return false;
	}


	Point p;
	bool flag = false;
	for (int i = 0; i < GameHelper::col&&flag == false; i++)
		for (int j = 0; j < GameHelper::row; j++)
		{
			p = Point(i, j);
			if ((currentPlayer == 1 && getType(p) == "base1") ||
				(currentPlayer == 2 && getType(p) == "base2"))
			{
				flag = true;
				break;
			}

		}

	if (getUnitByXY(p.x, p.y) != nullptr)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("noMoney.wav");
		CCLOG("there is unit in base");
		return false;
	}

	GameUnit* sd = new GameUnit(currentPlayer, this);
	currentUnit = sd;
	units.push_back(sd);

	sd->setXY(p.x, p.y);
	money[currentPlayer] -= GameUnit::price;

	CCLOG("new unit");
	count++;
	gameStatus->setCount(count);
	return true;
}

void GameMap::kill(GameUnit* t)
{
	delete t;
	CCLOG("delete:");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("die.wav");
	int i = -1;
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
