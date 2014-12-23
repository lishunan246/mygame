#ifndef GameUnit_h__
#define GameUnit_h__

#include "cocos2d.h"
#include "GameHelper.h"

USING_NS_CC;
using namespace std;

class GameUnit
{
public:
	GameUnit(int player,Node* node);
	~GameUnit();
	Sprite* getSprite();
	Sprite* sprite;
	void setXY(int x, int y);
	Point getXY();
	int x = -1, y = -1;
	int hp = 100;
	int attack = ((int)(rand()))%100;
	int owner;
	string name = "Warrior"+GameHelper::intToString(count);
private:
	Node* node;
	static int count;
	
	
};

#endif // GameUnit_h__
