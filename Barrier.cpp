#include "Barrier.h"

Barrier::Barrier()
{
}

Barrier::Barrier(int x, int y, int hlth)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.w = 66;
	m_pos.h = 48;
	sprN = 0;
	health = hlth;
	initialHealth = hlth;
}

Barrier::~Barrier()
{
}

void Barrier::setHealth(int hlth)
{
	health = hlth;
}

void Barrier::hit(int damage)
{
	health -= damage;
	if (health > 0)
	{
		sprN = 2 - health / (initialHealth / 3);
	}
}

bool Barrier::isDestroyed()
{
	if (health > 0)
		return false;
	else
		return true;
}
