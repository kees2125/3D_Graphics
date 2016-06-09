#include "Player.h"

using namespace tmp12;


Player::Player()
{
	x = 0;
	y = -4;
	z = 0;
	pitch = 0;
	yaw = 0;
	speed = 3.0f;
	height = 4.5f;
	width = 1.5f;
	depth = 1.5f;
	xMin = -width / 2 + x;
	xMax = width / 2 + x;
	yMin = -height / 2 + y;
	yMax = height / 2 + y;
	zMin = -depth / 2 + z;
	zMax = depth/ 2 + z;
}


Player::~Player()
{
}

void tmp12::Player::draw()
{
}

void tmp12::Player::updatePlayer()
{
	xMin = -width / 2 + x;
	xMax = width / 2 + x;
	yMin = -height / 2 + y;
	yMax = height / 2 + y;
	zMin = -depth / 2 + z;
	zMax = depth / 2 + z;
}
