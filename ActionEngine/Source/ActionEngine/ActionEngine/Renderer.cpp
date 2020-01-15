#pragma once
#include "Renderer.h"
#include "drawHelper.h"
#include "SDL/SDL.h"
#include "SDL/SDL_Image.h"
#include "SDL/SDL_FontCache.h"

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
	window = SDL_CreateWindow("Action Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight,SDL_WINDOW_RESIZABLE);
	window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255))
		ErrorPopup(SDL_GetError());
	SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);
	SDL_RenderSetIntegerScale(window_renderer, SDL_TRUE);
	pFont = FC_CreateFont();
	FC_LoadFont(pFont, window_renderer, "../../../Assets/fonts/FreeSans.ttf", 20, FC_MakeColor(255, 255, 255, 255), 0);
	mScreenScale = v2(1, 1);
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
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			handleInternalEvents(event);
	}
	SDL_RenderClear(window_renderer);
	SDL_Rect dest;
	std::map<int, std::vector<drawObject>>::iterator it = renderQueue.begin();
	while(it != renderQueue.end())
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			dest.x = it->second[i].screenPosition.x;
			dest.y = it->second[i].screenPosition.y;
			dest.w = sprites[it->second[i].spriteIndex].bounds.w * (int)(it->second[i].screenScale.x *4.0f);
			dest.h = sprites[it->second[i].spriteIndex].bounds.h * (int)(it->second[i].screenScale.y *4.0f);
			SDL_RenderCopy(window_renderer, textures[sprites[it->second[i].spriteIndex].index], &sprites[it->second[i].spriteIndex].bounds, &dest);
		}
		it->second.clear();
		it++;
	}
	FC_Draw(pFont, window_renderer, 0, 0, "%.4f", getDeltaTime());
	SDL_RenderPresent(window_renderer);
}

void Renderer::updateTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (mKeyboardFocus && !mMinimized)?(double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency()):0.0f;
}

float Renderer::getDeltaTime()
{
	return deltaTime;
}

int Renderer::getWidth()
{
	return mWidth;
}

int Renderer::getHeight()
{
	return mHeight;
}

v2 Renderer::getScreenScale()
{
	return mScreenScale;
}

void Renderer::handleInternalEvents(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			setScreenScale();
			FC_ResetFontFromRendererReset(pFont, window_renderer, e.window.type);
			SDL_RenderPresent(window_renderer);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(window_renderer);
			break;
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			break;

		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			break;

		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		}
	}
}

void Renderer::setScreenScale()
{
	mScreenScale.x = mWidth / 640.0f;
	mScreenScale.y = mHeight / 480.0f;
}

Renderer::Renderer(){}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(window_renderer);
	SDL_DestroyWindow(window);
	FC_FreeFont(pFont);
	for (int i = 0; i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]);
	}
	textures.clear();
	delete s_pInstance;
	s_pInstance = nullptr;
}
