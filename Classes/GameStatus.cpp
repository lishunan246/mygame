#include "GameStatus.h"

GameStatus::GameStatus(Node* node)
{
	this->node = node;

	label = Label::createWithTTF("0", font, size);

	// position the label on the center of the screen
	label->setPosition(600, 1000);

	// add the label as a child to this layer
	node->addChild(label, 1);

	player = Label::createWithTTF("player", font, size);
	player->setPosition(600, 1050);
	node->addChild(player, 1);


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

	owner = Label::createWithTTF("owner", font, size);
	owner->setPosition(1400, 1050);
	node->addChild(owner, 1);

	attack = Label::createWithTTF("attack", font, size);
	attack->setPosition(1200, 1050);
	node->addChild(attack, 1);

	stm = Label::createWithTTF("stm", font, size);
	stm->setPosition(1200, 1000);
	node->addChild(stm, 1);
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
		owner->setString("");
		attack->setString("");
		stm->setString("");
		return;
	}
	name->setString(unit->name);
	hp->setString(GameHelper::intToString(unit->hp));
	positionX->setString(GameHelper::intToString(unit->x));
	positionY->setString(GameHelper::intToString(unit->y));
	attack->setString("atk: " + GameHelper::intToString(unit->attack));
	stm->setString("stm: " + GameHelper::intToString(unit->stamina));
	if (unit->owner == 1)
	{
		owner->setString("Player1");
	}
	else
	{
		owner->setString("Player2");
	}
}

void GameStatus::showTerrain(string s)
{
	terrain->setString(s);
}

void GameStatus::showPlayer(string s)
{
	player->setString(s);
}
