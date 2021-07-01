#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Renderer.h"
#include "Resource.h"
#include "Sprites.h"
#include "Button.h"
#include "Entity.h"
#include "Player.h"
#include "Drone.h"
#include "Alien.h"
#include "Overseer.h"
#include "Laser.h"
#include "Barrier.h"

#define N_MENU 4
#define N_ABOUT 7
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
		SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_FULLSCREEN);
	/*wndw = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, 0);*/
	srfc = SDL_GetWindowSurface(wndw);
	rndr = SDL_CreateRenderer(wndw, -1, SDL_RENDERER_ACCELERATED);

	SDL_GetWindowSize(wndw, &SCREEN_W, &SCREEN_H);

	//Error catching
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
		return false;
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

	backRenderRect.x = SCREEN_W / 2 - 260;
	backRenderRect.h = SCREEN_H;

	return true;
}

void Rndr::renderMenu(Resource& src, int ch, std::string* buttons, Button* bArr, int numbOfButtons)	//Resources& media
{
	int winWidth, winHeight;
	std::string tmpstr;

	SDL_Texture* texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;
	SrcR.x = 0;
	SrcR.y = 0;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 0, 0, 0, 0);
	src.setCharSize(24);

	for (unsigned int i = 0; i < numbOfButtons; ++i)
	{
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

		SrcR.w = bArr[i].getButtonPos()->w;
		SrcR.h = bArr[i].getButtonPos()->h;
		texture = SDL_CreateTextureFromSurface(rndr, srfc);
		SDL_RenderCopy(rndr, texture, &SrcR, bArr[i].getButtonPos());
		SDL_FreeSurface(srfc);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(rndr);
}

void Rndr::renderScoreBoard(Resource& src, Button* button, std::string* str, int &ch)
{
	std::string tmpstr = u8"Лидеры";
	SDL_Rect SrcR;
	SDL_Rect DestR;
	SDL_Texture* texture;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 0, 0, 0, 0);
	src.setCharSize(24);
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * tmpstr.length();
	SrcR.h = 1.666 * src.getCharSize();

	DestR.x = SCREEN_W / 2 - SrcR.w / 2;
	DestR.y = 0;
	DestR.w = src.getCharSize() * tmpstr.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	src.setCharSize(18);

	for (int i = 0; i < src.getStrNumb(); ++i)
	{
		tmpstr = src.getStrings()[i];
		tmpstr += u8"  -  " + std::to_string(src.getNumbers()[i]);

		SrcR.x = 0;
		SrcR.y = 0;
		SrcR.w = src.getCharSize() * tmpstr.length();
		SrcR.h = 1.666 * src.getCharSize();

		DestR.x = SCREEN_W / 2 - 250;
		DestR.y += DestR.h + 20;
		DestR.w = src.getCharSize() * tmpstr.length();
		DestR.h = 1.666 * src.getCharSize();
		srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 255, 255, 255 });
		texture = SDL_CreateTextureFromSurface(rndr, srfc);
		SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
		SDL_FreeSurface(srfc);
		SDL_DestroyTexture(texture);
	}

	if (ch == 0)
	{
		tmpstr = '>' + (*str);
		srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 50, 169, 86 });
	}
	else
		srfc = TTF_RenderUTF8_Solid(src.getFont(), (*str).c_str(), { 255, 255, 255 });
	if (srfc == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}
	SrcR.w = (*button).getButtonPos()->w;
	SrcR.h = (*button).getButtonPos()->h;
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, (*button).getButtonPos());
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(rndr);
}

