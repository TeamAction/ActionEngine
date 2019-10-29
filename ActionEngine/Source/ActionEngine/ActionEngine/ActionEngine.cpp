#define WIDTH 320*3
#define HEIGHT 240*3
#define DRAWLAYERS 5

#define PHYSAC_IMPLEMENTATION
#include "ActionEngine.h"
#include "Actor.h"
#include "tigr.h"
//#include "cute_c2.h" //a library for collision detection


//components
#include "DrawSprite.h"
#include "SampleActorScript.h"

//for console debug
#include <iostream>

ActionEngine* ActionEngine::s_pInstance = 0;


ActionEngine::ActionEngine()
{
	engineActive = true;
	screen = tigrWindow(WIDTH, HEIGHT, "Hello", 0);
	drawList.resize(DRAWLAYERS);
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
	loadedImages.push_back(Scale(tigrLoadImage(filePath),4));
}

void ActionEngine::generateSprite(int index, v2 position, v2 size)
{
	spriteData.push_back(new Sprite{ index,position,size });
}

void ActionEngine::createSampleActor()
{
	loadImage("../../../Assets/gfx/cave.png");
	generateSprite(0, v2(0, 0), v2(loadedImages[0]->w, loadedImages[0]->h));
	//for (int i = 0; i < 10; i++)
	//{

		//Actor* temp = new Actor(v2(i*-2000, i*-2000));
		Actor* temp = new Actor(v2(0,0));

		temp->addComponent("testImage", new DrawSprite(drawObject{ 0,v2(0,0) }, 0));
		temp->addComponent("testScrolling", new SampleActorScript(temp));
		activeActors.push_back(temp);
	//}
}

bool ActionEngine::isGameActive()
{
	return engineActive && !tigrClosed(screen);
}

void ActionEngine::tick()
{
	frameTime = tigrTime();
	std::cout << frameTime*1000 << std::endl;
	for (int i = 0; i < drawList.size(); i++)
	{
		drawList[i].clear();
	}
	for (int i = 0; i < activeActors.size(); i++)
	{
		activeActors[i]->tick(drawList,frameTime);
	}
}

void ActionEngine::draw()
{
	tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));

	for (int i =0;i<drawList.size();i++)
	{
		for (int q = 0; q < drawList[i].size(); q++)
		{
			tigrBlitAlpha(screen, loadedImages[spriteData[drawList[i][q].spriteIndex]->index],
				drawList[i][q].screenPosition.x, drawList[i][q].screenPosition.y,
				spriteData[drawList[i][q].spriteIndex]->positionOnSheet.x, spriteData[drawList[i][q].spriteIndex]->positionOnSheet.y,
				spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.x, spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.y,1.0f);
		}
	}
	tigrUpdate(screen);
}


Tigr* ActionEngine::Scale(Tigr* originalImage,int scale)
{
	Tigr* newImage = tigrBitmap((int)originalImage->w*scale, (int)originalImage->h*scale);
	int nw = (int)originalImage->w*scale;
	int nh = (int)originalImage->h*scale;
	for (int i = 0; i < nh; i++)
		for (int j = 0; j < nw; j++)
			newImage->pix[i*nw + j] = originalImage->pix[(i / scale)*originalImage->w + (j / scale)];
	tigrFree(originalImage);
	return newImage;
}

