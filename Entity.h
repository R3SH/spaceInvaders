#pragma once
#include <SDL.h>
#include <vector>

class Entity
{
public:
	Entity();
	Entity(int x, int y);
	~Entity();

	SDL_Rect getPosition() { return m_pos; }
	int getSpritesN() { return sprN; }
	int getPositionX() { return m_pos.x; }
	int getPositionY() { return m_pos.y; }
	int getWidth() { return m_pos.w; }
	int getHeight() { return m_pos.h; }
	int getSpeed() { return MOVEMENT_SPEED; }
	int getProjSpeed() { return projectileSpeed; }
	int getLBound() { return lBound; }
	int getRBound() { return rBound; }
	int getDownBound() { return downBound; };
	void setXPos(int xPos) { m_pos.x = xPos; }
	void setYPos(int yPos) { m_pos.y = yPos; }
	void frameUpdate(int numberOfSprites);
	void explUpdate(int numberOfSprites);

protected:
	SDL_Rect m_pos;
	//Current sprite
	int sprN;
	//Movement speed of entity
	int MOVEMENT_SPEED;
	//Projectile Speed
	int projectileSpeed;
	//MovementBoundaries
	int lBound, rBound;
	int topBound, downBound;
};