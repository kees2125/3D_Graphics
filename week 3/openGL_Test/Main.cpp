#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "WorldObject.h"
#include "Player.h"
#include "Cube.h"
#include <cstdio>
#include <cmath>

using namespace tmp12;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1001;
static int g_Width = 800;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static char keys[255];
static int mouseX, mouseY;
float lastFrameTime = 0;
Player player;
enum { SKY_LEFT = 0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM };
unsigned int skyBox[6];
Cube cube;

void init()
{
	/*int width, height, bpp;
	skyBox = stbi_load("forrest-skybox.png", &width, &height, &bpp, 4);
	glTexImage2D(..);
	stbi_image_free(imgData);*/

	for (int i = 0; i < 255; i++)
	{
		keys[i] = 0;
	}
}
void move(float angle, float fac) 
{
	player.x += (float)cos((player.pitch + angle) / 180 * M_PI) * fac;
	player.y += (float)sin((player.pitch + angle) / 180 * M_PI) * fac;
}
void initskybox()
{
	for (int x = 0; x < 6; x++)
	{
		glGenTextures(1, &skyBox[skyBox[x]]);
	}

	int width, height, bpp;
	unsigned char* l = stbi_load("leftS.png", &width, &height, &bpp, 4);
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_LEFT]);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		l);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* ba = stbi_load("backS.png", &width, &height, &bpp, 4);
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_BACK]);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		ba);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* r = stbi_load("rightS.png", &width, &height, &bpp, 4);
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_RIGHT]);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		r);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* f = stbi_load("frontS.png", &width, &height, &bpp, 4);
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_FRONT]);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* t = stbi_load("topS.png", &width, &height, &bpp, 4);
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_TOP]);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* bo = stbi_load("bottomS.png", &width, &height, &bpp, 4);
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_BOTTOM]);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		bo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	 
}
void killskybox()
{
	glDeleteTextures(6, &skyBox[0]);
}
void drawSkybox(float size)
{
	bool b1 = glIsEnabled(GL_TEXTURE_2D);     //new, we left the textures turned on, if it was turned on
	glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);       //turn off depth texting
	glEnable(GL_TEXTURE_2D);        //and turn on texturing
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_BACK]);  //use the texture we want
	glBegin(GL_QUADS);      //and draw a face
							//back face
	glTexCoord2f(0, 0);      //use the correct texture coordinate
	glVertex3f(size / 2, size / 2, size / 2);       //and a vertex
	glTexCoord2f(1, 0);      //and repeat it...
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_LEFT]);
	glBegin(GL_QUADS);
	//left face
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_FRONT]);
	glBegin(GL_QUADS);
	//front face
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	//right face
	glTexCoord2f(0, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_TOP]);
	glBegin(GL_QUADS);                      //top face
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_BOTTOM]);
	glBegin(GL_QUADS);
	//bottom face
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
	glEnable(GL_DEPTH_TEST);
	if (!b1)
		glDisable(GL_TEXTURE_2D);
}

void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(player.yaw, 1, 0, 0);
	glRotatef(player.pitch, 0, 1, 0);
	glTranslatef(player.x, player.z, player.y);
	drawSkybox(400.0f);
	cube.drawCube();
	

	

	
	glutSwapBuffers();
}
void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed); 

	glutPostRedisplay();
	
}
void reshape(GLint width, GLint height)
{
	g_Width = width;
	g_Height = height;
	glViewport(0, 0, g_Width, g_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
}
void keyHandler(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
		killskybox();
	}
	keys[key] = true;
}
void keyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}


bool movedCursor = false;
void mouseMoveFuct(int x, int y)
{
	if (movedCursor)
	{
		movedCursor = false;
		return;
	}
	int dx = x - g_Width / 2;
	int dy = y - g_Height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		player.pitch += dx / 10.0f;
		player.yaw += dy / 10.0f;
		
		movedCursor = true;
		glutWarpPointer(g_Width / 2, g_Height / 2);
	}
}
int main(int argc, char *argv[])
{
	init();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(g_Width, g_Height);
	glutInit(&argc, argv);
	glutCreateWindow("RemCOOOO");
	initskybox();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyHandler);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mouseMoveFuct);
	glutIdleFunc(idle);
	glutMainLoop();
}