#pragma once
#include "WorldObject.h"
class SolidSphere
{
public:
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);
	void draw(GLfloat x, GLfloat y, GLfloat z);
		~SolidSphere();
		
};

