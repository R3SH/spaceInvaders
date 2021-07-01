#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.w = 39;
	m_pos.h = 24;
	sprN = 0;
}

Entity::~Entity()
{
}

void Entity::frameUpdate(int numberOfSprites)
{
	++sprN;
	if (sprN >= numberOfSprites)
		sprN = 0;
}

void Entity::explUpdate(int numberOfSprites)
{
	++sprN;
}
