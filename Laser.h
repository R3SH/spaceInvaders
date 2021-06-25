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
	Laser(Rndr& rndr, int x, int y, int movSpeed);
	~Laser();

	void init(Rndr& rndr);

private:
	MovDir lasDir = MovDir::UP;
};