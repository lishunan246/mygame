#pragma once
#include "cocos2d.h"
#include "GameUnit.h"
#include "GameHelper.h"
#include "GameStatus.h"

using namespace std;
class GameMap : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameMap);

	void dealWithTouch();
	GameUnit* getUnitByXY(int x, int y);
	virtual void update(float delta);

private:
	TMXTiledMap* _tileMap=nullptr;
	GameStatus* gameStatus=nullptr;
	int count = 0;
	std::vector<GameUnit*> units;
	GameUnit* currentUnit=nullptr;
};

