
#define STB_IMAGE_IMPLEMENTATION
#include "WorldObject.h"
#include "Player.h"
#include "Cube.h"
#include "skyBox.h"
#include <vector>



using namespace tmp12;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1001;
static int g_Width = 800;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static char keys[255];
static int mouseX, mouseY;
bool godMode = 1;
float lastFrameTime = 0;
std::vector<WorldObject *> worldObjects;
std::vector<WorldObject *>::size_type worldObjects_size;
Player player;
skyBox skybox;


void init()
{

	for (int i = 0; i < 255; i++)
	{
		keys[i] = 0;
	}
	
	
}
void initWorld()
{
	Cube::initCube();
	for (int y = 0; y < 4;y++)
	{
		for (int z = -10; z < 10; z++)
		{
			for (int x = -10; x < 10;x++)
			{
				worldObjects.push_back(new Cube(x, y, z, 1.0f, y+z, 0, 0));
			}
		}
	}

	worldObjects_size = worldObjects.size();
}
void move(float angle, float fac) 
{
	player.x += (float)cos((player.pitch + angle) / 180 * M_PI) * fac;
	player.y += (float)sin((player.pitch + angle) / 180 * M_PI) * fac;
}
void moveVertical(bool moveUp,float fac)
{
	if (moveUp)
	{
		player.z -= player.speed *fac;
	}
	else
	{
		player.z += player.speed *fac;
	}
}


void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(player.yaw, 1, 0, 0);
	glRotatef(player.pitch, 0, 1, 0);
	skybox.drawSkybox(1000.0f);
	glTranslatef(player.x, player.z, player.y);

	glDisable(GL_LIGHTING);
	
	for (unsigned int i = 0; i < worldObjects_size;i++)
	{
		worldObjects[i]->draw();
	}
	

	
	glutSwapBuffers();
}
void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	bool colided = false;
	lastFrameTime = frameTime;
	if (!player.gravityEffected)
	{
		if (keys[32]) moveVertical(true, deltaTime);
		if (keys['z']) moveVertical(false, deltaTime);
	}
	else
	{
		for (unsigned int i = 0; i < worldObjects_size;i++)
		{
			if (worldObjects[i]->cubeInObject(player.xMin,player.xMax,player.yMin,player.yMax,player.zMin,player.zMax))
			{
				colided = true;
				printf("true");
				break;
			}
		}
		if (!colided)
		{
			moveVertical(false, 0.01f);
		}
	}
	if (!player.gravityEffected ||colided)
	{
		if (keys['a']) move(0, deltaTime*player.speed);
		if (keys['d']) move(180, deltaTime*player.speed);
		if (keys['w']) { move(90, deltaTime*player.speed); printf("%f,%f,%f\n", player.x, player.y, player.z); }
		if (keys['s']) move(270, deltaTime*player.speed);
	}
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
		skybox.killskybox();
	}
	if (key == 'g') player.gravityEffected = !player.gravityEffected;
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
	skybox.initskybox();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyHandler);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mouseMoveFuct);
	glutIdleFunc(idle);
	initWorld();
	glutMainLoop();
}