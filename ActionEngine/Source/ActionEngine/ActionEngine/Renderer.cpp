#pragma once
#include "Renderer.h"
#include "drawHelper.h"
#include "SDL/SDL.h"
#include "SDL/SDL_Image.h"

Renderer* Renderer::s_pInstance = 0;

struct Sprite {
	Sprite(int _Index, SDL_Rect _Bounds) : index(_Index) , bounds(_Bounds) {}
	int index;
	SDL_Rect bounds;
};


void Renderer::loadImageFile(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	if (!surface)
	{
		ErrorPopup(SDL_GetError());
		return;
	}
	textures.push_back(SDL_CreateTextureFromSurface(window_renderer, surface));
	SDL_FreeSurface(surface);
}

void Renderer::ErrorPopup(const char* text)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error",text, NULL);
	running = false;
}

void Renderer::Init()
{
	window = SDL_CreateWindow("Action Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255))
		ErrorPopup(SDL_GetError());

	SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);
	running = true;
}

bool Renderer::status()
{
	return running;
}

void Renderer::generateSprite(int index, int x,int y,int w ,int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	sprites.push_back(Sprite(index, rect));
}

void Renderer::addDrawItem(int layer, drawObject newObject)
{
	renderQueue[layer].push_back(newObject);
}

void Renderer::draw()
{
	SDL_RenderClear(window_renderer);
	std::map<int, std::vector<drawObject>>::iterator it = renderQueue.begin();
	while(it != renderQueue.end())
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			SDL_Rect dest;
			dest.x = it->second[i].screenPosition.x;
			dest.y = it->second[i].screenPosition.y;
			dest.w = sprites[it->second[i].spriteIndex].bounds.w * 4;
			dest.h = sprites[it->second[i].spriteIndex].bounds.h * 4;
			SDL_RenderCopy(window_renderer, textures[sprites[it->second[i].spriteIndex].index], &sprites[it->second[i].spriteIndex].bounds, &dest);
		}
		it->second.clear();
		it++;
	}
	SDL_RenderPresent(window_renderer);
}

void Renderer::updateTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
}

float Renderer::getDeltaTime()
{
	return deltaTime;
}

Renderer::Renderer(){}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(window_renderer);
	SDL_DestroyWindow(window);
	for (int i = 0; i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]);
	}
	textures.clear();
	delete s_pInstance;
	s_pInstance = nullptr;
}

