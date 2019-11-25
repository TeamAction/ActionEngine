#pragma once
#include <vector>

//forward declared classes and structs
struct Tigr;
class Actor;
struct v2;
struct Sprite;
struct drawObject;
class InputInterface;
typedef void *HANDLE;

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


	InputInterface* getInputInterface();

	void play();
	void addActor(Actor* actor);
	void addDrawItem(int layer, drawObject newObject);
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	void loadImage(const char* filePath);
	void generateSprite(int index, v2 position, v2 size);
	void createSampleActor();
	bool isGameActive();
	void tick();
	void draw();
	void deleteFlaggedActors();

	Tigr *screen;
	std::vector<Actor*> activeActors;
	std::vector<Tigr*> loadedImages;
	std::vector<Sprite*> spriteData;
	std::vector<std::vector<drawObject>> drawList;
	InputInterface* input;

	bool engineActive = false;
	float frameTime;


	HANDLE hHandle;
	float timer = 2.0f;
};


