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

	_tileMap = TMXTiledMap::create("map.tmx");
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
		return true;
	};

	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		Point point = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
		point = GameHelper::SrceenToMap(point);
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
			//delete currentUnit;
			//count--;
			gameStatus->setCount(count);
			currentUnit = t;
			//gameStatus->showUnit(currentUnit);
			return;
		}
		
		auto sd = new GameUnit(this);
		currentUnit = sd;
		units.push_back(sd);
		sd->setXY(point.x, point.y);
		
		CCLOG("dd");
		count++;
		gameStatus->setCount(count);
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _tileMap);
}

GameUnit* GameMap::getUnitByXY(int x, int y)
{
	for each (GameUnit* var in units)
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
}

