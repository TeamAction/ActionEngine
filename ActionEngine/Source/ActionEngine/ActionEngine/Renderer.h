#pragma once
#include <vector>
#include <map>
#include "drawHelper.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Rect;
struct drawObject;
struct Sprite;
union SDL_Event;
struct FC_Font;

class Renderer
{
public:
	static Renderer* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Renderer();
		}
		return s_pInstance;
	}

	void loadImageFile(const char* path);
	void ErrorPopup(const char* text);
	void Init();
	bool status();
	void generateSprite(int index, int x, int y, int w, int h);
	void addDrawItem(int layer, drawObject newObject);
	void draw();
	void updateTime();
	float getDeltaTime();
	int getWidth();
	int getHeight();
	v2 getScreenScale();
private:
	void handleInternalEvents(SDL_Event& e);
	void setScreenScale();
	uint64_t NOW = 0;
	uint64_t LAST = 0;
	float deltaTime = 0;

	static Renderer* s_pInstance;
	std::vector<SDL_Texture*> textures;
	std::vector<Sprite> sprites;
	std::map<int, std::vector<drawObject>> renderQueue;
	bool running = false;

//window info
	SDL_Renderer* window_renderer;
	SDL_Window* window;
	FC_Font* pFont;

	int mWidth = 640;
	int mHeight = 480;
	v2 mScreenScale;

	bool mMouseFocus = true;
	bool mKeyboardFocus = true;
	bool mMinimized = false;
	Renderer();
	~Renderer();
};


