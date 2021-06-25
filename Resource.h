#pragma once
#include <SDL.h>
#include <string>

class Rndr;

class Resource
{
public:
	const int charSize = 24;

	Resource();
	~Resource();

	bool load(Rndr& rndr);
	TTF_Font* getFont() { return gFont; };
	SDL_Texture* getSpriteSheet() { return spriteSheet; }
	SDL_Texture* getPlayerTexture() { return m_player; }
	SDL_Texture* getEnemyTexture() { return m_enemy; }
	SDL_Texture* getLaserTexture() { return m_laser; }

private:
	SDL_Surface* loadSurface(Rndr& rndr, std::string path);
	SDL_Texture* loadTexture(Rndr& rndr, std::string path);

	TTF_Font* gFont = nullptr;
	SDL_Texture* spriteSheet = nullptr;
	SDL_Texture* m_laser = nullptr;
	SDL_Texture* m_player = nullptr;
	SDL_Texture* m_enemy = nullptr;
};