#define PHYSAC_IMPLEMENTATION
#include "ActionEngine.h"

ActionEngine* ActionEngine::s_pInstance = 0;


ActionEngine::ActionEngine()
{
	engineActive = true;
	screen = tigrWindow(320, 240, "Hello", 8);
	loadImage("../../../Assets/gfx/cave.png");
	generateSprite(0,v2(0,0),v2(150,150));

	std::vector<drawObject> test;
	test.push_back(drawObject{ 0,v2(0,0) });
	activeActors.push_back(new Actor(v2(0,0),test));
}


ActionEngine::~ActionEngine()
{
	for (int i = 0; i < spriteData.size(); i++)
	{
		delete spriteData[i];
		spriteData[i] = nullptr;
	}
	for (int i = 0; i < activeActors.size(); i++)
	{
		delete activeActors[i];
		activeActors[i] = nullptr;
	}
	for (int i = 0; i < loadedImages.size(); i++)
	{
		tigrFree(loadedImages[i]);
		loadedImages[i] = nullptr;
	}
	delete s_pInstance;
	s_pInstance = nullptr;
	tigrFree(screen);
	screen = nullptr;
}

void ActionEngine::loadImage(const char* filePath)
{
	loadedImages.push_back(tigrLoadImage(filePath));
}

void ActionEngine::generateSprite(int index, v2 position, v2 size)
{
	Sprite *temp = new Sprite{index,position,size};
	spriteData.push_back(temp);
	temp = nullptr;
}

bool ActionEngine::isGameActive()
{
	return engineActive && !tigrClosed(screen);
}

void ActionEngine::tick()
{
	frameTime = tigrTime();
	drawList.clear();
	for (int i = 0; i < activeActors.size(); i++)
	{
		activeActors[i]->tick(drawList,frameTime);
	}
}

void ActionEngine::draw()
{
	tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));

	std::unordered_map<int, std::vector<drawObject>>::iterator it = drawList.begin();
	while (it != drawList.end())
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			tigrBlit(screen, loadedImages[spriteData[it->second[i].spriteIndex]->index],
				it->second[i].screenPosition.v[0], it->second[i].screenPosition.v[1],
				spriteData[it->second[i].spriteIndex]->positionOnSheet.v[0], spriteData[it->second[i].spriteIndex]->positionOnSheet.v[1],
				spriteData[it->second[i].spriteIndex]->sizeOnSheet.v[0], spriteData[it->second[i].spriteIndex]->sizeOnSheet.v[1]);
		}
		it++;
	}
	tigrUpdate(screen);
}
