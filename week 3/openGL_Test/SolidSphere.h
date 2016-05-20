#pragma once
#include "WorldObject.h"
class SolidSphere
{
public:
	SolidSphere(float radius, unsigned int rings, unsigned int sectors,char* path);
	void draw(GLfloat x, GLfloat y, GLfloat z);
		~SolidSphere();
		void init();
private:
	char* TexturePath;
};

