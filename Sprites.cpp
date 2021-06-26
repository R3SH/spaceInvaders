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
	projectileNumbSprites = 1;
	drLaserNumbSprites = 4;
	alLaserNumbSprites = 3;
	overLaserNumbSprites = 4;

	plrSprites = new SDL_Rect[plrNumbSprites];
	droneSprites = new SDL_Rect[droneNumbSprites];
	alienSprites = new SDL_Rect[alienNumbSprites];
	overseerSprites = new SDL_Rect[overseerNumbSprites];
	projectileSprites = new SDL_Rect[projectileNumbSprites];
	drLaserSprites = new SDL_Rect[drLaserNumbSprites];
	alLaserSprites = new SDL_Rect[alLaserNumbSprites];
	overLaserSprites = new SDL_Rect[overLaserNumbSprites];
	
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
	for (int i = 0; i < projectileNumbSprites; ++i)
	{
		projectileSprites[i].x = 80;
		projectileSprites[i].y = 36;
		projectileSprites[i].w = 6;
		projectileSprites[i].h = 9;
	}
	for (int i = 0; i < drLaserNumbSprites; ++i)
	{
		drLaserSprites[i].x = 93 + 5 * i + 9 * i;
		drLaserSprites[i].y = 37;
		drLaserSprites[i].w = 9;
		drLaserSprites[i].h = 18;
	}
	for (int i = 0; i < alLaserNumbSprites; ++i)
	{
		alLaserSprites[i].x = 152 + 5 * i + 9 * i;
		alLaserSprites[i].y = 37;
		alLaserSprites[i].w = 9;
		alLaserSprites[i].h = 21;
	}
	for (int i = 0; i < overLaserNumbSprites; ++i)
	{
		overLaserSprites[i].x = 190 + 5 * i + 9 * i;
		overLaserSprites[i].y = 37;
		overLaserSprites[i].w = 9;
		overLaserSprites[i].h = 21;
	}
}

int Sprites::getEnemyProjectileNumbSprites(char projType)
{
	if (projType == 'D')
	{
		return drLaserNumbSprites;
	}
	else if (projType == 'A')
	{
		return alLaserNumbSprites;
	}
	else if (projType == 'O')
	{
		return overLaserNumbSprites;
	}
	return 0;
}

SDL_Rect* Sprites::getEnemyProjectileSprite(int n, char projType)
{
	if (projType == 'D')
	{
		return &drLaserSprites[n];
	}
	else if (projType == 'A')
	{
		return &alLaserSprites[n];
	}
	else if (projType == 'O')
	{
		return &overLaserSprites[n];
	}
	return nullptr;
}
