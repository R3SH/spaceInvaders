#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Renderer.h"
#include "Resource.h"
#include "Sprites.h"

int main(int argc, char** argv)
{
	Rndr renderer;
	Resource src;
	Game game;
	Sprites sprites;

	game.menu(renderer, src, sprites);

	return 0;
}