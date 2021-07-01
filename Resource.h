#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <fstream>

#define N_SC_BOARD 10

class Rndr;

class Resource
{
public:

	Resource();
	~Resource();

	void setName(std::string* name, int score);
	void setCharSize(int n) { charSize = n; }

	int getCharSize() { return charSize; }
	int getStrNumb() { return strNumb; }
	bool load(Rndr& rndr);
	
	int* getNumbers() { return scoresTable; }
	std::string* getStrings() { return scoreStr; }
	TTF_Font* getFont() { return gFont; };

	SDL_Texture* getSpriteSheet() { return spriteSheet; }
	SDL_Texture* getBackgroundTexture() { return background; }
	SDL_Texture* getArrowKeys() { return arrowKeys; }
	SDL_Texture* getSpaceBar() { return spaceBar; }
	SDL_Texture* getEscKey() { return escKey; }

	Mix_Chunk* getSndMenuPress() { return menuPress; }
	Mix_Chunk* getSndMenuSwitch() { return menuSwitch; }
	Mix_Chunk* getSndMenuBack() { return menuBack; }
	Mix_Chunk* getSndPlrHit() { return plrHit; }
	Mix_Chunk* getSndPlrDeath() { return plrDeath; }
	Mix_Chunk* getSndPlrShoot() { return plrShoot; }
	Mix_Chunk* getSndPlrLiveUp() { return plrLiveUp; }
	Mix_Chunk* getSndEnemySpawn() { return enemySpawn; }
	Mix_Chunk* getSndEnemyShoot() { return enemyShoot; }
	Mix_Chunk* getSndDroneDeath() { return droneDeath; }
	Mix_Chunk* getSndAlienDeath() { return alienDeath; }
	Mix_Chunk* getSndOverseerDeath() { return overseerDeath; }
	Mix_Chunk* getBarrierHit() { return barrierHit; }
	Mix_Chunk* getBarrierDestr() { return barrierDestr; }

private:
	int charSize = 24;
	std::string scoreBoardName;
	int strNumb;
	int scoresTable[N_SC_BOARD];
	std::string* scoreStr = new std::string [10];
	std::fstream scoreBoardFile;

	TTF_Font* gFont = nullptr;
	SDL_Texture* spriteSheet = nullptr;
	SDL_Texture* background = nullptr;
	SDL_Texture* arrowKeys = nullptr;
	SDL_Texture* spaceBar = nullptr;
	SDL_Texture* escKey = nullptr;

	Mix_Chunk* menuPress = nullptr;
	Mix_Chunk* menuSwitch = nullptr;
	Mix_Chunk* menuBack = nullptr;
	Mix_Chunk* plrHit = nullptr;
	Mix_Chunk* plrDeath = nullptr;
	Mix_Chunk* plrShoot = nullptr;
	Mix_Chunk* plrLiveUp = nullptr;
	Mix_Chunk* enemySpawn = nullptr;
	Mix_Chunk* enemyShoot = nullptr;
	Mix_Chunk* droneDeath = nullptr;
	Mix_Chunk* alienDeath = nullptr;
	Mix_Chunk* overseerDeath = nullptr;
	Mix_Chunk* barrierHit = nullptr;
	Mix_Chunk* barrierDestr = nullptr;
	
	SDL_Surface* loadSurface(Rndr& rndr, std::string path);
	SDL_Texture* loadTexture(Rndr& rndr, std::string path);

};