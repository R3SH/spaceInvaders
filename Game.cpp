#include <iostream>
#include <vector>
#include "Game.h"
#include "Renderer.h"
#include "Resource.h"
#include "Sprites.h"
#include "Entity.h"
#include "Player.h"
#include "Drone.h"
#include "Alien.h"
#include "Overseer.h"

#define N 4

Game::Game()
{
}

Game::~Game()
{
}

void Game::menu(Rndr& rndr, Resource& src, Sprites& sprites)
{
	int ch = 0;
	SDL_Event e;

	if (!rndr.init())
	{
		std::cout << "Renderer failed to initialize." << SDL_GetError() << std::endl;
		return;
	}
	if (!src.load(rndr))
	{
		std::cout << "Loader failed to load." << SDL_GetError() << std::endl;
		return;
	}
	sprites.init();
	

	while (!k_exit)
	{
		//Keyboard input
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE: 
					k_exit = true;
					break;
				/*case SDLK_LEFT:
					std::cout << "Left\n";
					break;
				case SDLK_RIGHT:
					std::cout << "Right\n";
					break;*/
				case SDLK_RETURN:
					switch (ch)
					{
					case 0:		//Start game
						start(rndr, src, sprites);
						break;
					case 1:		//Leaderboard
						scoreBoard(rndr, src);
						break;
					case 2:		//About
						about(rndr, src, sprites);
						break;
					case 3:		//Exit
						k_exit = true;
						break;
					}
					break;
				case SDLK_DOWN:
					if (ch < N - 1)
						++ch;
					else
						ch = 0;
					break;
				case SDLK_UP:
					if (ch > 0)
						--ch;
					else
						ch = N - 1;
					break;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				std::cout << "+\n";
			}
		}

		rndr.renderMenu(src, ch);
		SDL_Delay(16);
	}
}

void Game::scoreBoard(Rndr& rndr, Resource& src)
{
}

void Game::about(Rndr& rndr, Resource& src, Sprites& sprites)
{
	bool abExit = false;
	SDL_Event e;

	rndr.renderAbout(src);

	while (!abExit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					abExit = true;
			}

			SDL_Delay(16);
		}
	}
}

void Game::start(Rndr& rndr, Resource& src, Sprites& sprites)
{
	int animCntr = 0;
	bool endGame = false;
	SDL_Event e;
	Player plr;
	std::vector<Drone> drones;
	std::vector<Alien> aliens;
	std::vector<Overseer> overseers;

	//Initialization
	plr.init(rndr, src);
	plr.setXPos(rndr.getScreenW() / 2);
	plr.setYPos(rndr.getScreenH() - 23);
	addEnemies(rndr, drones, aliens, overseers, 1);

	while (!endGame)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					endGame = true;
				else
					plr.plrMov(e);
			}

		}

		plr.boundsCheck();
		movEnemies(drones, aliens, overseers);
		if (animCntr == 10)
		{
			animCntr = 0;
			animUpdate(sprites, drones, aliens, overseers);
		}
		else
			++animCntr;
		rndr.renderGame(src, sprites, plr, drones, aliens, overseers);
		SDL_Delay(16);			//32
	}

}

void Game::addEnemies(Rndr& rndr, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, int movSpeed)
{
	addDrones(rndr, drones, movSpeed);
	addAliens(rndr, aliens, movSpeed);
	addOverseers(rndr, overseers, movSpeed);
}

void Game::addDrones(Rndr& rndr, std::vector<Drone>& drones, int movSpeed)
{
	//2 rows 450px wide
	int spawnXPos;
	int offsetXPos = 36 + 10;			//offset = 10
	int spawnYPos = rndr.getScreenH() / 2 - 100;
	int offsetYPos = 24 + 10;
	int numbOfEnemies = 10;
	int numbOfRows = 2;

	for (int i = 0; i < numbOfRows; ++i)
	{
		spawnXPos = rndr.getScreenW() / 2 - 240;

		for (int j = 0; j < numbOfEnemies; ++j)
		{
			drones.push_back(Drone(rndr, spawnXPos, spawnYPos, movSpeed));
			spawnXPos += offsetXPos;
		}

		spawnYPos -= offsetYPos;
	}
}

