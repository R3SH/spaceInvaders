#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"
#include "MovDir.h"

class Rndr;

class Overseer : public Entity
{
public:
	Overseer();
	Overseer(Rndr& rndr, int x, int y, int speed, int projSpeed);
	~Overseer();

	void init(Rndr& rndr);
	void setMovDir(MovDir dir) { overDir = dir; }
	MovDir getMovDir() { return overDir; }

private:
	MovDir overDir = MovDir::RIGHT;

};