#include "Laser.h"

Laser::Laser()
{
}

Laser::Laser(Rndr& rndr, int x, int y, int movSpeed)
{
	init(rndr);
	m_pos.x = x;
	m_pos.y = y;
	m_pos.w = 6;
	m_pos.h = 9;
	MOVEMENT_SPEED = movSpeed;
}

Laser::~Laser()
{
}

void Laser::init(Rndr& rndr)
{
	sprN = 0;

	topBound = 0;
	downBound = rndr.getScreenH();
}
