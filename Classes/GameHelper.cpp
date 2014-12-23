#include "GameHelper.h"
USING_NS_CC;
using namespace std;

Point GameHelper::MapToScreen(Point x)
{
	return Point(16 + 32 * x.x, 16 + 32 * (29-x.y));
}

Point GameHelper::SrceenToMap(Point x)
{
	return Point((int)x.x / 32, 29-(int)x.y / 32);
}

Point GameHelper::ScreenToScreen(Point x)
{
	return MapToScreen(SrceenToMap(x));
}

string GameHelper::intToString(int number){
    string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
            default : CCLOG("Trouble converting number to string.");
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}

int GameHelper::getDistance(Point p1, Point p2)
{
	int c = 0;
	if (p1.x > p2.x)
	{
		c += p1.x - p2.x;
	}
	else
	{
		c += p2.x - p1.x;
	}
	if (p1.y > p2.y)
	{
		c += p1.y - p2.y;
	}
	else
	{
		c += p2.y - p1.y;
	}
	return c;
}