void Game::addAliens(Rndr& rndr, std::vector<Alien>& aliens, int movSpeed)
{
	//2 rows 
	int spawnXPos;
	int offsetXPos = 33 + 3 + 10;			//offset = 13
	int spawnYPos = rndr.getScreenH() / 2 - 100 - 34 * 2;
	int offsetYPos = 24 + 10;
	int numbOfEnemies = 10;
	int numbOfRows = 2;

	for (int i = 0; i < numbOfRows; ++i)
	{
		spawnXPos = rndr.getScreenW() / 2 - 240;

		for (int j = 0; j < numbOfEnemies; ++j)
		{
			aliens.push_back(Alien(rndr, spawnXPos, spawnYPos, movSpeed));
			spawnXPos += offsetXPos;
		}

		spawnYPos -= offsetYPos;
	}
}

void Game::addOverseers(Rndr& rndr, std::vector<Overseer>& overseers, int movSpeed)
{
	int spawnXPos;
	int offsetXPos = 24 + 12 + 10;			//offset = 22
	int spawnYPos = rndr.getScreenH() / 2 - 100 - 34 * 4;
	int offsetYPos = 24 + 10;
	int numbOfEnemies = 10;
	int numbOfRows = 2;

	for (int i = 0; i < numbOfRows; ++i)
	{
		spawnXPos = rndr.getScreenW() / 2 - 239;			//240

		for (int j = 0; j < numbOfEnemies; ++j)
		{
			overseers.push_back(Overseer(rndr, spawnXPos, spawnYPos, movSpeed));
			spawnXPos += offsetXPos;
		}

		spawnYPos -= offsetYPos;
	}
}

void Game::movEnemies(std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers)
{
	movDrones(drones);
	movAliens(aliens);
	movOverseers(overseers);
}

void Game::movDrones(std::vector<Drone>& drones)
{
	int offsetFix = 1;
	int offsetYPos = 5; //Offset to move drones down everytime they hit a wall

	if ((*drones.begin()).getPositionY() > (*drones.begin()).getDownBound())
		offsetYPos = 0;

	for (std::vector<Drone>::iterator enemy = drones.begin(); enemy != drones.end(); ++enemy)
	{
		if ((*enemy).getMovDir() == MovDir::LEFT)			//Move Left
		{
			(*enemy).setXPos((*enemy).getPositionX() - (*enemy).getSpeed());
			//If an enemy has exceeded allowed bounds, change dir
			if ((*enemy).getPositionX() <= (*enemy).getLBound())
			{
				for(std::vector<Drone>::iterator it = drones.begin(); it != drones.end() && it <= enemy; ++it)
					(*it).setXPos((*it).getPositionX() + 2*(*it).getSpeed());

				for (auto& i : drones)
				{
					i.setMovDir(MovDir::RIGHT);
					i.setXPos(i.getPositionX() - 2*offsetFix);
					i.setYPos(i.getPositionY() + offsetYPos);
				}
			}
		}
		else if ((*enemy).getMovDir() == MovDir::RIGHT)			//Move Right
		{
			(*enemy).setXPos((*enemy).getPositionX() + (*enemy).getSpeed());
			//If enemy exceeds allowed bounds, change dir
			if ((*enemy).getPositionX() >= (*enemy).getRBound())
			{
				for (std::vector<Drone>::iterator it = drones.begin(); it != drones.end() && it <= enemy; ++it)
					(*it).setXPos((*it).getPositionX() - 2*(*it).getSpeed());

				for (auto& i : drones)
				{
					i.setMovDir(MovDir::LEFT);
					i.setXPos(i.getPositionX() + 2*offsetFix);
					i.setYPos(i.getPositionY() + offsetYPos);
				}
			}
		}
	}
}

