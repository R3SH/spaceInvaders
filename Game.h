#pragma once
#include <SDL.h>
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

class Game
{
public:
	Game();
	~Game();

	void menu(Rndr& rndr, Resource& src, Sprites& sprites);
	void scoreBoard(Rndr& rndr, Resource& src);
	void about(Rndr& rndr, Resource& src, Sprites& sprites);
	void start(Rndr& rndr, Resource& src, Sprites& sprites);

private:
	bool k_exit = false;
	void addEnemies(Rndr& rndr, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers, int movSpeed);
	void addDrones(Rndr& rndr, std::vector<Drone>& drones, int movSpeed);
	void addAliens(Rndr& rndr, std::vector<Alien>& aliens, int movSpeed);
	void addOverseers(Rndr& rndr, std::vector<Overseer>& overseers, int movSpeed);
	void movEnemies(std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers);
	void movDrones(std::vector<Drone>& drones);
	void movAliens(std::vector<Alien>& aliens);
	void movOverseers(std::vector<Overseer>& overseers);
	void animUpdate(Sprites& sprites, std::vector<Drone>& drones, std::vector<Alien>& aliens, std::vector<Overseer>& overseers);
	//void dronesAnimUpdate();
	//void aliensAnimUpdate();
	//void overseersAnimUpdate();
	//void laserAnimUpdate();

	/*void addEnemy(std::vector<Enemy>& enemies);
	void moveEnemies(std::vector<Enemy>& enemies);
	void moveLasers(std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers);

	void checkCollisions(Player& player, std::vector<Enemy>& enemies, std::vector<Laser>& playerLasers, std::vector<Laser>& enemyLasers);
	bool findPlayerLaserCollision(Laser& laser, Enemy& enemy);
	bool findEnemyLaserCollisions(Laser& laser, Player& player);
	bool checkGameOver(std::vector<Enemy>& enemies);
	void enemyShoot(std::vector<Enemy>& enemies, std::vector<Laser>& enemyLasers);
	void resetPlayerPos(Player& player);*/

};