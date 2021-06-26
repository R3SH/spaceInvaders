#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

class Resource;
class Sprites;
class Player;
class Drone;
class Alien;
class Overseer;
class Laser;

class Rndr
{
public:
	Rndr();
	~Rndr();

	bool init();
	void renderMenu(Resource& src, int ch);
	void renderScoreBoard(Resource& src);
	void renderAbout(Resource& src, Sprites& sprites, int& n);
	void renderGame(Resource& src, Sprites& sprites, Player& plr, std::vector<Drone>& drones,std::vector<Alien>& aliens,
		std::vector<Overseer>& overseers, std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles);
	void renderPause(Resource& src);
	int getScreenW() { return SCREEN_W; }
	int getScreenH() { return SCREEN_H; }

	SDL_Surface* getWindowSurface() { return srfc; }
	SDL_Renderer* getRenderer() { return rndr; }
private:
	SDL_Rect backRect {0, 0, 200, 200};
	SDL_Rect backRenderRect{ 0, 0, 520, 0 };
	SDL_Window* wndw = nullptr;
	SDL_Surface* srfc = nullptr;
	SDL_Renderer* rndr = nullptr;

	int SCREEN_W = 0;
	int SCREEN_H = 0;
};
