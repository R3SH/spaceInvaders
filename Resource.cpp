#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Game.h"
#include "Renderer.h"
#include "Resource.h"

Resource::Resource()
{
}

Resource::~Resource()
{
	Mix_FreeChunk(menuPress);
	Mix_FreeChunk(menuBack);
	Mix_FreeChunk(plrHit);
	Mix_FreeChunk(plrDeath);
	Mix_FreeChunk(plrShoot);
	Mix_FreeChunk(plrLiveUp);
	Mix_FreeChunk(enemySpawn);
	Mix_FreeChunk(enemyShoot);
	Mix_FreeChunk(droneDeath);
	Mix_FreeChunk(alienDeath);
	Mix_FreeChunk(overseerDeath);
	scoreBoardFile.close();
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

	tmpsrfc = IMG_Load("background.png");
	background = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (background == nullptr)
	{
		std::cout << "Failed to load background" << SDL_GetError() << std::endl;
		return false;
	}

	scoreBoardName = "scoreBoard.txt";
	scoreBoardFile.open(scoreBoardName.c_str());
	for (int i = 0; i < 10 && scoreBoardFile; ++i)
	{
		scoreStr[i] = u8"";
		getline(scoreBoardFile, scoreStr[i]);
		std::cout << scoreStr[i] << std::endl;
	}

	menuPress = Mix_LoadWAV("sounds/menuPress.wav");
	if (menuPress == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		return false;
	}
	menuSwitch = Mix_LoadWAV("sounds/menuSwitch.wav");
	if (menuSwitch == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		return false;
	}
	menuBack = Mix_LoadWAV("sounds/menuBack.wav");
	if (menuBack == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		return false;
	}
	plrHit = Mix_LoadWAV("sounds/plrHit.wav");
	if (plrHit == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		return false;
	}
	plrDeath = Mix_LoadWAV("sounds/plrDth.wav");
	if (plrDeath == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	plrShoot = Mix_LoadWAV("sounds/plrShoot.wav");
	if (plrShoot == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	plrLiveUp = Mix_LoadWAV("sounds/plrLiveUp.wav");
	if (plrLiveUp == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	enemySpawn = Mix_LoadWAV("sounds/enemySpawn.wav");
	if (enemySpawn == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	enemyShoot = Mix_LoadWAV("sounds/enemyShoot.wav");
	if (enemyShoot == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	droneDeath = Mix_LoadWAV("sounds/drnDth.wav");
	if (droneDeath == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	alienDeath = Mix_LoadWAV("sounds/alnDth.wav");
	if (alienDeath == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	overseerDeath = Mix_LoadWAV("sounds/overseerDth.wav");
	if (overseerDeath == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
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
