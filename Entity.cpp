#include "Entity.h"

Entity::Entity()
{

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
