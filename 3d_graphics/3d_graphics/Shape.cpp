#include "shape.h"

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
}

void Shape::createCube()
{
	polygonsize = 4;

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

	int cubepolygonindexes[6][4] = { { 0,1,2,3 },{ 4,5,6,7 },{ 0,1,5,4 },{ 1,2,6,5 },{ 2,3,7,6 },{ 3,0,4,7 } };

	for (int i = 0; i < 6; i++)
	{
		for (int p = 0; p < 4; p++)
		{
			polygonindexes[i][p] = cubepolygonindexes[i][p];
		}
	}
}

void Shape::createPiramide()
{
	polygonsize = 3;

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