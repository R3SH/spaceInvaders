#include "Laser.h"

Laser::Laser()
{
}

Laser::Laser(Rndr& rndr, int x, int y, int movSpeed, MovDir mdir, char passedType)
{
	init(rndr);
	m_pos.x = x;
	m_pos.y = y;
	type = passedType;
	if (passedType == 'P')
	{
		m_pos.w = 6;
		m_pos.h = 9;
	}
	else if (passedType == 'D')
	{
		m_pos.w = 9;
		m_pos.h = 18;
	}
	else if (passedType == 'A' || passedType == 'O')
	{
		m_pos.w = 9;
		m_pos.h = 21;
	}
	else
	{
		std::cout << "LASER INIT: INVALID LASER TYPE" << std::endl;
		system("PAUSE");
	}
	MOVEMENT_SPEED = movSpeed;
	lasDir = mdir;
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

bool Laser::chekBounds(Rndr& rndr)
{
	if (m_pos.y >= downBound || m_pos.y <= topBound)
		return false;
	return true;
}
