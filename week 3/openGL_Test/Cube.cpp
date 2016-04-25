#include "Cube.h"

using namespace tmp12;


Cube::Cube()
{
}


Cube::~Cube()
{
}

bool Cube::pointInCube(float x, float y, float z)
{
	return false;
}

void tmp12::Cube::drawCube()
{
	glRotatef(pitch, 1, 0, 0);
	glRotatef(yaw, 0, 1, 0);
	glBegin(GL_QUADS); // leftside *
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //bottom *
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //right *
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //top
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_QUADS); //back
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();

	glBegin(GL_QUADS);  // front
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	glEnd();
}