void Rndr::renderAbout(Resource& src, Sprites& sprites, Button* button, std::string* str, int& n, int& ch)
{
	std::string tmpstr;
	std::string buttons[N_ABOUT] = {
		u8"Таблица  набора  очков",
		u8"  очков.",
		u8"Управление",
		u8" движение  влево|вправо",
		u8" выстрел",
		u8" пауза|выход",
		u8"Автор:  Решетов А.Е.",
	};

	SDL_Texture* texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 0, 0, 0, 0);
	src.setCharSize(24);

	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * buttons[0].length();
	SrcR.h = 1.666 * src.getCharSize();

	DestR.x = SCREEN_W / 2 - SrcR.w / 2;
	DestR.y = SCREEN_H / 2 - 300;
	DestR.w = src.getCharSize() * buttons[0].length();
	DestR.h = 1.666 * src.getCharSize();

	srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[0].c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	src.setCharSize(18);

	DestR.x = SCREEN_W / 2 - 36 - 150;
	DestR.y = SCREEN_H / 2 - 300 + 1.666 * src.getCharSize() + 20;
	DestR.w = 36;
	DestR.h = 24;
	SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getDroneSprite(n / 32), &DestR);
	tmpstr = "- 10 " + buttons[1];
	DestR.x = SCREEN_W / 2 - 140;
	SrcR.w = src.getCharSize() * tmpstr.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.w = src.getCharSize() * tmpstr.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	DestR.x = SCREEN_W / 2 - 33 - 150;
	DestR.y = SCREEN_H / 2 - 300 + 1.666 * src.getCharSize() + 2 * 20 + 24;
	DestR.w = 33;
	DestR.h = 24;
	SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getAlienSprite(n / 32), &DestR);
	tmpstr = "- 20 " + buttons[1];
	DestR.x = SCREEN_W / 2 - 140;
	SrcR.w = src.getCharSize() * tmpstr.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.w = src.getCharSize() * tmpstr.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	DestR.x = SCREEN_W / 2 - 24 - 150;
	DestR.y = SCREEN_H / 2 - 300 + 1.666 * src.getCharSize() + 3 * 20 + (24 * 2);
	DestR.w = 24;
	DestR.h = 24;
	SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getOverseerSprite(n / 32), &DestR);
	tmpstr = "- 30 " + buttons[1];
	DestR.x = SCREEN_W / 2 - 140;
	SrcR.w = src.getCharSize() * tmpstr.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.w = src.getCharSize() * tmpstr.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	tmpstr = buttons[2];
	SrcR.w = src.getCharSize() * tmpstr.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.x = SCREEN_W / 2 - SrcR.w / 2;
	DestR.y = SCREEN_H / 2 - 1.666 * src.getCharSize() - 80;
	DestR.w = src.getCharSize() * tmpstr.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);
	
	//Arrows
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = 120;
	SrcR.h = 53;
	DestR.x = SCREEN_W / 2 - SrcR.w / 2 - 150;
	DestR.y = SCREEN_H / 2 - 70;
	DestR.w = SrcR.w;
	DestR.h = SrcR.h;
	SDL_RenderCopy(rndr, src.getArrowKeys(), &SrcR, &DestR);
	DestR.x += 10 + SrcR.w;
	SrcR.w = src.getCharSize() * buttons[3].length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.y = SCREEN_H / 2 - 70 + SrcR.h / 2;
	DestR.w = src.getCharSize() * buttons[3].length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[3].c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);
	//SpaceBar
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = 400;
	SrcR.h = 100;
	DestR.x = SCREEN_W / 2 - SrcR.w / 2 - 150;
	DestR.y = SCREEN_H / 2;
	DestR.w = SrcR.w;
	DestR.h = SrcR.h;
	SDL_RenderCopy(rndr, src.getSpaceBar(), &SrcR, &DestR);
	DestR.x += 10 + SrcR.w;
	SrcR.w = src.getCharSize() * buttons[4].length();
	DestR.y = DestR.y - 1.666 * src.getCharSize() / 2 + SrcR.h / 2;
	SrcR.h = 1.666 * src.getCharSize();
	DestR.w = src.getCharSize() * buttons[4].length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[4].c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);
	//Esc key
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = 120;
	SrcR.h = 120;
	DestR.x = SCREEN_W / 2 - SrcR.w / 2 - 150;
	DestR.y = SCREEN_H / 2 + 20 + 100;
	DestR.w = SrcR.w;
	DestR.h = SrcR.h;
	SDL_RenderCopy(rndr, src.getEscKey(), &SrcR, &DestR);
	DestR.x += 10 + SrcR.w;
	SrcR.w = src.getCharSize() * buttons[5].length();
	DestR.y = DestR.y - 1.666 * src.getCharSize() / 2 + SrcR.h / 2;
	SrcR.h = 1.666 * src.getCharSize();
	DestR.w = src.getCharSize() * buttons[5].length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[5].c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * buttons[6].length();
	SrcR.h = 1.666 * src.getCharSize();

	DestR.x = SCREEN_W / 2;
	DestR.y = SCREEN_H - 1.666 * src.getCharSize() - 10;
	DestR.w = src.getCharSize() * buttons[6].length();
	DestR.h = 1.666 * src.getCharSize();

	srfc = TTF_RenderUTF8_Solid(src.getFont(), buttons[6].c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	if (ch == 0)
	{
		tmpstr = '>' + (*str);
		srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 50, 169, 86 });
	}
	else
		srfc = TTF_RenderUTF8_Solid(src.getFont(), (*str).c_str(), { 255, 255, 255 });
	if (srfc == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}
	SrcR.w = (*button).getButtonPos()->w;
	SrcR.h = (*button).getButtonPos()->h;
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, (*button).getButtonPos());
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(rndr);
	
	++n;
	if (n >= 64)
		n = 0;
}

