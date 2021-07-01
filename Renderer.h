#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

class Resource;
class Sprites;
class Button;
class Player;
class Drone;
class Alien;
class Overseer;
class Laser;
class Entity;
class Barrier;

class Rndr
{
public:
	Rndr();
	~Rndr();

	bool init();
	void renderMenu(Resource& src, int ch, std::string* buttons, Button* bArr, int numbOfButtons);
	void renderScoreBoard(Resource& src, Button* button, std::string* str, int &ch);
	void renderAbout(Resource& src, Sprites& sprites, Button* button, std::string* str, int& n, int &ch);
	void renderGame(Resource& src, Sprites& sprites, Player& plr, std::vector<Drone>& drones,std::vector<Alien>& aliens, std::vector<Overseer>& overseers, 
		std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles, std::vector<Entity>& explosions, std::vector<Barrier>& barriers);
	void renderPause(Resource& src);
	void renderSaveScoreBoard(Resource& src);
	int getScreenW() { return SCREEN_W; }
	int getScreenH() { return SCREEN_H; }

	SDL_Surface* getWindowSurface() { return srfc; }
	SDL_Renderer* getRenderer() { return rndr; }

private:
	SDL_Window* wndw = nullptr;
	SDL_Surface* srfc = nullptr;
	SDL_Renderer* rndr = nullptr;
	SDL_Rect backRect {0, 0, 200, 200};
	SDL_Rect backRenderRect{ 0, 0, 520, 0 };

	int SCREEN_W = 0;
	int SCREEN_H = 0;
};
