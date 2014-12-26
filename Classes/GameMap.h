#ifndef GameMap_h__
#define GameMap_h__

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "GameUnit.h"
#include "GameHelper.h"
#include "GameStatus.h"
#include "GameEndScene.h"
#include "GameEndScene1.h"

using namespace std;

enum Mode
{
	normal, moveUnit
};

class GameMap : public cocos2d::Layer
{
public:
	GameMap();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void newUnitCallback(cocos2d::Ref* pSender);
	void endTurnCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameMap);

	void dealWithTouch();

	void kill(GameUnit* t);

	bool newUnit();	

	string getType(Point point);

	GameUnit* getUnitByXY(int x, int y);
	virtual void update(float delta);

private:
	TMXTiledMap* _tileMap=nullptr;
	TMXLayer* ground=nullptr;
	GameStatus* gameStatus=nullptr;
	int count = 0;
	std::vector<GameUnit*> units;
	std::vector<Sprite*> oks;
	GameUnit* currentUnit=nullptr;
	Mode mode = normal;

	//current player can be 1 or 2
	int currentPlayer = 1;
	int money[3];
	Point startPoint;
	Sprite* moveAble = Sprite::create("ok.png");
	const int maxHP=100;
	const int mapCount = 3;
};

#endif // GameMap_h__