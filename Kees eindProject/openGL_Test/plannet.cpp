#include "plannet.h"
#include "Cube.h"



plannet::plannet(float x, float y, float z, bool isMoon)
{
	this->x = x;
	this->y = y;
	this->z = z;
	rotation = 0;
	if (!isMoon)
	{
		moon = new plannet(cos(rotation) * 2, 0, sin(rotation) * 2,true);
	}
}


plannet::~plannet()
{
}

void plannet::draw()
{
	glTranslated(this->x, this->y, this->z);
	glutSolidSphere(1, 20, 20);
	glTranslated(moon->x, moon->y, moon->z);
	glutSolidSphere(0.5f, 10, 10);
	glTranslated(-this->x, -this->y, -this->z);
	glTranslated(-moon->x, -moon->y, -moon->z);
}

void plannet::update()
{
	rotation+= 0.01f;
	if (rotation > 6.28f)
	{
		rotation = 0;
	}
	moon->x =  cos(rotation) * 2;
	moon->z =  sin(rotation) * 2;

}
