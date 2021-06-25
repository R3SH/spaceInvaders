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

//#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
//
//int main(int argc, char** argv)
//{
//	bool game = true;
//	SDL_Event event;
//	SDL_RWops* rwop = SDL_RWFromFile("revAAA.jpg", "rb");
//
//	
//	SDL_Init(SDL_INIT_VIDEO);
//	SDL_Window* wndw = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
//				SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP);
//	SDL_Renderer* rndr = SDL_CreateRenderer(wndw, -1, 0);
//	SDL_Surface* img = IMG_LoadJPG_RW(rwop);
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(rndr, img);
//
//
//	while (game)
//	{
//		SDL_WaitEvent(&event);
//		switch (event.type)
//		{
//		case SDL_QUIT:
//			game = false;
//			break;
//		}
//
//		SDL_RenderCopy(rndr, texture, NULL, NULL);
//		SDL_RenderPresent(rndr);
//	}
//
//	SDL_DestroyTexture(texture);
//	SDL_FreeSurface(img);
//	SDL_DestroyRenderer(rndr);
//	SDL_DestroyWindow(wndw);
//	SDL_Quit();
//	return 0;
//}