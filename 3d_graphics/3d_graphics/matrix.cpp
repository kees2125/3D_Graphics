#include "matrix.h"
#include <math.h>

Matrix::Matrix()
{
	
}
Matrix::Matrix(float a[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			data[i][k] = a[i][k];
		}
	}
}

Matrix::~Matrix()
{
}

vector Matrix::MultiplyByVector(vector a)
{
	vector temp = vector(0, 0, 0);
	temp.x = data[0][0] * a.x + data[0][1] * a.y + data[0][2] * a.z + data[0][3] * 1;
	temp.y = data[1][0] * a.x + data[1][1] * a.y + data[1][2] * a.z + data[1][3] * 1;
	temp.z = data[2][0] * a.x + data[2][1] * a.y + data[2][2] * a.z + data[2][3] * 1;

	return temp;
}

Matrix Matrix::MultiplyBYMatrix(Matrix m)
{
	Matrix temp = Matrix();
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			temp.data[i][k] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				temp.data[i][k] = data[i][k]*m.data[k][j];
			}
		}
	}
	return temp;
}

Matrix Matrix::Identity()
{
	float temp[4][4] = { 
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 } };
	Matrix id  = Matrix(temp);

	return id;
}

Matrix Matrix::Translate(vector a)
{
	float temp[4][4] = { 
		{ 1,0,0,a.x },
		{ 0,1,0,a.y },
		{ 0,0,1,a.z },
		{ 0,0,0,1 } };
	Matrix id = Matrix(temp);

	return id;
}

Matrix Matrix::Rotate(vector a,float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	float temp[4][4] = { 
		{ a.x*a.x*(1-c)+c,		a.x*a.y*(1-c)-a.z*s,	a.x*a.z*(1-c)+a.y*s,		0},
		{ a.x*a.y*(1-c)+a.z*s,	a.y*a.y*(1-c)+c,		a.y*a.z*(1-c)-a.x*s,		0},
		{ a.x*a.z*(1-c)-a.y*s,	a.y*a.z*(1-c)+a.x*s,	a.z*a.z*(1-c)+c,			0},
		{ 0,0,0,1 } };
	Matrix id = Matrix(temp);

	return id;
}

Matrix Matrix::Perspective(float fov,float aspact,float nearp,float farp)
{
	float temp[4][4] = {
		{ tanf(fov/2)/aspact,0,0,0 },
		{ 0	,	tanf(fov/2),0	,0 },
		{ 0,0,farp/(farp-nearp),farp*nearp / (farp - nearp) },
		{ 0,0,0,1 } };
	Matrix id = Matrix(temp);

	return id;
}

Matrix Matrix::LookAtMatrix()
{
	return Matrix();
}


