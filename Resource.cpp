#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "Renderer.h"
#include "Resource.h"

Resource::Resource()
{
}

Resource::~Resource()
{
}

bool Resource::load(Rndr& rndr)
{
	SDL_Surface* tmpsrfc;
	if (TTF_Init() < 0)
	{
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}

	gFont = TTF_OpenFont("fnt.ttf", charSize);
	if (gFont == nullptr)
	{
		std::cout << "Failed to load font" << SDL_GetError() << std::endl;
		return false;
	}

	//SDL_RWops* rwop = SDL_RWFromFile("spritesheet.png", "rb");
	tmpsrfc = IMG_Load("spritesheet.png");
	spriteSheet = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (spriteSheet == nullptr)
	{
		std::cout << "Failed to load spriteSheet" << SDL_GetError() << std::endl;
		return false;
	}

	SDL_FreeSurface(tmpsrfc);
	return true;
}

SDL_Surface* Resource::loadSurface(Rndr& display, std::string path)
{
	return nullptr;
}

SDL_Texture* Resource::loadTexture(Rndr& display, std::string path)
{
	return nullptr;
}
