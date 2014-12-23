#include "GameStatus.h"

GameStatus::GameStatus(Node* node)
{
	this->node = node;

	label = Label::createWithTTF("Hello", font, size);

	// position the label on the center of the screen
	label->setPosition(600, 1000);

	// add the label as a child to this layer
	node->addChild(label, 1);
	label->setString("zero");

	positionX = Label::createWithTTF("X:", font, size);
	positionX->setPosition(1800, 1050);
	node->addChild(positionX, 1);


	positionY = Label::createWithTTF("Y:", font, size);
	positionY->setPosition(1800, 1000);
	node->addChild(positionY, 1);

	name = Label::createWithTTF("Name", font, size);
	name->setPosition(1600, 1050);
	node->addChild(name, 1);

	hp = Label::createWithTTF("HP", font, size);
	hp->setPosition(1600, 1000);
	node->addChild(hp, 1);

	terrain = Label::createWithTTF("terrain", font, size);
	terrain->setPosition(1400, 1000);
	node->addChild(terrain, 1);

	player = Label::createWithTTF("player", font, size);
	player->setPosition(1400, 1050);
	node->addChild(player, 1);
}


GameStatus::~GameStatus()
{
}

void GameStatus::setCount(int count)
{
	label->setString(GameHelper::intToString(count));
}

void GameStatus::showUnit(GameUnit* unit)
{
	if (unit == nullptr)
	{
		name->setString("");
		hp->setString("");
		positionX->setString("");
		positionY->setString("");
		return;
	}
	name->setString(unit->name);
	hp->setString(GameHelper::intToString(unit->hp));
	positionX->setString(GameHelper::intToString(unit->x));
	positionY->setString(GameHelper::intToString(unit->y));
}

void GameStatus::showTerrain(string s)
{
	terrain->setString(s);
}
