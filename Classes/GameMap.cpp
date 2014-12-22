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

	this->addChild(_tileMap);

	auto unit = new GameUnit();

	unit->setXY(2, 1);
	this->addChild(unit->getSprite());
	unit->setXY(1, 1);
	dealWithTouch();
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
		point = GameHelper::ScreenToScreen(point);
		
		auto sd = new GameUnit();
		sd->getSprite()->setPosition(point.x, point.y);
		this->addChild(sd->getSprite());
		CCLOG("dd");
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _tileMap);
}

