#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"
#include "Laser.h"

class Resource;
class Rndr;
class Laser;

class Player: public Entity
{
public:
	Player();
	~Player();

	void init(Rndr& rndr, Resource& src);
	void plrMov(SDL_Event& e);
	void shoot(Rndr& rndr, std::vector<Laser>& projectiles);
	void hit(Rndr& rndr);
	void reset(Rndr& rndr);
	void boundsCheck();
	void incrScore(int n);
	void addLife() { ++lives; };
	int getLives() { return lives; }
	int getScore() { return score; }
	bool dead();

private:
	int lives;
	int score;
};