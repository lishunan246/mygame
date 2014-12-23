#include "GameUnit.h"

int GameUnit::count = 0;

GameUnit::GameUnit(int player,Node* node)
{
	this->owner = player;
	if (player == 1)
	{
		sprite = Sprite::create("Player.png");
	}
	else
	{
		sprite = Sprite::create("Player2.png");
	}
	
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

bool GameUnit::moveToPoint(Point p)
{
	int c = 0;
	if (p.x > x)
	{
		c += p.x - x;
	}
	else
	{
		c += x - p.x;
	}
	if (p.y > y)
	{
		c += p.y - y;
	}
	else
	{
		c += y - p.y;
	}

	if (c <= stamina)
	{
		stamina -= c;
		setXY(p.x, p.y);
		return true;
	}
	else
	{
		CCLOG("no stamina");
		return false;
	}
}
