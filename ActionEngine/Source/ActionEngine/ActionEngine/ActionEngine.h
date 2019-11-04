#pragma once
#include <vector>

//forward declared classes and structs
struct Tigr;
class Actor;
struct v2;
struct Sprite;
struct drawObject;

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
	void deleteFlaggedActors();

	void addActor(Actor* actor);
	void addDrawItem(int layer, drawObject newObject);
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	void loadImage(const char* filePath);
	void generateSprite(int index, v2 position, v2 size);
	void createSampleActor();
	Tigr* Scale(Tigr* originalImage, float xScale, float yScale);

	Tigr *screen;
	std::vector<Actor*> activeActors;
	std::vector<Tigr*> loadedImages;
	std::vector<Sprite*> spriteData;
	std::vector<std::vector<drawObject>> drawList;

	bool engineActive;
	float frameTime;



	float timer = 2.0f;
};


