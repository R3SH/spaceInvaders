#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"
#include "MovDir.h"

class Rndr;

class Drone : public Entity
{
public:
	Drone();
	Drone(Rndr& rndr, int x, int y, int speed);
	~Drone();

	void init(Rndr& rndr);
	void setMovDir(MovDir dir) { drDir = dir; }
	MovDir getMovDir() { return drDir; }

private:
	MovDir drDir = MovDir::RIGHT;
	
};
