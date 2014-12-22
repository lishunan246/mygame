#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameHelper
{
public:
	GameHelper();
	~GameHelper();
	static Point SrceenToMap(Point x);
	static Point MapToScreen(Point x);
	static Point ScreenToScreen(Point x);
};

