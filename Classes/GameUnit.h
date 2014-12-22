#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameUnit
{
public:
	GameUnit();
	~GameUnit();
	Sprite* getSprite();
	Sprite* sprite;
	void setXY(int x, int y);
};

