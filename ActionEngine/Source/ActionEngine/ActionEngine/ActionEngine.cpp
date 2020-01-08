#define WIDTH 640
#define HEIGHT 480
#define DRAWLAYERS 5

#define DEBUG
#include "ActionEngine.h"
#include "Actor.h"
#include "tigr.h"
#include "InputManager.h"
#include "Initialize.h"


//components
#include "DrawSprite.h"
#include "SampleActorScript.h"
#include "SampleActorSpawnScript.h"
#include "SampleMouseClickScript.h"

#ifdef DEBUG
#include <iostream>
#endif  DEBUG


ActionEngine* ActionEngine::s_pInstance = 0;


ActionEngine::ActionEngine()
{
	if (!Initialize::IsOnlyInstance("MyGame", &hHandle))
		return;
	if (!Initialize::CheckAvailibleMemory(300000, 300000)) // memory in kb
		return;
	if (!Initialize::CheckStorage(300)) // memory in mb
		return;
	Initialize::checkSystem();
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
	tigrFree(screen);
	screen = nullptr;
	delete s_pInstance;
	s_pInstance = nullptr;
	Initialize::Terminate(&hHandle);
}

void ActionEngine::loadImage(const char* filePath)
{
	loadedImages.push_back(tigrScale(tigrLoadImage(filePath),4,4));
}

void ActionEngine::generateSprite(int index, v2 position, v2 size)
{
	spriteData.push_back(new Sprite{ index,position,size });
}

void ActionEngine::createSampleActor()
{
	loadImage("../../../Assets/gfx/cave.png");
	generateSprite(0, v2(64 * 6, 64 * 8), v2(64,64));
	generateSprite(0, v2(64*7, 64*9), v2(64,64));

	{
		Actor* temp = new Actor();
		temp->addComponent("testSpawning", new SampleActorMouseClick());
		activeActors.push_back(temp);
	}


	for (int j = 0; j < HEIGHT/64 +1; j++)
	{
		Actor* temp = new Actor();
		temp->addComponent("testSpawning", new SampleActorSpawnScript());
		temp->addComponent("transform", new DataInterface<v2>(v2(-64, j * 64)));
		activeActors.push_back(temp);
	}
	for (int i = 0;i < WIDTH / 64 + 1; i++)
	{
		for (int j = 0; j < HEIGHT / 64 + 1; j++)
		{
			Actor* temp = new Actor();
			temp->addComponent("testImage", new DrawSprite(drawObject(0, v2(0, 0)), 0));
			temp->addComponent("transform", new DataInterface<v2>(v2(i * 64, j * 64)));
			activeActors.push_back(temp);
		}
	}

}

bool ActionEngine::isGameActive()
{
	return engineActive && !tigrClosed(screen);
}

void ActionEngine::tick()
{
	frameTime = tigrTime();	
	//input->prossesInput(screen);
	if (InputManager::Instance()->getKeyDown(' '))
	{
		EventManager::Instance()->fireEvent("spaceKey");
	}
	InputManager::Instance()->updateMouse();
	if (InputManager::Instance()->getMouseLeftButton())
	{
		EventManager::Instance()->fireEvent("click to spawn");
	}
	for (int i = 0; i < activeActors.size(); i++)
	{
		activeActors[i]->tick(frameTime);
	}
}

void ActionEngine::draw()
{
	tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));

	for (int i =0;i< DRAWLAYERS;i++)
	{
		for (int q = 0; q < drawList[i].size(); q++)
		{
				tigrBlitAlphaClip(screen, loadedImages[spriteData[drawList[i][q].spriteIndex]->index],
					drawList[i][q].screenPosition.x, drawList[i][q].screenPosition.y,
					spriteData[drawList[i][q].spriteIndex]->positionOnSheet.x, spriteData[drawList[i][q].spriteIndex]->positionOnSheet.y,
					spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.x, spriteData[drawList[i][q].spriteIndex]->sizeOnSheet.y,0.99f);
		}
		drawList[i].clear();
	}
#ifdef DEBUG

	char output[32];
	sprintf_s(output, "FrameTime: %.2f ms", frameTime*1000);
	tigrPrint(screen, tfont, WIDTH-tigrTextWidth(tfont, output)-10, 10, tigrRGB(0xff, 0xff, 0xff),output);

	sprintf_s(output, "Number of Actors: %d", activeActors.size());
	tigrPrint(screen, tfont, WIDTH - tigrTextWidth(tfont, output) - 10,12 + tigrTextHeight(tfont, output), tigrRGB(0xff, 0xff, 0xff), output);
	

	sprintf_s(output, "Mouse Position: %d, %d", InputManager::Instance()->getMouseX(), InputManager::Instance()->getMouseY());
	tigrPrint(screen, tfont, WIDTH - tigrTextWidth(tfont, output) - 10,10 + ((2 + tigrTextHeight(tfont, output))*2), tigrRGB(0xff, 0xff, 0xff), output);
	sprintf_s(output, "Mouse Buttons: %d ,%d ,%d", InputManager::Instance()->getMouseLeftButton(), 0, InputManager::Instance()->getMouseRightButton());
	tigrPrint(screen, tfont, WIDTH - tigrTextWidth(tfont, output) - 10, 10 + ((2 + tigrTextHeight(tfont, output)) * 3), tigrRGB(0xff, 0xff, 0xff), output);


	char buffer[1024];
	sprintf_s(buffer, "Keys Down:");
	for (int i = 0; i < 256; i++)
	{
		if (InputManager::Instance()->getKeyDown(i))
		{
			sprintf_s(output, " %c,",i);
			strcat_s(buffer, output);
		}
	}
	tigrPrint(screen, tfont, WIDTH - tigrTextWidth(tfont, buffer) - 10, 10 + ((2 + tigrTextHeight(tfont, buffer)) * 4), tigrRGB(0xff, 0xff, 0xff), buffer);

#endif  DEBUG
	tigrUpdate(screen);
}

void ActionEngine::deleteFlaggedActors()
{
	for (int i = 0; i < activeActors.size(); i++)
	{
		if (activeActors[i]->actorToBeRemoved())
		{
			delete activeActors[i];
			activeActors.erase(activeActors.begin() + i);
		}
	}
}


void ActionEngine::play()
{
	while (isGameActive())
	{

		tick();
		deleteFlaggedActors();
		draw();
	}
}

void ActionEngine::addActor(Actor * actor)
{
	activeActors.push_back(actor);
}

void ActionEngine::addDrawItem(int layer,drawObject newObject)
{
	drawList[layer].push_back(newObject);
}
