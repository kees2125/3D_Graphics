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
	xMin = -size / 2 + x;
	xMax =  size / 2 + x;
	yMin = -size / 2 + y;
	yMax =  size / 2 + y;
	zMin = -size / 2 + z;
	zMax =  size / 2 + z;
}




Cube::~Cube()
{
}

bool tmp12::Cube::pointInObject(float X, float Y, float Z)
{
	if (X >= xMin)
	{
		if (X <= xMax)
		{
			if (Y >= yMin)
			{
				if (Y <= yMax)
				{
					if (Z >= zMin)
					{
						if (Z <= zMax)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool tmp12::Cube::cubeInObject(float Xmin, float Xmax, float Ymin, float Ymax, float Zmin, float Zmax)
{
	return(xMax >= Xmin &&
		xMin <= Xmax &&
		yMax >= Ymin &&
		yMin <= Ymax &&
		zMax >= Zmin &&
		zMin <= Zmax );

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
	glEnable(GL_TEXTURE_2D); //and turn on texturing
	glBindTexture(GL_TEXTURE_2D, textureLiberyID);  //use the texture we want
	glBegin(GL_QUADS);      //and draw a face
	glNormal3f(0.0, 0.0, 1.0);						//back face
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
	glNormal3f(-1.0, 0.0, 0.0);
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
	glNormal3f(0.0, 0.0, -1.0);
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
	glNormal3f(1.0, 0.0, 0.0);
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
	glBegin(GL_QUADS); 
	glNormal3f(0.0, 1.0, 0.0);//top face
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
	glNormal3f(0.0, -1.0, 0.0);
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
	if (textureLiberyID == NULL)
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
