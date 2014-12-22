#include "GameUnit.h"


GameUnit::GameUnit()
{
	sprite=Sprite::create("Player.png");
}


GameUnit::~GameUnit()
{
}

void GameUnit::setXY(int x, int y)
{
	sprite->setPosition(16 + 32 * x, 16 + 32 * y);
}

Sprite* GameUnit::getSprite()
{
	return sprite;
}
