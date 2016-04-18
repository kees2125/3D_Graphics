#include "matrix.h"
#include <math.h>

Matrix::Matrix()
{
	
}
Matrix::Matrix(float a[4][4])
{

}

Matrix::~Matrix()
{
}

void Matrix::MultiplyByVector(vector a)
{
}

void Matrix::MultiplyBYMatrix(Matrix m)
{
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


