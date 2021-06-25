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
	SDL_Rect* getPlrSprite(int n) { return &plrSprites[n]; }
	SDL_Rect* getDroneSprite(int n) { return &droneSprites[n]; }
	SDL_Rect* getAlienSprite(int n) { return &alienSprites[n]; }
	SDL_Rect* getOverseerSprite(int n) { return &overseerSprites[n]; }

private:
	int plrNumbSprites;
	SDL_Rect* plrSprites = nullptr;
	int droneNumbSprites;
	SDL_Rect* droneSprites = nullptr;
	int alienNumbSprites;
	SDL_Rect* alienSprites = nullptr;
	int overseerNumbSprites;
	SDL_Rect* overseerSprites = nullptr;
	int laserNumbSprites;
	SDL_Rect* laserSprites = nullptr;
};