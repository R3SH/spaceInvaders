#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"

class Resource;
class Rndr;

class Player: public Entity
{
public:
	Player();
	~Player();

	void init(Rndr& rndr, Resource& src);
	void plrMov(SDL_Event& e);
	void boundsCheck();
	int getLives() { return lives; }

private:
	int lives;
	int score;
};