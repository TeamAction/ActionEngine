#pragma once
#include <vector>
#include <map>
#include <string>
#include "helperStructs.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Rect;
struct drawObject;
struct Sprite;
union SDL_Event;
struct FC_Font;

struct screenText
{
	int x,y;
	float time;
	std::string text;
};

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
	void loadImageFile(const char* path, int& w, int& h);
	void ErrorPopup(const char* text);
	void Init(int w, int h, const char* fontPath, int fontSize);
	void showSplash(const char* path);
	bool status();
	void generateSprite(int index, int x, int y, int w, int h);
	void addDrawItem(int layer, drawObject newObject);
	void addScreenText(int x,int y,std::string text,float timer);
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
	std::vector<screenText> renderText;
	bool running = false;

//window info
	SDL_Renderer* window_renderer;
	SDL_Window* window;
	FC_Font* pFont;

	int mWidth;
	int mHeight;
	int mInitWidth;
	int mInitHeight;
	std::string mFontPath;
	int mFontSize;
	v2 mScreenScale;

	bool mMouseFocus = true;
	bool mKeyboardFocus = true;
	bool mMinimized = false;
	Renderer();
	~Renderer();
};


