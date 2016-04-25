#define _USE_MATH_DEFINES
#include <iostream>
#include "WorldObject.h"
#include "Player.h"
#include "Cube.h"
#include <cstdio>
#include <cmath>

using namespace tmp12;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 800;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static char keys[255];
static int mouseX, mouseY;
float lastFrameTime = 0;
Player player;

void init()
{
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

void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	player.x, player.y, player.z,
				0, 0, 0,
				0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	

	

	
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
		exit(0);
	keys[key] = true;
}
void keyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}
void mouseMoveFuct(int x, int y)
{
	int dx = x - g_Width / 2;
	int dy = y - g_Height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		player.pitch += dx / 10.0f;
		player.yaw += dy / 10.0f;
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
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyHandler);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mouseMoveFuct);
	glutIdleFunc(idle);
	glutMainLoop();
}