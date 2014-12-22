#include "GameStatus.h"

GameStatus::GameStatus(Node* node)
{
	this->node = node;

	label = Label::createWithTTF("Hello", font, size);

	// position the label on the center of the screen
	label->setPosition(40, 1000);

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
}


GameStatus::~GameStatus()
{
}

void GameStatus::setCount(int count)
{
	label->setString(std::to_string(count));
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
	hp->setString(to_string(unit->hp));
	positionX->setString(to_string(unit->x));
	positionY->setString(to_string(unit->y));
}
