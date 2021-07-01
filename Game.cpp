#include <iostream>
#include <vector>
#include "Game.h"
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
#define N 4
#define BUTTON_OFFSET 20

Game::Game()
{
}

Game::~Game()
{
}

void Game::menu(Rndr& rndr, Resource& src, Sprites& sprites)
{
	int mouseX, mouseY;
	int ch = 0, prevCh = 0;
	std::string buttons[N_MENU] = {
		u8"Начать  игру",
		u8"Таблица  лидеров",
		u8"Справка",
		u8"Выход"
	};
	Button rButtons[N_MENU];
	SDL_Rect tmpRect;
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
	
	k_exit = false;
	src.setCharSize(24);

	for (unsigned int i = 0; i < N_MENU; ++i)
	{
		tmpRect.w = src.getCharSize()* buttons[i].length();
		tmpRect.h = 1.666 * src.getCharSize();
		tmpRect.x = (rndr.getScreenW() - src.getCharSize() * buttons[i].length()) / 2;
		tmpRect.y = rndr.getScreenH() / 2 - 3 * tmpRect.h / 2 + i * (tmpRect.h + BUTTON_OFFSET) - BUTTON_OFFSET;
		rButtons[i].setButtonPos(tmpRect);
	}

	while (!k_exit)
	{
		//Ввод
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE: 
					k_exit = true;
					Mix_PlayChannel(-1, src.getSndMenuBack(), 0);
					break;
				case SDLK_RETURN:
					Mix_PlayChannel(-1, src.getSndMenuPress(), 0);
					k_exit = switchMenu(rndr, src, sprites, ch);
					break;
				case SDLK_DOWN:
					Mix_PlayChannel(-1, src.getSndMenuSwitch(), 0);
					if (ch < N - 1)
						++ch;
					else
						ch = 0;
					break;
				case SDLK_UP:
					Mix_PlayChannel(-1, src.getSndMenuSwitch(), 0);
					if (ch > 0)
						--ch;
					else
						ch = N - 1;
					break;
				}
			}
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
				std::cout << "M:\t" << mouseX << '\t' << mouseY << "\tCH:\t" << ch << std::endl;
				if (handleMouse(&e, &ch, mouseX, mouseY, rButtons, N_MENU))
				{
					std::cout << "M:\t" << mouseX << '\t' << mouseY << "\tCH:\t" << ch << std::endl;
					k_exit = switchMenu(rndr, src, sprites, ch);
				}

				if(ch != prevCh)
					Mix_PlayChannel(-1, src.getSndMenuSwitch(), 0);
				prevCh = ch;
			}
		}

		rndr.renderMenu(src, ch, buttons, rButtons, N_MENU);
		SDL_Delay(16);
	}
}

void Game::scoreBoard(Rndr& rndr, Resource& src)			//Таблица лидеров
{
	int ch = -1, prevCh = -1;
	int mouseX, mouseY;
	std::string tmps = u8"Назад";
	Button rButton;
	SDL_Event e;

	k_exit = false;
	src.setCharSize(24);
	rButton.setButtonPos(50, rndr.getScreenH() - 50, tmps.length() * src.getCharSize(), 1.666 * src.getCharSize());

	while (!k_exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					Mix_PlayChannel(-1, src.getSndMenuBack(), 0);
					k_exit = true;
				}
			}

			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
				std::cout << "M:\t" << mouseX << '\t' << mouseY << "\tCH:\t" << ch << std::endl;
				if (handleMouse(&e, &ch, mouseX, mouseY, &rButton, 1))
				{
					std::cout << "M:\t" << mouseX << '\t' << mouseY << "\tCH:\t" << ch << std::endl;
					if (ch == 0)
					{
						Mix_PlayChannel(-1, src.getSndMenuBack(), 0);
						k_exit = true;
					}
				}

				if (ch != prevCh)
					Mix_PlayChannel(-1, src.getSndMenuSwitch(), 0);
				prevCh = ch;
			}
		}

		rndr.renderScoreBoard(src, &rButton, &tmps, ch);
		SDL_Delay(32);
	}
}

