#pragma once
#include <vector>
#include <map>


struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
struct v2;
struct SDL_Rect;
struct drawObject;
struct Sprite;

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

	SDL_Renderer* window_renderer;
	SDL_Window* window;
	void loadImageFile(const char* path);
	void ErrorPopup(const char* text);
	void Init();
	bool status();
	void generateSprite(int index, int x, int y, int w, int h);
	void addDrawItem(int layer, drawObject newObject);
	void draw();
	void updateTime();
	float getDeltaTime();

private:
	uint64_t NOW = 0;
	uint64_t LAST = 0;
	double deltaTime = 0;

	static Renderer* s_pInstance;
	std::vector<SDL_Texture*> textures;
	std::vector<Sprite> sprites;
	std::map<int, std::vector<drawObject>> renderQueue;
	bool running = false;
	Renderer();
	~Renderer();
};


