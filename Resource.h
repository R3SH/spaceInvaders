#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <fstream>

class Rndr;

class Resource
{
public:

	Resource();
	~Resource();

	void setCharSize(int n) { charSize = n; }
	int getCharSize() { return charSize; }
	std::string* getStrings() { return scoreStr; }
	bool load(Rndr& rndr);
	TTF_Font* getFont() { return gFont; };
	SDL_Texture* getSpriteSheet() { return spriteSheet; }
	SDL_Texture* getPlayerTexture() { return m_player; }
	SDL_Texture* getBackgroundTexture() { return background; }
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

private:
	int charSize = 24;
	std::string scoreBoardName;
	std::string* scoreStr = new std::string [10];
	std::fstream scoreBoardFile;

	SDL_Surface* loadSurface(Rndr& rndr, std::string path);
	SDL_Texture* loadTexture(Rndr& rndr, std::string path);

	TTF_Font* gFont = nullptr;
	SDL_Texture* spriteSheet = nullptr;
	SDL_Texture* m_player = nullptr;
	SDL_Texture* background = nullptr;

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
	
};