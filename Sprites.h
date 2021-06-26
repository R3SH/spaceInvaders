#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"

class Sprites
{
public:
	Sprites();
	~Sprites();

	void init();
	int getPlrNumbSprites() { return plrNumbSprites; }
	int getDroneNumbSprites() { return droneNumbSprites; }
	int getAlienNumbSprites() { return alienNumbSprites; }
	int getOverseerNumbSprites() { return overseerNumbSprites; }
	int getEnemyProjectileNumbSprites(char projType);
	SDL_Rect* getPlrSprite(int n) { return &plrSprites[n]; }
	SDL_Rect* getDroneSprite(int n) { return &droneSprites[n]; }
	SDL_Rect* getAlienSprite(int n) { return &alienSprites[n]; }
	SDL_Rect* getOverseerSprite(int n) { return &overseerSprites[n]; }
	SDL_Rect* getProjectileSprite(int n) { return &projectileSprites[n]; }
	SDL_Rect* getEnemyProjectileSprite(int n, char projSprite);

private:
	int plrNumbSprites;
	SDL_Rect* plrSprites = nullptr;
	int droneNumbSprites;
	SDL_Rect* droneSprites = nullptr;
	int alienNumbSprites;
	SDL_Rect* alienSprites = nullptr;
	int overseerNumbSprites;
	SDL_Rect* overseerSprites = nullptr;
	int projectileNumbSprites;
	SDL_Rect* projectileSprites = nullptr;
	int drLaserNumbSprites;
	SDL_Rect* drLaserSprites = nullptr;
	int alLaserNumbSprites;
	SDL_Rect* alLaserSprites = nullptr;
	int overLaserNumbSprites;
	SDL_Rect* overLaserSprites = nullptr;
};