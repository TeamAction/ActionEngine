#define WIDTH 320
#define HEIGHT 240

#define PHYSAC_IMPLEMENTATION
#include "ActionEngine.h"
#include "DrawSprite.h"
#include "SampleActorScript.h"
#include "ComponentNameEnum.h"
#include <iostream>

ActionEngine* ActionEngine::s_pInstance = 0;


ActionEngine::ActionEngine()
{
	engineActive = true;
	screen = tigrWindow(WIDTH, HEIGHT, "Hello", 8);
	createSampleActor();
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

void ActionEngine::createSampleActor()
{
	loadImage("../../../Assets/gfx/cave.png");
	generateSprite(0, v2(0, 0), v2(16, 16));
	for (int i = 0; i < 1000; i++)
	{

		Actor* temp = new Actor(v2(i*-20, i*-20));

		temp->addComponent(IMAGE, new DrawSprite(drawObject{ 0,v2(0,0) }, 0));
		temp->addComponent(TEST, new SampleActorScript());
		activeActors.push_back(temp);
	}
}

bool ActionEngine::isGameActive()
{
	return engineActive && !tigrClosed(screen);
}

void ActionEngine::tick()
{
	frameTime = tigrTime();
	std::cout << frameTime*1000 << std::endl;
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
			tigrBlitAlpha(screen, loadedImages[spriteData[it->second[i].spriteIndex]->index],
				it->second[i].screenPosition.x, it->second[i].screenPosition.y,
				spriteData[it->second[i].spriteIndex]->positionOnSheet.x, spriteData[it->second[i].spriteIndex]->positionOnSheet.y,
				spriteData[it->second[i].spriteIndex]->sizeOnSheet.x, spriteData[it->second[i].spriteIndex]->sizeOnSheet.y,1.0f);
		}
		it++;
	}
	tigrUpdate(screen);
}
