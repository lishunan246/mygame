#include "MainMenuReader.h"
#include "MainMenu.h"

USING_NS_CC;
static MainMenuReader* _instanceMainMenuReader = nullptr;
MainMenuReader::MainMenuReader()
{
}


MainMenuReader::~MainMenuReader()
{
}

MainMenuReader* MainMenuReader::getInstance()
{
	if (!_instanceMainMenuReader)
	{
		_instanceMainMenuReader = new MainMenuReader();
	}
	return _instanceMainMenuReader;
}

void MainMenuReader::purge()
{
	CC_SAFE_DELETE(_instanceMainMenuReader);
}

cocos2d::Node* MainMenuReader::createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions)
{
	MainMenu* node = MainMenu::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
}
