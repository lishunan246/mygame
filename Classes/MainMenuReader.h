#ifndef MainMenuReader_h__
#define MainMenuReader_h__
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class MainMenuReader :	public cocostudio::NodeReader
{
public:
	MainMenuReader();
	~MainMenuReader();
	static MainMenuReader* getInstance();
	static void purge();
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif // MainMenuReader_h__
