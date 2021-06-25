#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(Rndr& rndr, Resource& src)
{
	MOVEMENT_SPEED = 10;

	sprN = 0;

	m_pos.x = 100;
	m_pos.y = 100;
	m_pos.w = 38;
	m_pos.h = 24;

	lBound = rndr.getScreenW() / 2 - 240;
	rBound = rndr.getScreenW() / 2 + 240;
	
	lives = 3;
	score = 0;
}

void Player::plrMov(SDL_Event& e)
{
	switch (e.key.keysym.sym)
	{
		//Move right
	case SDLK_RIGHT:
		m_pos.x += MOVEMENT_SPEED;
		break;
		//Move left
	case SDLK_LEFT:
		m_pos.x -= MOVEMENT_SPEED;
		break;
	}
}

void Player::boundsCheck()
{
	if (m_pos.x <= lBound) {
		m_pos.x = lBound;
	}
	if (m_pos.x >= rBound) {
		m_pos.x = rBound;
	}
}
