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

	reset(rndr);

	lBound = rndr.getScreenW() / 2 - 260;
	rBound = rndr.getScreenW() / 2 + 260 - m_pos.w;
	
	lives = 3;
	score = 0;
	projectileSpeed = 8;
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

void Player::shoot(Rndr& rndr, std::vector<Laser>& projectiles)
{
	projectiles.push_back(Laser(rndr, m_pos.x + 16, m_pos.y, projectileSpeed, MovDir::UP, 'P'));		//m_pos.y - 24
}

void Player::hit(Rndr& rndr)
{
	--lives;
	reset(rndr);
}

void Player::reset(Rndr& rndr)
{
	setXPos(rndr.getScreenW() / 2);
	setYPos(rndr.getScreenH() - 23);
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

void Player::incrScore(int n)
{
	score += n;
}

bool Player::dead()
{
	if (lives < 0)
		return true;
	return false;
}