void Game::about(Rndr& rndr, Resource& src, Sprites& sprites)			//О игре
{
	int ch = -1, prevCh = -1;
	int animCntr = 0;
	int mouseX, mouseY;
	SDL_Event e;
	std::string tmps = u8"Назад";
	Button rButton;

	k_exit = false;
	src.setCharSize(24);
	rButton.setButtonPos(50, rndr.getScreenH() - 50, tmps.length() * src.getCharSize(), 1.666 * src.getCharSize());

	while (!k_exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					Mix_PlayChannel(-1, src.getSndMenuBack(), 0);
					k_exit = true;
				}
			}

			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
				std::cout << "M:\t" << mouseX << '\t' << mouseY << "\tCH:\t" << ch << std::endl;
				if (handleMouse(&e, &ch, mouseX, mouseY, &rButton, 1))
				{
					std::cout << "M:\t" << mouseX << '\t' << mouseY << "\tCH:\t" << ch << std::endl;
					if (ch == 0)
					{
						Mix_PlayChannel(-1, src.getSndMenuBack(), 0);
						k_exit = true;
					}
				}

				if (ch != prevCh)
					Mix_PlayChannel(-1, src.getSndMenuSwitch(), 0);
				prevCh = ch;
			}
		}

		rndr.renderAbout(src, sprites, &rButton, &tmps, animCntr, ch);
		SDL_Delay(32);
	}
}

void Game::start(Rndr& rndr, Resource& src, Sprites& sprites)
{
	int frameCntr = 1;
	int shootDelay = 0;
	int addedLifes = 0;
	int enemyMovementSpeed = 1, enemyProjectileSpeed = 2;
	SDL_Event e;
	Player plr;
	std::vector<Drone> drones;
	std::vector<Alien> aliens;
	std::vector<Overseer> overseers;
	std::vector<Entity> explosions;
	std::vector<Laser> plrProjectiles;
	std::vector<Laser> enemyProjectiles;
	std::vector<Barrier> barriers;

	//Инициализация
	k_exit = false;
	plr.init(rndr, src);
	addEnemies(rndr, drones, aliens, overseers, enemyMovementSpeed, enemyProjectileSpeed);
	Mix_PlayChannel(-1, src.getSndEnemySpawn(), 0);
	for (int i = 0; i < 4; ++i)
		barriers.push_back(Barrier(rndr.getScreenW() / 2 - 260 + 32 + i * (66 + 64), rndr.getScreenH() - 48 - 80, 60));

	while (!k_exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					Mix_PlayChannel(-1, src.getSndMenuPress(), 0);
					k_exit = pause(rndr, src);
					if (k_exit)
						return;
				}
				else
				{
					if (e.key.keysym.sym == SDLK_SPACE && shootDelay >= 50)
					{
						shootDelay = 0;
						plr.shoot(rndr, plrProjectiles);
						Mix_PlayChannel(-1, src.getSndPlrShoot(), 0);
					}
					plr.plrMov(e);
				}
			}
		}

		movEnemies(drones, aliens, overseers);
		movProjectiles(plrProjectiles, enemyProjectiles);
		checkProjectiles(rndr, plr, src, plrProjectiles, enemyProjectiles, drones, aliens, overseers, explosions, barriers);
		plr.boundsCheck();
		if (frameCntr % 10 == 0)
		{
			if (frameCntr == 100)
			{
				frameCntr = 0;
				enemyShoot(rndr, plr, src, enemyProjectiles, drones, aliens, overseers);
				std::cout << "\n" << enemyProjectiles.size()  << '\t' << plrProjectiles.size() << std::endl;
			}

			//Checking if there's no enemies left
			if (drones.empty() && aliens.empty() && overseers.empty())
			{
				++enemyMovementSpeed;
				++enemyProjectileSpeed;
				plr.incrScore(100);
				plr.addLife();
				Mix_PlayChannel(-1, src.getSndPlrLiveUp(), 0);
				addEnemies(rndr, drones, aliens, overseers, enemyMovementSpeed, enemyProjectileSpeed);
				Mix_PlayChannel(-1, src.getSndEnemySpawn(), 0);
			}
			if (plr.getScore() / 1000 > addedLifes)
			{
				addedLifes = plr.getScore() / 1000;
				Mix_PlayChannel(-1, src.getSndPlrLiveUp(), 0);
			}
			animUpdate(sprites, drones, aliens, overseers, enemyProjectiles, explosions);
			++frameCntr;
		}
		else
			++frameCntr;
		if (plr.dead())
		{
			k_exit = true;
			Mix_PlayChannel(-1, src.getSndPlrDeath(), 0);
		}
		rndr.renderGame(src, sprites, plr, drones, aliens, overseers, plrProjectiles, enemyProjectiles, explosions, barriers);
		++shootDelay;			//32
		SDL_Delay(16);
	}

	saveScore(rndr, src, plr.getScore());
}

