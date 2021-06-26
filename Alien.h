#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"
#include "Entity.h"
#include "MovDir.h"

class Rndr;

class Alien : public Entity
{
public:
	Alien();
	Alien(Rndr& rndr, int x, int y, int speed, int projSpeed);
	~Alien();

	void init(Rndr& rndr);
	void setMovDir(MovDir dir) { alDir = dir; }
	MovDir getMovDir() { return alDir; }

private:
	MovDir alDir = MovDir::RIGHT;
};