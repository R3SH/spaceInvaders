#include "Overseer.h"

Overseer::Overseer()
{
}

Overseer::Overseer(Rndr& rndr, int x, int y, int speed)
{
	init(rndr);
	m_pos.x = x;
	m_pos.y = y;
	m_pos.w = 24;
	m_pos.h = 24;
	MOVEMENT_SPEED = speed;
}

Overseer::~Overseer()
{
}

void Overseer::init(Rndr& rndr)
{
	sprN = 0;

	lBound = rndr.getScreenW() / 2 - 240;
	rBound = rndr.getScreenW() / 2 + 240;
	downBound = rndr.getScreenH() - 300 - 4 * (24 + 10);
}