void Game::saveScore(Rndr& rndr, Resource& src, int score)
{
	std::string name = u8"";

	while(name.empty())
	{
		rndr.renderSaveScoreBoard(src);
		std::cin >> name;
		src.setName(&name, score);
	}
}

bool Game::pause(Rndr& rndr, Resource& src)
{
	k_exit = false;
	SDL_Event e;

	rndr.renderPause(src);

	while (!k_exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					Mix_PlayChannel(-1, src.getSndMenuPress(), 0);
					return true;
				}
				else if (e.key.keysym.sym == SDLK_SPACE)
				{
					Mix_PlayChannel(-1, src.getSndMenuBack(), 0);
					return false;
				}
			}
		}

		SDL_Delay(32);
	}
}

bool Game::switchMenu(Rndr& rndr, Resource& src, Sprites& sprites, int ch)
{
	switch (ch)
	{
	case 0:		//Начало игры
		start(rndr, src, sprites);
		break;
	case 1:		//Таблица лидеров
		scoreBoard(rndr, src);
		break;
	case 2:		//О игре
		about(rndr, src, sprites);
		break;
	case 3:		//Выход
		return true;
		break;
	}
	
	return false;
}

bool Game::handleMouse(SDL_Event* e, int* prevCh, int mouseX, int mouseY, Button* buttonPos, int numbOfButtons)
{
	SDL_Rect tmpRect;

	for (int i = 0; i < numbOfButtons; ++i)
	{
		tmpRect = *buttonPos[i].getButtonPos();
		if (mouseX >= tmpRect.x && mouseX <= (tmpRect.x + tmpRect.w))
		{
			if (mouseY >= tmpRect.y && mouseY <= (tmpRect.y + tmpRect.h))
			{
				(*prevCh) = i;

				if ((*e).type == SDL_MOUSEBUTTONDOWN)
				{
					std::cout << "CHANGE";
					if ((*e).button.button == SDL_BUTTON_LEFT)
						return true;
				}
			}
		}
	}

	return false;
}

void Game::addEnemies(Rndr& rndr, std::vector<Drone>& drones, std::vector<Alien>& aliens,
	std::vector<Overseer>& overseers, int movSpeed, int projSpeed)
{
	addDrones(rndr, drones, movSpeed, projSpeed);
	addAliens(rndr, aliens, movSpeed, projSpeed + 1);
	addOverseers(rndr, overseers, movSpeed, projSpeed + 2);
}

void Game::addDrones(Rndr& rndr, std::vector<Drone>& drones, int movSpeed, int projSpeed)
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
			drones.push_back(Drone(rndr, spawnXPos, spawnYPos, movSpeed, projSpeed));
			spawnXPos += offsetXPos;
		}

		spawnYPos -= offsetYPos;
	}
}

void Game::addAliens(Rndr& rndr, std::vector<Alien>& aliens, int movSpeed, int projSpeed)
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
			aliens.push_back(Alien(rndr, spawnXPos, spawnYPos, movSpeed, projSpeed));
			spawnXPos += offsetXPos;
		}

		spawnYPos -= offsetYPos;
	}
}