void Game::movAliens(std::vector<Alien>& aliens)
{
	int offsetYPos = 5; //Offset to move drones down everytime they hit a wall

	if ((*aliens.begin()).getPositionY() > (*aliens.begin()).getDownBound())
		offsetYPos = 0;

	for (std::vector<Alien>::iterator enemy = aliens.begin(); enemy != aliens.end(); ++enemy)
	{
		if ((*enemy).getMovDir() == MovDir::LEFT)			//Move Left
		{
			(*enemy).setXPos((*enemy).getPositionX() - (*enemy).getSpeed());
			//If an (*enemy) has exceeded allowed bounds, change dir
			if ((*enemy).getPositionX() < (*enemy).getLBound())
			{
				for (std::vector<Alien>::iterator it = aliens.begin(); it != aliens.end() && it <= enemy; ++it)
					(*it).setXPos((*it).getPositionX() + 2*(*it).getSpeed());

				for (auto& i : aliens)
				{
					i.setMovDir(MovDir::RIGHT);
					i.setYPos(i.getPositionY() + offsetYPos);
				}
			}
		}
		else if ((*enemy).getMovDir() == MovDir::RIGHT)			//Move Right
		{
			(*enemy).setXPos((*enemy).getPositionX() + (*enemy).getSpeed());
			//If (*enemy) exceeds allowed bounds, change dir
			if ((*enemy).getPositionX() > (*enemy).getRBound())
			{
				for (std::vector<Alien>::iterator it = aliens.begin(); it != aliens.end() && it <= enemy; ++it)
					(*it).setXPos((*it).getPositionX() - 2*(*it).getSpeed());

				for (auto& i : aliens)
				{
					i.setMovDir(MovDir::LEFT);
					i.setYPos(i.getPositionY() + offsetYPos);
				}
			}
		}
	}
}

void Game::movOverseers(std::vector<Overseer>& overseers)
{
	int offsetYPos = 5; //Offset to move drones down everytime they hit a wall

	if ((*overseers.begin()).getPositionY() > (*overseers.begin()).getDownBound())
		offsetYPos = 0;

	for (std::vector<Overseer>::iterator enemy = overseers.begin(); enemy != overseers.end(); ++enemy)
	{
		if ((*enemy).getMovDir() == MovDir::LEFT)			//Move Left
		{
			(*enemy).setXPos((*enemy).getPositionX() - (*enemy).getSpeed());
			//If an enemy has exceeded allowed bounds, change dir
			if ((*enemy).getPositionX() < (*enemy).getLBound())
			{
				for (std::vector<Overseer>::iterator it = overseers.begin(); it != overseers.end() && it <= enemy; ++it)
					(*it).setXPos((*it).getPositionX() + 2*(*it).getSpeed());

				for (auto& i : overseers)
				{
					i.setMovDir(MovDir::RIGHT);
					i.setYPos(i.getPositionY() + offsetYPos);
				}
			}
		}
		else if ((*enemy).getMovDir() == MovDir::RIGHT)			//Move Right
		{
			(*enemy).setXPos((*enemy).getPositionX() + (*enemy).getSpeed());
			//If enemy exceeds allowed bounds, change dir
			if ((*enemy).getPositionX() > (*enemy).getRBound())
			{
				for (std::vector<Overseer>::iterator it = overseers.begin(); it != overseers.end() && it <= enemy; ++it)
					(*it).setXPos((*it).getPositionX() - 2*(*it).getSpeed());

				for (auto& i : overseers)
				{
					i.setMovDir(MovDir::LEFT);
					i.setYPos(i.getPositionY() + offsetYPos);
				}
			}
		}
	}
}

void Game::animUpdate(Sprites& sprites, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers)
{
	for (auto& i : drones)
	{
		i.frameUpdate(sprites.getDroneNumbSprites());
	}
	for (auto& i : aliens)
	{
		i.frameUpdate(sprites.getAlienNumbSprites());
	}
	for (auto& i : overseers)
	{
		i.frameUpdate(sprites.getOverseerNumbSprites());
	}
}
