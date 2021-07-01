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
	int getPlrNumbSprites() { return plrNumbSprites; }			//Возвращает кол-во спрайтов игрока
	int getDroneNumbSprites() { return droneNumbSprites; }			//Возвращает кол-во спрайтов противника 1-го типа
	int getAlienNumbSprites() { return alienNumbSprites; }			//Возвращает кол-во спрайтов противника 2-го типа
	int getOverseerNumbSprites() { return overseerNumbSprites; }			//Возвращает кол-во спрайтов противника 3-го типа
	int getEnemyProjectileNumbSprites(char projType);			//Возвращает кол-во спрайтов снарядов противника, на вход принимает тип противника
	int getexplosionNumbSprites() { return explosionNumbSprites; }			//Возвращает кол-во спрайтов взрыва
	int getBarrierNumbSprites() { return barrierNumbSprites; }
	SDL_Rect* getPlrSprite(int n) { return &plrSprites[n]; }			//Возвращает координаты спрайта игрока
	SDL_Rect* getDroneSprite(int n) { return &droneSprites[n]; }			//Возвращает координаты спрайта противника 1-го типа
	SDL_Rect* getAlienSprite(int n) { return &alienSprites[n]; }			//Возвращает координаты спрайта противника 2-го типа
	SDL_Rect* getOverseerSprite(int n) { return &overseerSprites[n]; }			//Возвращает координаты спрайта противника 3-го типа
	SDL_Rect* getProjectileSprite(int n) { return &projectileSprites[n]; }			//Возвращает координаты спрайта снарядов игрока
	SDL_Rect* getEnemyProjectileSprite(int n, char projSprite);			//Возвращает координаты спрайта снарядов противника
	SDL_Rect* getExplosionSprites(int n) { return &explosionSprites[n]; }			//Возвращает координаты спрайта взрыва
	SDL_Rect* getBarrierSprites(int n) { return &barrierSprites[n]; }

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
	int explosionNumbSprites;
	SDL_Rect* explosionSprites = nullptr;
	int barrierNumbSprites;
	SDL_Rect* barrierSprites = nullptr;
};