void Game::addOverseers(Rndr& rndr, std::vector<Overseer>& overseers, int movSpeed, int projSpeed)
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
			overseers.push_back(Overseer(rndr, spawnXPos, spawnYPos, movSpeed, projSpeed));
			spawnXPos += offsetXPos;
		}

		spawnYPos -= offsetYPos;
	}
}

void Game::movEnemies(std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers)
{
	int maxDr, maxAl;
	maxDr = movDrones(drones);
	maxAl = movAliens(drones, aliens, maxDr);
	movOverseers(drones, aliens, overseers, maxDr, maxAl);
}

int Game::movDrones(std::vector<Drone>& drones)
{
	int offsetFix = 1;
	int offsetYPos = 5;			//Offset to move drones down everytime they hit a wall
	int maxH = INT_MAX;

	if (!drones.empty())
	{
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

			if ((*enemy).getPositionY() - 10 < maxH)
				maxH = (*enemy).getPositionY() - 10;
		}
	}
	return maxH;
}

int Game::movAliens(std::vector<Drone>& drones, std::vector<Alien>& aliens, int maxDr)
{
	int offsetYPos = 5; //Offset to move drones down everytime they hit a wall
	int maxH = INT_MAX, alMaxH = 0;

	if (!aliens.empty())
	{
		for (std::vector<Alien>::iterator enemy = aliens.begin(); enemy != aliens.end(); ++enemy)
		{
			if(((*enemy).getPositionY() + (*enemy).getHeight()) > alMaxH)
				alMaxH = (*enemy).getPositionY() + (*enemy).getHeight();
		}

		if (((*aliens.begin()).getPositionY() > (*aliens.begin()).getDownBound()) || alMaxH >= maxDr)
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

			if ((*enemy).getPositionY() - 10 < maxH)
				maxH = (*enemy).getPositionY() - 10;
		}
	}

	return maxH;
}

