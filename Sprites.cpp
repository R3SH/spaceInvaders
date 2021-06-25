#include "Sprites.h"

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
}

void Sprites::init()
{
	plrNumbSprites = 1;
	droneNumbSprites = 2;
	alienNumbSprites = 2;
	overseerNumbSprites = 2;
	laserNumbSprites = 1;

	plrSprites = new SDL_Rect[plrNumbSprites];
	droneSprites = new SDL_Rect[droneNumbSprites];
	alienSprites = new SDL_Rect[alienNumbSprites];
	overseerSprites = new SDL_Rect[overseerNumbSprites];
	laserSprites = new SDL_Rect[laserNumbSprites];
	
	for (int i = 0; i < plrNumbSprites; ++i)
	{
		plrSprites[i].x = 87;
		plrSprites[i].y = 5;
		plrSprites[i].w = 38;
		plrSprites[i].h = 24;
	}
	for (int i = 0; i < droneNumbSprites; ++i)
	{
		droneSprites[i].x = 5 * (i + 1) + 36 * i;
		droneSprites[i].y = 5;
		droneSprites[i].w = 36;
		droneSprites[i].h = 24;
	}
	for (int i = 0; i < alienNumbSprites; ++i)
	{
		alienSprites[i].x = 5 * (i + 1) + 33 * i;
		alienSprites[i].y = 34;
		alienSprites[i].w = 33;
		alienSprites[i].h = 24;
	}
	for (int i = 0; i < overseerNumbSprites; ++i)
	{
		overseerSprites[i].x = 5 * (i + 1) + 24 * i;
		overseerSprites[i].y = 63;
		overseerSprites[i].w = 24;
		overseerSprites[i].h = 24;
	}
	for (int i = 0; i < laserNumbSprites; ++i)
	{
		laserSprites[i].x = 81 + 6 * i;
		laserSprites[i].y = 34;
		laserSprites[i].w = 6;
		laserSprites[i].h = 9;
	}
}