void Rndr::renderGame(Resource& src, Sprites& sprites, Player& plr, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, 
	std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles, std::vector<Entity>& explosions, std::vector<Barrier>& barriers)
{
	std::string scoreString = (std::to_string(plr.getScore())) + u8"  очков.";
	std::string livesString = (std::to_string(plr.getLives())) + u8"  X  ";
	SDL_Texture* texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 255, 255, 255, 255);
	SDL_RenderCopy(rndr, src.getBackgroundTexture(), &backRect, &backRenderRect);
	
	src.setCharSize(16);
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * scoreString.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.x = SCREEN_W / 2 - 260;
	DestR.y = 0;
	DestR.w = src.getCharSize() * scoreString.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), scoreString.c_str(), { 50, 169, 86 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

	src.setCharSize(16);
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * scoreString.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.x = SCREEN_W / 2 + 260 - src.getCharSize() * livesString.length() - plr.getWidth();
	DestR.y = 0;
	DestR.w = src.getCharSize() * livesString.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), livesString.c_str(), { 50, 169, 86 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	DestR.x += src.getCharSize() * livesString.length();
	DestR.w = plr.getWidth();
	DestR.h = plr.getHeight();
	SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getPlrSprite(plr.getSpritesN()) , &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);

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
	for (auto& i : plrProjectiles)
	{
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getProjectileSprite(0), &i.getPosition());
	}
	for (auto& i : enemyProjectiles)
	{
		//std::cout << i.getPosition().x << '\t' << i.getPosition().y << '\t' << i.getPosition().w << '\t' << i.getPosition().h << std::endl;
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getEnemyProjectileSprite(i.getSpritesN(), i.getType()), &i.getPosition());
	}
	for (auto& i : explosions)
	{
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getExplosionSprites(i.getSpritesN()), &i.getPosition());
	}
	for (auto& i : barriers)
	{
		SDL_RenderCopy(rndr, src.getSpriteSheet(), sprites.getBarrierSprites(i.getSpritesN()), &i.getPosition());
	}

	SDL_RenderPresent(rndr);
}

void Rndr::renderPause(Resource& src)
{
	std::string info = u8"Нажмите  [Esc]  чтобы выйти, [Пробел]  чтобы  продолжить";
	SDL_Texture* texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;

	src.setCharSize(16);

	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * info.length();
	SrcR.h = 2 * src.getCharSize();

	DestR.x = SCREEN_W / 2 - SrcR.w / 2;
	DestR.y = SCREEN_H / 2 - 3 * SrcR.h / 2;
	DestR.w = src.getCharSize() * info.length();
	DestR.h = 1.666 * src.getCharSize();

	srfc = TTF_RenderUTF8_Solid(src.getFont(), info.c_str(), { 50, 169, 86 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(rndr);
}

void Rndr::renderSaveScoreBoard(Resource& src)
{
	SDL_Texture* texture;
	std::string tmpstr = u8"Введите имя в консоль: ";
	SDL_Rect SrcR;
	SDL_Rect DestR;

	SDL_RenderClear(rndr);
	SDL_SetRenderDrawColor(rndr, 255, 255, 255, 0);

	src.setCharSize(16);
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = src.getCharSize() * tmpstr.length();
	SrcR.h = 1.666 * src.getCharSize();
	DestR.x = SCREEN_W / 2 - 260;
	DestR.y = SCREEN_H / 2;
	DestR.w = src.getCharSize() * tmpstr.length();
	DestR.h = 1.666 * src.getCharSize();
	srfc = TTF_RenderUTF8_Solid(src.getFont(), tmpstr.c_str(), { 50, 169, 86 });
	texture = SDL_CreateTextureFromSurface(rndr, srfc);
	SDL_RenderCopy(rndr, texture, &SrcR, &DestR);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(rndr);
}