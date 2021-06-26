#include "Overseer.h"

Overseer::Overseer()
{
}

Overseer::Overseer(Rndr& rndr, int x, int y, int speed, int projSpeed)
{
	init(rndr);
	m_pos.x = x;
	m_pos.y = y;
	m_pos.w = 24;
	m_pos.h = 24;
	MOVEMENT_SPEED = speed;
	projectileSpeed = projSpeed;
}

Overseer::~Overseer()
{
}

void Overseer::init(Rndr& rndr)
{
	sprN = 0;

	lBound = rndr.getScreenW() / 2 - 260;
	rBound = rndr.getScreenW() / 2 + 260 - 36;
	downBound = rndr.getScreenH() - 300 - 4 * (24 + 10);
}