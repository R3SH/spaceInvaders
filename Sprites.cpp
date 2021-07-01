#include "Sprites.h"

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
}

void Sprites::init()			//Инициализация спрайтов
{
	//Ввод кол-ва спрайтов объетов
	plrNumbSprites = 1;
	droneNumbSprites = 2;
	alienNumbSprites = 2;
	overseerNumbSprites = 2;
	projectileNumbSprites = 1;
	drLaserNumbSprites = 4;
	alLaserNumbSprites = 3;
	overLaserNumbSprites = 4;
	explosionNumbSprites = 2;
	barrierNumbSprites = 3;

	//Динам. выделение памяти для хранения спрайтов
	plrSprites = new SDL_Rect[plrNumbSprites];
	droneSprites = new SDL_Rect[droneNumbSprites];
	alienSprites = new SDL_Rect[alienNumbSprites];
	overseerSprites = new SDL_Rect[overseerNumbSprites];
	projectileSprites = new SDL_Rect[projectileNumbSprites];
	drLaserSprites = new SDL_Rect[drLaserNumbSprites];
	alLaserSprites = new SDL_Rect[alLaserNumbSprites];
	overLaserSprites = new SDL_Rect[overLaserNumbSprites];
	explosionSprites = new SDL_Rect[explosionNumbSprites];
	barrierSprites = new SDL_Rect[barrierNumbSprites];
	
	for (int i = 0; i < plrNumbSprites; ++i)			//Координаты спрайта игрока
	{
		plrSprites[i].x = 87;
		plrSprites[i].y = 5;
		plrSprites[i].w = 38;
		plrSprites[i].h = 24;
	}
	for (int i = 0; i < droneNumbSprites; ++i)			//Координаты спрайта противника 1-го типа
	{
		droneSprites[i].x = 5 * (i + 1) + 36 * i;
		droneSprites[i].y = 5;
		droneSprites[i].w = 36;
		droneSprites[i].h = 24;
	}
	for (int i = 0; i < alienNumbSprites; ++i)			//Координаты спрайта противника 2-го типа
	{
		alienSprites[i].x = 5 * (i + 1) + 33 * i;
		alienSprites[i].y = 34;
		alienSprites[i].w = 33;
		alienSprites[i].h = 24;
	}
	for (int i = 0; i < overseerNumbSprites; ++i)			//Координаты спрайта противника 3-го типа
	{
		overseerSprites[i].x = 5 * (i + 1) + 24 * i;
		overseerSprites[i].y = 63;
		overseerSprites[i].w = 24;
		overseerSprites[i].h = 24;
	}
	for (int i = 0; i < projectileNumbSprites; ++i)			//Координаты спрайта снаряда игрока
	{
		projectileSprites[i].x = 80;
		projectileSprites[i].y = 36;
		projectileSprites[i].w = 6;
		projectileSprites[i].h = 9;
	}
	for (int i = 0; i < drLaserNumbSprites; ++i)			//Координаты спрайта снаряда противника 1-го типа
	{
		drLaserSprites[i].x = 93 + 5 * i + 9 * i;
		drLaserSprites[i].y = 37;
		drLaserSprites[i].w = 9;
		drLaserSprites[i].h = 18;
	}
	for (int i = 0; i < alLaserNumbSprites; ++i)			//Координаты спрайта снаряда противника 2-го типа
	{
		alLaserSprites[i].x = 149 + 5 * i + 9 * i;
		alLaserSprites[i].y = 37;
		alLaserSprites[i].w = 9;
		alLaserSprites[i].h = 21;
	}
	for (int i = 0; i < overLaserNumbSprites; ++i)			//Координаты спрайта снаряда противника 3-го типа
	{
		overLaserSprites[i].x = 190 + 5 * i + 9 * i;
		overLaserSprites[i].y = 37;
		overLaserSprites[i].w = 9;
		overLaserSprites[i].h = 21;
	}
	for (int i = 0; i < explosionNumbSprites; ++i)
	{
		explosionSprites[i].x = 131 + (5 + 39) * i;
		explosionSprites[i].y = 5;
		explosionSprites[i].w = 39;
		explosionSprites[i].h = 24;
	}
	//293
	for (int i = 0; i < barrierNumbSprites; ++i)
	{
		barrierSprites[i].x = 293 + (7 + 66) * i;
		barrierSprites[i].y = 5;
		barrierSprites[i].w = 66;
		barrierSprites[i].h = 48;
	}
}

int Sprites::getEnemyProjectileNumbSprites(char projType)			//Возвращает количество спрайтов у разных типов снарядов противника
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

SDL_Rect* Sprites::getEnemyProjectileSprite(int n, char projType)				//Возвращает координаты спрайта для разных типов снарядов противника
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
