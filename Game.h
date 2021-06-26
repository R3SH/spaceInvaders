#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

//struct Laser;
//struct Enemy;
class Resource;
class Rndr;
class Sprites;
class Player;
class Drone;
class Alien;
class Overseer;
class Laser;

class Game
{
public:
	Game();
	~Game();

	void menu(Rndr& rndr, Resource& src, Sprites& sprites);
	void scoreBoard(Rndr& rndr, Resource& src);
	void about(Rndr& rndr, Resource& src, Sprites& sprites);
	void start(Rndr& rndr, Resource& src, Sprites& sprites);
	bool pause(Rndr& rndr, Resource& src);

private:
	bool k_exit = false;
	void addEnemies(Rndr& rndr, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, int movSpeed, int projSpeed);
	void addDrones(Rndr& rndr, std::vector<Drone>& drones, int movSpeed, int projSpeed);
	void addAliens(Rndr& rndr, std::vector<Alien>& aliens, int movSpeed, int projSpeed);
	void addOverseers(Rndr& rndr, std::vector<Overseer>& overseers, int movSpeed, int projSpeed);
	void movEnemies(std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers);
	int movDrones(std::vector<Drone>& drones);
	int movAliens(std::vector<Drone>& drones, std::vector<Alien>& aliens, int maxDr);
	void movOverseers(std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, int maxDr, int maxAl);
	void movProjectiles(std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles);
	void movPlrProjectiles(std::vector<Laser>& projectiles);
	void movEnemyProjectiles(std::vector<Laser>& projectiles);
	void enemyShoot(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& enemyLasers, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers);
	void checkProjectiles(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& plrProjectiles, std::vector<Laser>& enemyProjectiles,
		std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers);
	void checkPlrProjectile(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& projectiles, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers);
	void checkEnemyProjectile(Rndr& rndr, Player& plr, Resource& src, std::vector<Laser>& projectiles);
	void animUpdate(Sprites& sprites, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, std::vector<Laser>& enemyProjectiles);

};