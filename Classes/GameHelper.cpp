#include "GameHelper.h"
USING_NS_CC;

GameHelper::GameHelper()
{
}


GameHelper::~GameHelper()
{
}

Point GameHelper::MapToScreen(Point x)
{
	return Point(16 + 32 * x.x, 16 + 32 * x.y);
}

Point GameHelper::SrceenToMap(Point x)
{
	return Point((int)x.x / 32, (int)x.y / 32);
}

Point GameHelper::ScreenToScreen(Point x)
{
	return MapToScreen(SrceenToMap(x));
}
