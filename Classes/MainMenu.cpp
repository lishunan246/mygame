#include "MainMenu.h"
#include "MainMenuReader.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("MainMenuReader", (ObjectFactory::Instance)MainMenuReader::getInstance);

	auto node = CSLoader::getInstance()->createNode("MainMenu.csb");
	
	this->addChild(node);

	return true;
}

cocos2d::ui::Widget::ccWidgetClickCallback MainMenu::onLocateClickCallback(const std::string &callBackName)
{

	if (callBackName == "quit")
	{
		return CC_CALLBACK_1(MainMenu::onClick, this);
	}
	return nullptr;
}

void MainMenu::onClick(cocos2d::Ref* sender)
{
	CCLOG("onClick");
}
