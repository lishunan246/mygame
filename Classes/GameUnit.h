#pragma once
#include "cocos2d.h"
#include "GameHelper.h"
USING_NS_CC;
using namespace std;
class GameUnit
{
public:
	GameUnit(Node* node);
	~GameUnit();
	Sprite* getSprite();
	Sprite* sprite;
	void setXY(int x, int y);
	Point getXY();
	int x = -1, y = -1;
	int hp = 100;
	string name = "Warrior"+to_string(count);
private:
	Node* node;
	static int count;
};

