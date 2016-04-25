#pragma once
#include "matrix.h"
class Shape
{
public:
	enum type { SHAPE_SQUARE, SHAPE_PIRAMIDE, SHAPE_PIN };
	type thistype;
	int polygonindexes[100][4];
	int polygonsize;
	int polygoncount;
	vector vectors[100];
	Shape(type);
	void createCube();
	void createPiramide();
	void createPin();
};