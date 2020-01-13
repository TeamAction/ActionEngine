#pragma once
#define WIDTH 640
#define HEIGHT 480

#include "ActionEngine.h"
#include "Actor.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Initialize.h"


//components
#include "DrawSprite.h"
#include "SampleActorScript.h"
#include "SampleActorSpawnScript.h"
#include "SampleMouseClickScript.h"



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
	Renderer::Instance()->Init();
	sceneRoot = new Actor("SceneRoot",nullptr);
	createSampleActor();
	Renderer::Instance()->updateTime();
}



ActionEngine::~ActionEngine()
{
	sceneRoot->flagActorForRemoval();
	sceneRoot->removeFlaggedActors();
	delete s_pInstance;
	s_pInstance = nullptr;
	Initialize::Terminate(&hHandle);
}
void ActionEngine::createSampleActor()
{
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/cave.png");
	Renderer::Instance()->generateSprite(0, 16 * 6, 16 * 8, 16,16);
	Renderer::Instance()->generateSprite(0, 16 * 7, 16 *9, 16,16);

	//Actor* temp = new Actor("Test SDL rendering", sceneRoot);
	//temp->addComponent("testScrolling", new SampleActorScript());
	//temp->addComponent("scrolling square", new DrawSprite(drawObject(0, v2(0, 0)), 0));

	Actor* temp = new Actor("Mouse Click Spawner", sceneRoot);
	temp->addComponent("testSpawning", new SampleActorMouseClick());
	for (int j = 0; j < HEIGHT/64+1; j++)
	{
		temp = new Actor("Space Bar Spawner",sceneRoot);
		temp->addComponent("testSpawning", new SampleActorSpawnScript());
		temp->addComponent("transform", new DataInterface<v2>(v2(-64.0f, j * 64.0f)));
	}
 	//temp = new Actor("background",sceneRoot);
	//temp->addComponent("testImage", new DrawSprite(drawObject(2, v2(0, 0)), 0));
}

bool ActionEngine::isGameActive()
{
	return engineActive && Renderer::Instance()->status();
}

void ActionEngine::play()
{
	bool test = Renderer::Instance()->status();
	while (isGameActive())
	{
		Renderer::Instance()->updateTime();
		InputManager::Instance()->fireInputEvents();
		sceneRoot->tick(Renderer::Instance()->getDeltaTime());
		sceneRoot->removeFlaggedActors();
		Renderer::Instance()->draw();
	}
}