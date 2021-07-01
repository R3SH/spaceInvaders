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

void Resource::setName(std::string* name, int score)
{
	int tmp = INT_MAX, indx = -1;			//NOOOOOOOOOOOOOOOO
	std::string tmps = u8"";
	std::string tmpNumb;
	std::cout << scoreBoardName << std::endl;
	scoreBoardFile.close();
	//scoreBoardFile.open(scoreBoardName.c_str(), std::ios::trunc);
	std::fstream wFile(scoreBoardName);
	tmps = (*name);

	if (strNumb == N_SC_BOARD)
	{
		for (int i = 0; i < strNumb; ++i)
		{
			if (tmp <= scoresTable[i])
			{
				tmp = scoresTable[i];
				indx = i;
				std::cout << "Index " << tmp << std::endl;
			}
		}
		if (indx != -1)
		{
			scoreStr[indx] = tmps;
			scoresTable[indx] = score;
			std::cout << "Passed name: " << scoreStr[indx] << "score: " << scoresTable[indx] << std::endl;
		}
	}
	else
	{
		scoreStr[strNumb] = tmps;
		scoresTable[strNumb] = score;
		++strNumb;
		std::cout << "Passed name: " << scoreStr[strNumb] << "score: " << scoresTable[strNumb] << std::endl;
	}

	for (int i = 0; i < strNumb - 1; ++i)
	{
		for (int j = 0; j < strNumb - i - 1; ++j)
		{
			if (scoresTable[j] > scoresTable[j + 1])
			{
				tmp = scoresTable[j];
				tmps = scoreStr[j];
				scoresTable[j] = scoresTable[j + 1];
				scoreStr[j] = scoreStr[j + 1];
				scoresTable[j + 1] = tmp;
				scoreStr[j + 1] = tmps; 
			}

		}
	}

	for (int i = strNumb - 1; i >= 0; --i)
	{
		std::cout << scoreStr[i] << '\t' << scoresTable[i] << std::endl;
		wFile << scoreStr[i] << '\n' << scoresTable[i] << '\n';
		//scoreStr[strNumb] = u8"";
		//getline(scoreBoardFile, scoreStr[strNumb]);
		std::cout << "i " << i << '\t' << scoreStr[strNumb] << std::endl;
	}

	wFile.seekg(0, std::ios::beg);

	for (int i = 0; i < strNumb; ++i)
	{
		scoreStr[i] = u8"";
		getline(wFile, scoreStr[i]);
		getline(wFile, tmps);
		scoresTable[i] = std::stoi(tmps);
		std::cout << "strNumb = " << strNumb << " name: " << scoreStr[i] << "score: " << scoresTable[i] << " i: " << i << " i: " << i << std::endl;
	}


	wFile.close();
}

bool Resource::load(Rndr& rndr)
{
	int tmp;
	std::string tmps;
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
	tmpsrfc = IMG_Load("imgs/spritesheet.png");
	spriteSheet = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (spriteSheet == nullptr)
	{
		std::cout << "Failed to load spriteSheet" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FreeSurface(tmpsrfc);

	tmpsrfc = IMG_Load("imgs/background.png");
	background = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (background == nullptr)
	{
		std::cout << "Failed to load background" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FreeSurface(tmpsrfc);

	tmpsrfc = IMG_Load("imgs/arrowKeys.png");
	arrowKeys = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (arrowKeys == nullptr)
	{
		std::cout << "Failed to load arrowKeys" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FreeSurface(tmpsrfc);

	tmpsrfc = IMG_Load("imgs/spaceBar.png");
	spaceBar = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (spaceBar == nullptr)
	{
		std::cout << "Failed to load spaceBar" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FreeSurface(tmpsrfc);

	tmpsrfc = IMG_Load("imgs/escKey.png");
	escKey = SDL_CreateTextureFromSurface(rndr.getRenderer(), tmpsrfc);
	if (escKey == nullptr)
	{
		std::cout << "Failed to load escKey" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FreeSurface(tmpsrfc);

	scoreBoardName = "scoreBoard.txt";
	scoreBoardFile.open(scoreBoardName.c_str());
	for (strNumb = 0; strNumb < N_SC_BOARD && !scoreBoardFile.eof(); ++strNumb)
	{
		scoreStr[strNumb] = u8"";
		getline(scoreBoardFile, scoreStr[strNumb]);
		getline(scoreBoardFile, tmps);
		scoresTable[strNumb] = std::stoi(tmps);
		//scoreBoardFile >> scoresTable[strNumb];
		std::cout << scoreStr[strNumb] << '\t' << scoresTable[strNumb] << std::endl;
	}

	--strNumb;

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
	barrierHit = Mix_LoadWAV("sounds/barrierHit.wav");
	if (barrierHit == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	barrierDestr = Mix_LoadWAV("sounds/barrierDestr.wav");
	if (barrierDestr == nullptr)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

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
