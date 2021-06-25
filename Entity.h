#pragma once
#include <SDL.h>
#include <vector>

class Entity
{
public:
	Entity();
	~Entity();

	SDL_Rect getPosition() { return m_pos; }
	int getSpritesN() { return sprN; }
	int getPositionX() { return m_pos.x; }
	int getPositionY() { return m_pos.y; }
	int getSpeed() { return MOVEMENT_SPEED; }
	int getLBound() { return lBound; }
	int getRBound() { return rBound; }
	int getDownBound() { return downBound; };
	void setXPos(int xPos) { m_pos.x = xPos; }
	void setYPos(int yPos) { m_pos.y = yPos; }
	void frameUpdate(int numberOfSprites);

protected:
	SDL_Rect m_pos;
	//Current sprite
	int sprN;
	//Starting position of entity
	int START_XPOS;
	int START_YPOS;
	//Movement speed of entity
	int MOVEMENT_SPEED;
	//MovementBoundaries
	int lBound, rBound;
	int topBound, downBound;
};