#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class GameHelper
{
public:
	static int getDistance(Point p1, Point p2);
	static Point SrceenToMap(Point x);
	static Point MapToScreen(Point x);
	static Point ScreenToScreen(Point x);
	static string intToString(int x);
};

