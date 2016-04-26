#include "Cube.h"

using namespace tmp12;

static unsigned int textureLiberyID;
Cube::Cube()
{
	
}

tmp12::Cube::Cube(float X, float Y, float Z, float Size, int ID, float Pitch, float Yaw)
{
	x = X;
	y = Y;
	z = Z;
	size = Size;
	cubeID = ID;
	pitch = Pitch;
	yaw = Yaw;
}




Cube::~Cube()
{
}

bool Cube::pointInCube(float x, float y, float z)
{
	return false;
}

void Cube::draw()
{
	glColor3f(1, 1, 1);
	float multiplier = 0.0625f;
	int cubeIDY =  floor(cubeID / 16);
	int cubeIDX = cubeID - (cubeIDY * 16);
	float aX = cubeIDX*multiplier;      //left bind location for x replace the 0 with this
	float aY = cubeIDY*multiplier;		//left bind location for Y replace the 0 with this
	float bX = aX + multiplier;			//left bind location for x replace the 1 with this
	float bY = aY + multiplier;			//left bind location for Y replace the 1 with this
	/*aX = 0;
	aY = 0;
	bX = 0.0625f;
	bY = 0.0625f;*/
	glRotatef(pitch, x+1, y, z);
	glRotatef(yaw, x, y+1, z);
	glEnable(GL_TEXTURE_2D);        //and turn on texturing
	glBindTexture(GL_TEXTURE_2D, textureLiberyID);  //use the texture we want
	glBegin(GL_QUADS);      //and draw a face
							//back face
	glTexCoord2f(aX, aY);      //use the correct texture coordinate
	glVertex3f(size / 2 +x, size / 2 + y, size / 2 + z);       //and a vertex
	glTexCoord2f(bX, aY);      //and repeat it...
	glVertex3f(-size / 2 + x, size / 2 + y, size / 2 + z);
	glTexCoord2f(bX, bY);
	glVertex3f(-size / 2 + x, -size / 2 + y, size / 2 + z);
	glTexCoord2f(aX, bY);
	glVertex3f(size / 2 + x, -size / 2 + y, size / 2 + z);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, skyBoxSides[SKY_LEFT]);
	glBegin(GL_QUADS);
	//left face
	glTexCoord2f(aX, aY);
	glVertex3f(-size / 2 + x, size / 2 + y, size / 2 + z);
	glTexCoord2f(bX, aY);
	glVertex3f(-size / 2 + x, size / 2 + y, -size / 2 + z);
	glTexCoord2f(bX, bY);
	glVertex3f(-size / 2 + x, -size / 2 + y, -size / 2 + z);
	glTexCoord2f(aX, bY);
	glVertex3f(-size / 2 + x, -size / 2 + y, size / 2 + z);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, skyBoxSides[SKY_FRONT]);
	glBegin(GL_QUADS);
	//front face
	glTexCoord2f(bX, aY);
	glVertex3f(size / 2 + x, size / 2 + y, -size / 2 + z);
	glTexCoord2f(aX, aY);
	glVertex3f(-size / 2 + x, size / 2 + y, -size / 2 + z);
	glTexCoord2f(aX, bY);
	glVertex3f(-size / 2 + x, -size / 2 + y, -size / 2 + z);
	glTexCoord2f(bX, bY);
	glVertex3f(size / 2 + x, -size / 2 + y, -size / 2 + z);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, skyBoxSides[SKY_RIGHT]);
	glBegin(GL_QUADS);
	//right face
	glTexCoord2f(aX, aY);
	glVertex3f(size / 2 + x, size / 2 + y, -size / 2 + z);
	glTexCoord2f(bX, aY);
	glVertex3f(size / 2 + x, size / 2 + y, size / 2 + z);
	glTexCoord2f(bX, bY);
	glVertex3f(size / 2 + x, -size / 2 + y, size / 2 + z);
	glTexCoord2f(aX, bY);
	glVertex3f(size / 2 + x, -size / 2 + y, -size / 2 + z);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, skyBoxSides[SKY_TOP]);
	glBegin(GL_QUADS);                      //top face
	glTexCoord2f(bX, aY);
	glVertex3f(size / 2 + x, size / 2 + y, size / 2 + z);
	glTexCoord2f(aX, aY);
	glVertex3f(-size / 2 + x, size / 2 + y, size / 2 + z);
	glTexCoord2f(aX, bY);
	glVertex3f(-size / 2 + x, size / 2 + y, -size / 2 + z);
	glTexCoord2f(bX, bY);
	glVertex3f(size / 2 + x, size / 2 + y, -size / 2 + z);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, skyBoxSides[SKY_BOTTOM]);
	glBegin(GL_QUADS);
	//bottom face
	glTexCoord2f(bX, bY);
	glVertex3f(size / 2 + x, -size / 2 + y, size / 2 + z);
	glTexCoord2f(aX, bY);
	glVertex3f(-size / 2 + x, -size / 2 + y, size / 2 + z);
	glTexCoord2f(aX, aY);
	glVertex3f(-size / 2 + x, -size / 2 + y, -size / 2 + z);
	glTexCoord2f(bX, aY);
	glVertex3f(size / 2 + x, -size / 2 + y, -size / 2 + z);
	glEnd();

	glRotatef(-pitch, x + 1, y, z);
	glRotatef(-yaw, x, y + 1, z);

}

void tmp12::Cube::initCube()
{
	if (true)
	{
		int width, height, bpp;
		glGenTextures(1, &textureLiberyID);
		unsigned char* texture = stbi_load("resources/terainMap.png", &width, &height, &bpp, 4);
		glBindTexture(GL_TEXTURE_2D, textureLiberyID);
		glTexImage2D(GL_TEXTURE_2D,
			0,		//level
			GL_RGBA,		//internal format
			width,		//width
			height,		//height
			0,		//border
			GL_RGBA,		//data format
			GL_UNSIGNED_BYTE,	//data type
			texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //same if the image bigger
	}
}
