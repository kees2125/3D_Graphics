
#define STB_IMAGE_IMPLEMENTATION
#include "WorldObject.h"
#include "Player.h"
#include "Cube.h"
#include "skyBox.h"
#include <vector>
#include "ParticalEmitter.h"
#include "SolidSphere.h"
#include "BillBordParticalEffects.h"
#include "ObjModel.h"
#include "plannet.h"



using namespace tmp12;
static GLfloat g_nearPlane = 0.1f;
static GLfloat g_farPlane = 101;
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
ParticalEmitter *particalEmitter;
SolidSphere *sphere;
BillBordParticalEffects *fire;
ObjModel *ketel;
plannet *Plannet;



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
	for (int y = 0; y < 2;y+=1)
	{
		for (int z = -10; z < 10; z+=1)
		{
			for (int x = -10; x < 10;x+=1)
			{
				worldObjects.push_back(new Cube(x, y, z, 1.0f,1, 0, 0));
				worldObjects.push_back(new Cube(30+x, y, z, 1.0f, 0, 0, 0));
			}
		}
	}
	worldObjects.push_back(new Cube(10, 1, 0, 1.0f, 2, 0, 0));

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float amb[] = { 0.2,0.2,0.2 };
	float dif[] = { 1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT,amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, amb);
	worldObjects_size = worldObjects.size();
	//particalEmitter = new ParticalEmitter(2, 10, 100, 0.2f, 0, 0, 0);
	//sphere = new SolidSphere(0.3f, 20, 20, "resources/fireAnimate.png", 4);
	fire = new BillBordParticalEffects(2, 3, 4, 2, "resources/fireAnimate.png", 4);
	ketel = new ObjModel("models/ketel/ketel.obj");
	Plannet = new plannet(30, 5, 0,false);
	
}
void move(float angle, float fac) 
{
	player.x += (float)cos((player.pitch + angle) / 180 * M_PI) * fac;
	player.z += (float)sin((player.pitch + angle) / 180 * M_PI) * fac;
}
void moveVertical(bool moveUp, float fac)
{
	if (moveUp)
	{
		player.y -= player.speed *fac;
	}
	else
	{
		player.y += player.speed *fac;
	}
}


void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float pos[] = { player.x,player.y,player.z };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glRotatef(player.yaw, 1, 0, 0);
	glRotatef(player.pitch, 0, 1, 0);
	skybox.drawSkybox(100.0f);
	glTranslatef(player.x, player.y, player.z);
	
	
	for (unsigned int i = 0; i < worldObjects_size;i++)
	{
		worldObjects[i]->draw();
	}
	//particalEmitter->drawParticals();
	glTranslated(2, 5, 5);
	ketel->draw();
	glTranslated(-2, -5, -5);
	Plannet->draw();
	fire->draw();
	
	
	glutSwapBuffers();
}
void slowTick(int i)
{
	
	glutTimerFunc(1000, slowTick, 0);
}
void timerfunc(int i)
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	bool colided = false;
	bool onMoving = false;
	float movingSpeed = 0.16f;
	lastFrameTime = frameTime;
	player.updatePlayer();
	
	if (!player.gravityEffected)
	{
		if (keys[32]) moveVertical(true, deltaTime);
		if (keys['z']) moveVertical(false, deltaTime);
	}
	else
	{
		for (unsigned int i = 0; i < worldObjects_size; i++)
		{
			if (worldObjects[i]->cubeInObject(player.xMin, player.xMax, player.yMin, player.yMax, player.zMin, player.zMax))
			{
				colided = true;
				player.Gspeed = 0.02f;
				break;
			}
		}
		if (!colided)
		{
			player.Gspeed = player.Gspeed * 9.81f *0.16f;
			if (player.Gspeed > 1.56f)
			{
				player.Gspeed = 1.56f;
			}
			player.y += player.Gspeed;
		}
	}
	if (worldObjects[worldObjects_size - 1]->cubeInObject(player.xMin, player.xMax, player.yMin, player.yMax, player.zMin, player.zMax))
	{
		onMoving = true;
	}
	if (worldObjects[worldObjects_size - 1]->gravityEffected)
	{
		if (onMoving)
		{
			player.x += movingSpeed;
		}
		worldObjects[worldObjects_size - 1]->x += movingSpeed;
		Plannet->x += movingSpeed;
		if (worldObjects[worldObjects_size - 1]->x > 19)
		{
			worldObjects[worldObjects_size - 1]->gravityEffected = false;
		}
	}
	else
	{
		if (onMoving)
		{
			player.x -= movingSpeed;
		}
		worldObjects[worldObjects_size - 1]->x -= movingSpeed;
		Plannet->x -= movingSpeed;
		if (worldObjects[worldObjects_size - 1]->x < 10)
		{
			worldObjects[worldObjects_size - 1]->gravityEffected = true;
		}
	}
	if (!player.gravityEffected || colided)
	{
		if (keys['a']) move(0, deltaTime*player.speed);
		if (keys['d']) move(180, deltaTime*player.speed);
		if (keys['w']) { move(90, deltaTime*player.speed); }
		if (keys['s']) move(270, deltaTime*player.speed);
	}
	Plannet->update();
	glutPostRedisplay();

	glutTimerFunc(16, timerfunc, 0);
}
void idle()
{
	
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
	glutTimerFunc(16, timerfunc, 0);
	//glutTimerFunc(1000, slowTick, 0);
	initWorld();
	glutMainLoop();
}