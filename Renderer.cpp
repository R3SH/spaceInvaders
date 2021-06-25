#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Resource.h"
#include "Sprites.h"
#include "Entity.h"
#include "Player.h"
#include "Drone.h"
#include "Alien.h"
#include "Overseer.h"

#define N 4
#define BUTTON_SIZE 120
#define BUTTON_OFFSET 20

Rndr::Rndr()
{
}

Rndr::~Rndr()
{
}

bool Rndr::init()
{
	//Initializing
	wndw = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_FULLSCREEN_DESKTOP);
	/*wndw = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, 0);*/
	srfc = SDL_GetWindowSurface(wndw);
	rndr = SDL_CreateRenderer(wndw, -1, SDL_RENDERER_ACCELERATED);

	SDL_GetWindowSize(wndw, &SCREEN_W, &SCREEN_H);

	//Error catching
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Video failed to initialize." <<  SDL_GetError() << std::endl;
		return false;
	}

	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	int initiated_flags = IMG_Init(flags);
	if ((initiated_flags & flags) != flags)
	{
		std::cout << "Failed to initialize all image loaders\n";
		std::cout << "IMG Error: " << IMG_GetError() << "\n";
	}

	if (wndw == nullptr)
	{
		std::cout << "Failed to create window." << SDL_GetError() << std::endl;
		return false;
	}

	if (srfc == nullptr)
	{
		std::cout << "Failed to get window surface." << SDL_GetError() << std::endl;
		return false;
	}
	
	if (rndr == nullptr)
	{
		std::cout << "Failed to create the renderer." << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Rndr::renderMenu(Resource& src, int ch)	//Resources& media
{
	/*SDL_RWops* rwop = SDL_RWFromFile("revAAA.jpg", "rb");
	srfc = IMG_LoadJPG_RW(rwop);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rndr, srfc);

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 255, 255, 255, 0);

	SDL_RenderCopy(rndr, texture, nullptr, nullptr);

	SDL_RenderPresent(rndr);

	SDL_FreeSurface(srfc);*/

	int winWidth, winHeight;
	std::string tmpstr;
	std::string buttons[N] = {
		u8"Начать  игру",
		u8"Таблица  лидеров",
		u8"Справка",
		u8"Выход"
	};

	//SDL_GetWindowSize(wndw, &winWidth, &winHeight);

	SDL_Texture* texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 0, 0, 0, 0);
	
	for (unsigned int i = 0; i < N; ++i)
	{
		SrcR.x = 0;
		SrcR.y = 0;
		SrcR.w = src.charSize * buttons[i].length();		//strlen(buttons[i]);
		SrcR.h = 1.666 * src.charSize;

		DestR.x = SCREEN_W / 2 - SrcR.w / 2;
		DestR.y = SCREEN_H / 2 - 3 * SrcR.h / 2 - BUTTON_OFFSET + i * (SrcR.h + BUTTON_OFFSET);
		DestR.w = src.charSize * buttons[i].length();
		DestR.h = 1.666 * src.charSize;

		if (ch == i)
		{
			tmpstr = '>' + buttons[i];
			srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 50, 169, 86 });
		}
		else
			srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[i].c_str(), { 255, 255, 255 });
		if (srfc == nullptr)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			return;
		}

		texture = SDL_CreateTextureFromSurface(rndr, srfc);
		SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
		SDL_FreeSurface(srfc);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(rndr);
}

void Rndr::renderAbout(Resource& src)
{
	std::string tmpstr;
	std::string buttons[N] = {
		u8"Таблица  набора  очков",
		u8"  очков",
		u8"Автор:  Решетов А.Е.,  студент БГТУ  'Военмех'  группы И904Б",
		u8"[Esc] для выхода"
	};

	SDL_Texture* texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 0, 0, 0, 0);

	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.charSize * buttons[0].length();
	SrcR.h = 1.666 * src.charSize;

	DestR.x = SCREEN_W / 2 - SrcR.w / 2;
	DestR.y = 0;
	DestR.w = src.charSize * buttons[0].length();
	DestR.h = 1.666 * src.charSize;

	srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[0].c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);

	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(rndr);
}

void Rndr::renderGame(Resource& src, Sprites& sprites, Player& plr, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers)
{
	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 0, 0, 0, 0);

	SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getPlrSprite(plr.getSpritesN()) , &plr.getPosition());
	
	for (auto& i : drones)
	{
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getDroneSprite(i.getSpritesN()), &i.getPosition());
	}
	for (auto& i : aliens)
	{
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getAlienSprite(i.getSpritesN()), &i.getPosition());
	}
	for (auto& i : overseers)
	{
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getOverseerSprite(i.getSpritesN()), &i.getPosition());
	}

	SDL_RenderPresent(rndr);
}
