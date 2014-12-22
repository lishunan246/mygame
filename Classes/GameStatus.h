#pragma once
#include "cocos2d.h"
#include "GameUnit.h"
USING_NS_CC;

class GameStatus
{
public:
	GameStatus(Node* node);
	~GameStatus();
	void setCount(int count);
	void showUnit(GameUnit* unit);
private:
	Node* node;
	std::string font = "fonts/Marker Felt.ttf";
	int size = 40;
	Label* label,*positionX,*positionY,*name,*hp;
};

