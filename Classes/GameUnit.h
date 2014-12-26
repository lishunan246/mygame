#ifndef GameUnit_h__
#define GameUnit_h__

#include "cocos2d.h"
#include "GameHelper.h"

USING_NS_CC;
using namespace std;

class GameUnit
{
public:
	GameUnit(int player,Node* node);
	~GameUnit();
	Sprite* getSprite();
	Sprite* sprite;
	void setXY(int x, int y);
	Point getXY();
	void resetLocation();
	bool moveToPoint(Point p);

	const static int price = 100;
	int x = -1, y = -1;
	int ran = rand() % 50;
	int hp = 100-ran;
	int attack = 25 + ran;
	int maxStamina = 5;
	int stamina=hp/20+1;
	int owner;
	string name = "Warrior"+GameHelper::intToString(count);
private:
	Node* node;
	static int count;
	
	
};

#endif // GameUnit_h__
