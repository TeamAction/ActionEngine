#pragma once
#include <unordered_map>

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
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	void loadImage(const char* filePath);
	void generateSprite(int index, v2 position, v2 size);
	void createSampleActor();
	Tigr* Scale(Tigr* originalImage, int scale);

	Tigr *screen;
	std::vector<Actor*> activeActors;
	std::vector<Tigr*> loadedImages;
	std::vector<Sprite*> spriteData;
	std::vector<std::vector<drawObject>> drawList;

	bool engineActive;
	float frameTime;
};


