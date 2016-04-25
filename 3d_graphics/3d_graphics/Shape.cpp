#include "shape.h"
#define _USE_MATH_DEFINES
#include <math.h>

Shape::Shape(enum type shapetype)
{
	if (shapetype == SHAPE_SQUARE)
	{
		createCube();
	}
	else if (shapetype == SHAPE_PIRAMIDE)
	{
		createPiramide();
	}
	else if (shapetype == SHAPE_PIN)
	{
		createPin();
	}
	thistype = shapetype;
}

void Shape::createCube()
{
	polygonsize = 4;
	polygoncount = 8;

	vector a = vector(-1, -1, -1);
	vector b = vector(1, -1, -1);
	vector c = vector(1, 1, -1);
	vector d = vector(-1, 1, -1);
	vector e = vector(-1, -1, 1);
	vector f = vector(1, -1, 1);
	vector g = vector(1, 1, 1);
	vector h = vector(-1, 1, 1);

	vector list[8] = { a,b,c,d,e,f,g,h };

	for (int i = 0; i < 8; i++)
	{
		vectors[i] = list[i];
	}

	int cubepolygonindexes[8][4] = { { 0,1,2,3 },{ 4,5,6,7 },{ 0,1,5,4 },{ 1,2,6,5 },{ 2,3,7,6 },{ 3,0,4,7 } };

	for (int i = 0; i < polygoncount; i++)
	{
		for (int p = 0; p < polygonsize; p++)
		{
			polygonindexes[i][p] = cubepolygonindexes[i][p];
		}
	}
}

void Shape::createPiramide()
{
	polygonsize = 3;
	polygoncount = 6;

	int polygonindexespiramide[6][3] = { { 0,1,2 },{ 1,2,3 },{ 0,1,4 },{ 1,2,4 },{ 2,3,4 },{ 3,0,4 } };

	vector pa = vector(-1, -1, 1);
	vector pb = vector(1, -1, 1);
	vector pc = vector(-1, -1, -1);
	vector pd = vector(1, -1, -1);
	vector pe = vector(0, 1, 0);

	vector list[5] = { pa,pb,pc,pd,pe };

	for (int i = 0; i < 5; i++)
	{
		vectors[i] = list[i];
	}

	for (int i = 0; i < 6; i++)
	{
		for (int p = 0; p < 3; p++)
		{
			polygonindexes[i][p] = polygonindexespiramide[i][p];
		}
	}
}

void Shape::createPin()
{
	polygonsize = 3;
	polygoncount = 3;

	vector list[100];
	
	int polygonindexespin[100][3];

	for (int i = 0; i < polygoncount; i++)
	{
		list[i * 3] = vector(sinf(M_PI * 2 / polygoncount * i), -1, cosf(M_PI * 2 / polygoncount * i));
		list[i * 3 + 1] = vector(0, 1, 0);
		list[i * 3 + 2] = vector(0, 1, 0);
		//list[i * 3 + 2] = vector(sinf(M_PI * 2 / polygoncount * (i + 1)), -1, cosf(M_PI * 2 / polygoncount * (i + 1)));
	}

	for (int i = 0; i < polygoncount; i++)
	{
		polygonindexespin[i][0] = 0 + 3 * i;
		polygonindexespin[i][1] = 1 + 3 * i;
		polygonindexespin[i][2] = 2 + 3 * i;
	}

	for (int i = 0; i < polygoncount * polygonsize; i++)
	{
		vectors[i] = list[i];
	}

	for (int i = 0; i < polygoncount; i++)
	{
		for (int p = 0; p < polygonsize; p++)
		{
			polygonindexes[i][p] = polygonindexespin[i][p];
		}
	}
}