void Game::movOverseers(std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, int maxDr, int maxAl)
{
	int offsetYPos = 5; //Offset to move drones down everytime they hit a wall
	int overMaxH = 0;

	if (!overseers.empty())
	{
		for (std::vector<Overseer>::iterator enemy = overseers.begin(); enemy != overseers.end(); ++enemy)
			if (((*enemy).getPositionY() + (*enemy).getHeight()) > overMaxH)
				overMaxH = (*enemy).getPositionY() + (*enemy).getHeight();

		if (((*overseers.begin()).getPositionY() > (*overseers.begin()).getDownBound()) || overMaxH > maxDr|| overMaxH > maxAl)
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
}

void Game::movProjectiles(std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles)
{
	movPlrProjectiles(plrProjectiles);
	movEnemyProjectiles(enemyProjectiles);
}

void Game::movPlrProjectiles(std::vector<Laser>& projectiles)
{
	for (auto& plrProj : projectiles)
	{
		if (plrProj.getMovDir() == MovDir::UP)
		{
			plrProj.setYPos(plrProj.getPositionY() - plrProj.getSpeed());
		}
	}
}

void Game::movEnemyProjectiles(std::vector<Laser>& projectiles)
{
	for (auto& plrProj : projectiles)
	{
		if (plrProj.getMovDir() == MovDir::DOWN)
		{
			plrProj.setYPos(plrProj.getPositionY() + plrProj.getSpeed());
		}
	}
}

void Game::enemyShoot(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& enemyLasers, std::vector<Drone>& drones,
	std::vector<Alien>& aliens, std::vector<Overseer>& overseers)
{
	int closestDr = -1, closestAl = -1, closestOver = -1;
	int tmpDr = INT_MAX, tmpAl = INT_MAX, tmpOver = INT_MAX;
	int shootPos = 0;
	bool freeLine = true;

	if (!drones.empty())
	{
		for (int enemy = 0; enemy < drones.size() && abs(drones[enemy].getPositionX() - plr.getPositionX()) < tmpDr; ++enemy)
		{
			if (tmpDr > abs(drones[enemy].getPositionX() - plr.getPositionX()))
			{
				tmpDr = abs(drones[enemy].getPositionX() - plr.getPositionX());
				closestDr = enemy;
			}
		}
	}
	if (!aliens.empty())
	{
		for (int enemy = 0; enemy < aliens.size() && abs(aliens[enemy].getPositionX() - plr.getPositionX()) < tmpAl; ++enemy)
		{
			freeLine = true;
			if (!drones.empty())
			{
				shootPos = aliens[enemy].getPositionX() + (aliens[enemy].getWidth() / 2) - 3;
				//line of fire check
				for (int dr = 0; dr < drones.size(); ++dr)
				{
					if ((shootPos >= drones[dr].getPositionX()) && (shootPos <= drones[dr].getPositionX() + drones[dr].getWidth()) || 
						((shootPos + 3) >= drones[dr].getPositionX()) && ((shootPos + 3) <= drones[dr].getPositionX() + drones[dr].getWidth()))
						freeLine = false;
				}
				
			}
			
			if (tmpAl > abs(aliens[enemy].getPositionX() - plr.getPositionX()) && freeLine)
			{
				tmpAl = abs(aliens[enemy].getPositionX() - plr.getPositionX());
				closestAl = enemy;
			}
		}
	}
	if (!overseers.empty())
	{
		for (int enemy = 0; enemy < overseers.size() && abs(overseers[enemy].getPositionX() - plr.getPositionX()) < tmpOver; ++enemy)
		{
			freeLine = true;

			if (!drones.empty())
			{
				shootPos = overseers[enemy].getPositionX() + (overseers[enemy].getWidth() / 2) - 3;
				//line of fire check
				for (int dr = 0; dr < drones.size(); ++dr)
				{
					if ((shootPos >= drones[dr].getPositionX()) && (shootPos <= drones[dr].getPositionX() + drones[dr].getWidth()) ||
						((shootPos + 3) >= drones[dr].getPositionX()) && ((shootPos + 3) <= drones[dr].getPositionX() + drones[dr].getWidth()))
						freeLine = false;
				}
			}
			if (!aliens.empty())
			{
				//line of fire check
				for (int al = 0; al < aliens.size(); ++al)
				{
					shootPos = overseers[enemy].getPositionX() + (overseers[enemy].getWidth() / 2) - 3;
					if ((shootPos >= aliens[al].getPositionX()) && (shootPos <= aliens[al].getPositionX() + aliens[al].getWidth()) ||
						((shootPos + 3) >= aliens[al].getPositionX()) && ((shootPos + 3) <= aliens[al].getPositionX() + aliens[al].getWidth()))
						freeLine = false;
				}
			}

			if (tmpOver > abs(overseers[enemy].getPositionX() - plr.getPositionX()) && freeLine)
			{
				tmpOver = abs(overseers[enemy].getPositionX() - plr.getPositionX());
				closestOver = enemy;
			}
		}
	}

	if (tmpDr <= tmpAl && tmpDr <= tmpOver && (tmpDr != INT_MAX) && (!drones.empty()))
	{
		std::cout << drones[closestDr].getPositionX() << '\t';
		enemyLasers.push_back(Laser(rndr, (drones[closestDr].getPositionX() + (drones[closestDr].getWidth() / 2)), 
			(drones[closestDr].getPositionY() + drones[closestDr].getHeight()), drones[closestDr].getProjSpeed(), MovDir::DOWN, 'D'));
		Mix_PlayChannel(-1, src.getSndEnemyShoot(), 0);
	}
	else if (tmpAl <= tmpDr && tmpAl <= tmpOver && (tmpAl != INT_MAX) && (!aliens.empty()))
	{
		std::cout << "-\t" << enemyLasers.size() << std::endl;
		enemyLasers.push_back(Laser(rndr, (aliens[closestAl].getPositionX() + aliens[closestAl].getWidth() / 2),
			(aliens[closestAl].getPositionY() + aliens[closestAl].getHeight()), aliens[closestAl].getProjSpeed(), MovDir::DOWN, 'A'));
		Mix_PlayChannel(-1, src.getSndEnemyShoot(), 0);
	}
	else if(!overseers.empty())		//tmpOver is min
	{
		std::cout << "0";
		enemyLasers.push_back(Laser(rndr, (overseers[closestOver].getPositionX() + overseers[closestOver].getWidth() / 2),
			(overseers[closestOver].getPositionY() + overseers[closestOver].getHeight()), overseers[closestOver].getProjSpeed(), MovDir::DOWN, 'O'));
		Mix_PlayChannel(-1, src.getSndEnemyShoot(), 0);
	}
}

void Game::checkProjectiles(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles, 
	std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, std::vector<Entity>& explosions, std::vector<Barrier>& barriers)
{
	checkPlrProjectile(rndr, plr, src, plrProjectiles, drones, aliens, overseers, explosions, barriers);
	checkEnemyProjectile(rndr, plr, src, enemyProjectiles, explosions, barriers);
}

void Game::checkPlrProjectile(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& projectiles, std::vector<Drone>& drones, 
	std::vector<Alien>& aliens, std::vector<Overseer>& overseers, std::vector<Entity>& explosions, std::vector<Barrier>& barriers)
{
	bool hit = false;
	if (!projectiles.empty())
	{
		for (int plrProj = 0; plrProj < projectiles.size(); ++plrProj)
		{
			hit = false;
			if (!projectiles.empty())
			{
				if (projectiles[plrProj].chekBounds(rndr))
				{
					for (int enemy = 0; enemy < drones.size() && !hit; ++enemy)
					{
						if (!projectiles.empty())
						{
							if ((projectiles[plrProj].getPositionY() >= drones[enemy].getPositionY() &&
								projectiles[plrProj].getPositionY() <= (drones[enemy].getHeight() + drones[enemy].getPositionY())) ||
								((projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) >= drones[enemy].getPositionY() &&
									(projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) <= (drones[enemy].getPositionY() + drones[enemy].getHeight())))
							{
								if ((projectiles[plrProj].getPositionX() >= drones[enemy].getPositionX() && projectiles[plrProj].getPositionX() <= (drones[enemy].getWidth() + drones[enemy].getPositionX())
									|| (projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) >= drones[enemy].getPositionX() && (projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) <= (drones[enemy].getWidth() + drones[enemy].getPositionX())))
								{
									std::cout << "+";
									hit = true;
									projectiles.erase(projectiles.begin() + plrProj);
									if (!drones.empty())
									{
										explosions.push_back(Entity(drones[enemy].getPositionX(), drones[enemy].getPositionY()));
										drones.erase(drones.begin() + enemy);
									}
									plr.incrScore(10);
									Mix_PlayChannel(-1, src.getSndDroneDeath(), 0);
								}
							}
						}
					}
					if (!aliens.empty())
					{
						for (int enemy = 0; enemy < aliens.size() && !hit; ++enemy)
						{
							if ((projectiles[plrProj].getPositionY() >= aliens[enemy].getPositionY() &&
								projectiles[plrProj].getPositionY() <= (aliens[enemy].getHeight() + aliens[enemy].getPositionY())) ||
								((projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) >= aliens[enemy].getPositionY() &&
									(projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) <= (aliens[enemy].getPositionY() + aliens[enemy].getHeight())))
							{
								if ((projectiles[plrProj].getPositionX() >= aliens[enemy].getPositionX() && projectiles[plrProj].getPositionX() <= (aliens[enemy].getWidth() + aliens[enemy].getPositionX())
									|| (projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) >= aliens[enemy].getPositionX() && (projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) <= (aliens[enemy].getWidth() + aliens[enemy].getPositionX()))) 
								{
									hit = true;
									projectiles.erase(projectiles.begin() + plrProj);
									if (!aliens.empty())
									{
										explosions.push_back(Entity(aliens[enemy].getPositionX(), aliens[enemy].getPositionY()));
										aliens.erase(aliens.begin() + enemy);
									}
									plr.incrScore(20);
									Mix_PlayChannel(-1, src.getSndAlienDeath(), 0);
								}
							}
						}
					}
					if (!overseers.empty())
					{
						for (int enemy = 0; enemy < overseers.size() && !hit; ++enemy)
						{
							if ((projectiles[plrProj].getPositionY() >= overseers[enemy].getPositionY() &&
								projectiles[plrProj].getPositionY() <= (overseers[enemy].getHeight() + overseers[enemy].getPositionY())) ||
								((projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) >= overseers[enemy].getPositionY() &&
									(projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) <= (overseers[enemy].getPositionY() + overseers[enemy].getHeight())))
							{
								if ((projectiles[plrProj].getPositionX() >= overseers[enemy].getPositionX() && projectiles[plrProj].getPositionX() <= (overseers[enemy].getWidth() + overseers[enemy].getPositionX())
									|| (projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) >= overseers[enemy].getPositionX() && 
									(projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) <= (overseers[enemy].getWidth() + overseers[enemy].getPositionX()))) 
								{
									hit = true;
									projectiles.erase(projectiles.begin() + plrProj);
									if (!overseers.empty())
									{
										explosions.push_back(Entity(overseers[enemy].getPositionX(), overseers[enemy].getPositionY()));
										overseers.erase(overseers.begin() + enemy);
									}
									plr.incrScore(30);
									Mix_PlayChannel(-1, src.getSndOverseerDeath(), 0);
								}
							}
						}
					}
					if (!barriers.empty())
					{
						for (int tmpBarriers = 0; tmpBarriers < barriers.size() && !hit; ++tmpBarriers)
						{
							if ((projectiles[plrProj].getPositionY() >= barriers[tmpBarriers].getPositionY() &&
								projectiles[plrProj].getPositionY() <= (barriers[tmpBarriers].getHeight() + barriers[tmpBarriers].getPositionY())) ||
								((projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) >= barriers[tmpBarriers].getPositionY() &&
									(projectiles[plrProj].getPositionY() + projectiles[plrProj].getHeight()) <= (barriers[tmpBarriers].getPositionY() + barriers[tmpBarriers].getHeight())))
							{
								if ((projectiles[plrProj].getPositionX() >= barriers[tmpBarriers].getPositionX() && projectiles[plrProj].getPositionX() <= (barriers[tmpBarriers].getWidth() + barriers[tmpBarriers].getPositionX())
									|| (projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) >= barriers[tmpBarriers].getPositionX() &&
									(projectiles[plrProj].getPositionX() + projectiles[plrProj].getWidth()) <= (barriers[tmpBarriers].getWidth() + barriers[tmpBarriers].getPositionX())))
								{
									hit = true;
									if (!barriers.empty())
									{
										explosions.push_back(Entity(projectiles[plrProj].getPositionX() - 19, projectiles[plrProj].getPositionY()));
										barriers[tmpBarriers].hit(projectiles[plrProj].getSpeed());
										if (barriers[tmpBarriers].isDestroyed())
										{
											Mix_PlayChannel(-1, src.getBarrierDestr(), 0);
											barriers.erase(barriers.begin() + tmpBarriers);
										}
										else
											Mix_PlayChannel(-1, src.getBarrierHit(), 0);
									}
									projectiles.erase(projectiles.begin() + plrProj);
								}
							}
						}
					}
				}
				else
					projectiles.erase(projectiles.begin() + plrProj);
			}

			if (hit)
				std::cout << "ENEMY IS HIT\n";
		}
	}
}

void Game::checkEnemyProjectile(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& projectiles, std::vector<Entity>& explosions, std::vector<Barrier>& barriers)
{
	bool hit = false;

	for (int projectile = 0; projectile < projectiles.size(); ++projectile)
	{
		if (projectiles[projectile].chekBounds(rndr))
		{
			if ((projectiles[projectile].getPositionY() >= plr.getPositionY() &&
				projectiles[projectile].getPositionY() <= (plr.getHeight() + plr.getPositionY())) ||
				((projectiles[projectile].getPositionY() + projectiles[projectile].getHeight()) >= plr.getPositionY() &&
					(projectiles[projectile].getPositionY() + projectiles[projectile].getHeight()) <= (plr.getPositionY() + plr.getHeight())))
			{
				if ((projectiles[projectile].getPositionX() >= plr.getPositionX() && projectiles[projectile].getPositionX() <= (plr.getWidth() + plr.getPositionX())||
					(projectiles[projectile].getPositionX() + projectiles[projectile].getWidth()) >= plr.getPositionX() &&
					(projectiles[projectile].getPositionX() + projectiles[projectile].getWidth()) <= (plr.getWidth() + plr.getPositionX())))
				{
					hit = true;
					projectiles.erase(projectiles.begin() + projectile);
					explosions.push_back(Entity(plr.getPositionX(), plr.getPositionY()));
					plr.hit(rndr);
					Mix_PlayChannel(-1, src.getSndPlrHit(), 0);
				}
			}
			if (!barriers.empty())
			{
				for (int tmpBarriers = 0; tmpBarriers < barriers.size() && !hit; ++tmpBarriers)
				{
					if ((projectiles[projectile].getPositionY() >= barriers[tmpBarriers].getPositionY() &&
						projectiles[projectile].getPositionY() <= (barriers[tmpBarriers].getHeight() + barriers[tmpBarriers].getPositionY())) ||
						((projectiles[projectile].getPositionY() + projectiles[projectile].getHeight()) >= barriers[tmpBarriers].getPositionY() &&
							(projectiles[projectile].getPositionY() + projectiles[projectile].getHeight()) <= (barriers[tmpBarriers].getPositionY() + barriers[tmpBarriers].getHeight())))
					{
						if ((projectiles[projectile].getPositionX() >= barriers[tmpBarriers].getPositionX() && projectiles[projectile].getPositionX() <= (barriers[tmpBarriers].getWidth() + barriers[tmpBarriers].getPositionX())
							|| (projectiles[projectile].getPositionX() + projectiles[projectile].getWidth()) >= barriers[tmpBarriers].getPositionX() &&
							(projectiles[projectile].getPositionX() + projectiles[projectile].getWidth()) <= (barriers[tmpBarriers].getWidth() + barriers[tmpBarriers].getPositionX())))
						{
							hit = true;
							if (!barriers.empty())
							{
								explosions.push_back(Entity(projectiles[projectile].getPositionX() - 19, projectiles[projectile].getPositionY()));
								barriers[tmpBarriers].hit(projectiles[projectile].getSpeed());
								if (barriers[tmpBarriers].isDestroyed())
								{
									Mix_PlayChannel(-1, src.getBarrierDestr(), 0);
									barriers.erase(barriers.begin() + tmpBarriers);
								}
								else
									Mix_PlayChannel(-1, src.getBarrierHit(), 0);
							}
							projectiles.erase(projectiles.begin() + projectile);
						}
					}
				}
			}
		}
		else
			projectiles.erase(projectiles.begin() + projectile);

		if (hit)
		{
			std::cout << "PLAYER IS HIT\n";
		}
	}
}

void Game::animUpdate(Sprites& sprites, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, std::vector<Laser>& enemyProjectiles, std::vector<Entity>& explosions)
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
	for (auto& i : enemyProjectiles)
	{
		i.frameUpdate(sprites.getEnemyProjectileNumbSprites(i.getType()));
	}
	for (auto it = explosions.begin(); it != explosions.end();)
	{
		if ((*it).getSpritesN() >= sprites.getexplosionNumbSprites())
			it = explosions.erase(it);
		else
		{
			(*it).explUpdate(sprites.getexplosionNumbSprites());
			++it;
		}
	}
}