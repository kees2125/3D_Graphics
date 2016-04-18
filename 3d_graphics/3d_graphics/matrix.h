#pragma once
#include "vector.h"
class Matrix
{
public:
	float data[4][4];

	Matrix();
	Matrix(float a[4][4]);
	~Matrix();
	void MultiplyByVector(vector a);
	void MultiplyBYMatrix(Matrix m);
	static Matrix Identity();
	static Matrix Translate(vector a);
	static Matrix Rotate(vector a,float angle);
	static Matrix Perspective(float fov, float aspact, float nearp, float farp);
	static Matrix LookAtMatrix();
};

