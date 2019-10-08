#pragma once
#include "Actor.h"
#include "tigr.h"
#include "cute_c2.h"
#include "helper.h"
#include <unordered_map>


struct Sprite
{
	int index;
	v2 positionOnSheet;
	v2 sizeOnSheet;
};

class ActionEngine
{
public:
	static ActionEngine* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new ActionEngine();
		}
		return s_pInstance;
	}


	bool isGameActive();
	void tick();
	void draw();
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	bool engineActive;
	float frameTime;
	void loadImage(const char* filePath);
	void generateSprite(int index, v2 position, v2 size);
	Tigr *screen;
	std::vector<Actor*> activeActors;
	std::vector<Tigr*> loadedImages;
	std::vector<Sprite*> spriteData;
	std::unordered_map<int,std::vector<drawObject>> drawList;
};


