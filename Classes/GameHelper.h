#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class GameHelper
{
public:
	GameHelper();
	~GameHelper();
	static Point SrceenToMap(Point x);
	static Point MapToScreen(Point x);
	static Point ScreenToScreen(Point x);
	static string intToString(int x);
};

