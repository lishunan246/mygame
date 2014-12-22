#ifndef MainMenu_h__
#define MainMenu_h__

#include "cocos2d.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

class MainMenu:public cocos2d::Layer,public cocostudio::WidgetCallBackHandlerProtocol
{
public:
	MainMenu();
	~MainMenu();

	virtual cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName);
	void onClick(cocos2d::Ref* sender);

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenu);

private:
	std::string _click;
};

#endif // MainMenu_h__
