#pragma once
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class GameHelper
{
public:
	const static int size = 64;
	const static int row = 15;
	const static int col = 30;
	static int getDistance(Point p1, Point p2);
	static Point SrceenToMap(Point x);
	static Point MapToScreen(Point x);
	static Point ScreenToScreen(Point x);
	static string intToString(int x);
};

