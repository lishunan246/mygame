#include "GameUnit.h"

int GameUnit::count = 0;

GameUnit::GameUnit(Node* node)
{
	sprite=Sprite::create("Player.png");
	this->node = node;
	node->addChild(sprite);
	count++;
}


GameUnit::~GameUnit()
{
	node->removeChild(sprite);
}

void GameUnit::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
	Point t = GameHelper::MapToScreen(Point(x, y));
	sprite->setPosition(t.x, t.y);
}

Sprite* GameUnit::getSprite()
{
	return sprite;
}

Point GameUnit::getXY()
{
	return Point(x, y);
}
