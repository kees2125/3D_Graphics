#include <GL\freeglut.h>
#include <iostream>

static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 800;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static float rotate = 1;
static int   rotateMode = 1;
static float playerX = 0;
static float playerY = 0;
static float playerZ = -10;
static float playerYaw = 0;
static float playerPitch = 0;

static int mouseX, mouseY;

void drawCube()
{
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
void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	playerX, playerY, playerZ,
				playerX, 0, 0,
				0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	switch (rotateMode)
	{
	case 1:
		glRotated(rotate, 0, 1, 0);
		break;
	case 2:
		break;
		glRotated(rotate, 1, 0, 0);
	case 3:
		glRotated(rotate, 0, 0, 1);
		break;
	default:
		break;
	}
	glRotated(rotate, 0, 1, 0);
	drawCube();
	glTranslated(4, 0, 0);
	drawCube();
	glTranslated(0, 0, 3);
	drawCube();
	glTranslated(-2, 4, -1);
	drawCube();
	

	
	glutSwapBuffers();
}
void idle()
{
	
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
	std::cout << key;
	switch (key)
	{
		case 'a':
			playerX -= 1.0f;
		break;
		case 'w':
			playerZ += 1.0f;
			break;
		case 's':
			playerZ -= 1.0f;
			break;
		case 'd':
			playerX += 1.0f;
			break;
		case 'q':
			rotate -= 1.0f;
			break;
		case 'e':
			rotate += 1.0f;
			break;
		case 27:
			break;
		case '1':
			rotateMode = 1;
			break;
		case '2':
			rotateMode = 2;
			break;
		case'3':
			rotateMode = 3;
			break;
	}
}
void mouseMoveFuct(int x, int y)
{
	if (mouseX == NULL)
	{
		mouseX = x;
		mouseY = y;
	}
	playerPitch += x - mouseX;
	playerYaw += y - mouseY;
}
int main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(g_Width, g_Height);
	glutInit(&argc, argv);
	glutCreateWindow("RemCOOOO");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyHandler);
	glutMotionFunc(mouseMoveFuct);
	glutIdleFunc(idle);
	glutMainLoop();
}