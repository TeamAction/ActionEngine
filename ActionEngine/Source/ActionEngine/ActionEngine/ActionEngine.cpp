#define WIDTH 640
#define HEIGHT 480
#define DRAWLAYERS 5

#define DEBUG

#include "ActionEngine.h"
#include "Actor.h"
#include "tigr.h"


//components
#include "DrawSprite.h"
#include "SampleActorScript.h"

#ifdef DEBUG
#include <iostream>
#endif  DEBUG


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
	loadedImages.push_back(Scale(tigrLoadImage(filePath),4,4));
}

void ActionEngine::generateSprite(int index, v2 position, v2 size)
{
	spriteData.push_back(new Sprite{ index,position,size });
}

void ActionEngine::createSampleActor()
{
	loadImage("../../../Assets/gfx/cave.png");
	generateSprite(0, v2(0, 0), v2(loadedImages[0]->w, loadedImages[0]->h));
	//for (int i = 0; i < 100; i++)
	//{
		//Actor* temp = new Actor(v2(0,0));

		//temp->addComponent("testImage", new DrawSprite(drawObject{ 0,v2(0,0),false}, 0));
		//temp->addComponent("testScrolling", new SampleActorScript(temp));
		//activeActors.push_back(temp);
	//}
}

bool ActionEngine::isGameActive()
{
	return engineActive && !tigrClosed(screen);
}

void ActionEngine::tick()
{
	frameTime = tigrTime();



//test actor spawning and deletion
	timer += frameTime;
	if (timer >= 1.0f)
	{
		Actor* temp = new Actor(v2(-500,-500));

		temp->addComponent("testImage", new DrawSprite(drawObject( 0,v2(0,0),true ), 0));
		temp->addComponent("testScrolling", new SampleActorScript(temp));
		activeActors.push_back(temp);
		timer = 0;
	}



	
	for (int i = 0; i < DRAWLAYERS; i++)
	{
		drawList[i].clear();
	}
	for (int i = 0; i < activeActors.size(); i++)
	{
		activeActors[i]->tick(drawList,frameTime);
		if (activeActors[i]->actorToBeRemoved())
		{
			delete activeActors[i];
			activeActors.erase(activeActors.begin() + i);
		}
	}
}

void ActionEngine::draw()
{
	tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));

	for (int i =0;i< DRAWLAYERS;i++)
	{
		for (int q = 0; q < drawList[i].size(); q++)
		{
			if (drawList[i][q].alpha)
			{
				tigrFastBlitAlpha(screen, loadedImages[spriteData[drawList[i][q].spriteIndex]->index],
					drawList[i][q].screenPosition.x, drawList[i][q].screenPosition.y,
					spriteData[drawList[i][q].spriteIndex]->positionOnSheet.x, spriteData[drawList[i][q].spriteIndex]->positionOnSheet.y,
					spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.x, spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.y,0.5f);
			}
			else
			{
				tigrBlit(screen, loadedImages[spriteData[drawList[i][q].spriteIndex]->index],
					drawList[i][q].screenPosition.x, drawList[i][q].screenPosition.y,
					spriteData[drawList[i][q].spriteIndex]->positionOnSheet.x, spriteData[drawList[i][q].spriteIndex]->positionOnSheet.y,
					spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.x, spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.y);
			}
		}
	}
#ifdef DEBUG

	char output[32];
	sprintf_s(output, "FrameTime: %.2f", frameTime*1000);
	tigrPrint(screen, tfont, WIDTH-tigrTextWidth(tfont, output)-10, 10, tigrRGB(0xff, 0xff, 0xff),output);

	sprintf_s(output, "Number of Actors: %d", activeActors.size());
	tigrPrint(screen, tfont, WIDTH - tigrTextWidth(tfont, output) - 10,12 + tigrTextHeight(tfont, output), tigrRGB(0xff, 0xff, 0xff), output);


#endif  DEBUG
	tigrUpdate(screen);
}


Tigr* ActionEngine::Scale(Tigr* originalImage,float xScale, float yScale)
{
	Tigr* newImage = tigrBitmap(originalImage->w*xScale,originalImage->h*yScale);
	int nw = originalImage->w*xScale;
	int nh = originalImage->h*yScale;
	for (int i = 0; i < nh; i++)
	{
		for (int j = 0; j < nw; j++)
		{
			newImage->pix[(i*(nw))+j] = originalImage->pix[((int)(i/yScale)*(originalImage->w)) + (int)(j/xScale)];
		}
	}
	tigrFree(originalImage);
	return newImage;
}

