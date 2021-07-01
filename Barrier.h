#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"

class Rndr;

class Barrier : public Entity
{
public:
	Barrier();
	Barrier(int x, int y, int hlth);
	~Barrier();

	void setHealth(int hlth);
	void hit(int damage);
	bool isDestroyed();
	int getHealth() { return health; }

private:
	int health, initialHealth;

};