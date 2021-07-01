#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"
#include "MovDir.h"

class Laser	: public Entity
{
public:
	Laser();
	Laser(Rndr& rndr, int x, int y, int movSpeed, MovDir mdir, char type);
	~Laser();

	void init(Rndr& rndr);
	char getType() { return type; }
	int getSpeed() { return MOVEMENT_SPEED; }
	bool chekBounds(Rndr& rndr);
	MovDir getMovDir() { return lasDir; }

private:
	char type;
	MovDir lasDir = MovDir::UP;
};