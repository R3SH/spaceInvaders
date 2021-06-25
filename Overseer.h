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
	Overseer(Rndr& rndr, int x, int y, int speed);
	~Overseer();

	void init(Rndr& rndr);
	void setMovDir(MovDir dir) { drDir = dir; }
	MovDir getMovDir() { return drDir; }

private:
	MovDir drDir = MovDir::RIGHT;

};