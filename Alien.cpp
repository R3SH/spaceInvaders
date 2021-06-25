#include "Alien.h"

Alien::Alien()
{
}

Alien::Alien(Rndr& rndr, int x, int y, int speed)
{
	init(rndr);
	m_pos.x = x;
	m_pos.y = y;
	m_pos.w = 33;
	m_pos.h = 24;
	MOVEMENT_SPEED = speed;
}

Alien::~Alien()
{
}

void Alien::init(Rndr& rndr)
{
	sprN = 0;

	lBound = rndr.getScreenW() / 2 - 240;
	rBound = rndr.getScreenW() / 2 + 240;
	downBound = rndr.getScreenH() - 300 - 2 * (24 + 10);
}
