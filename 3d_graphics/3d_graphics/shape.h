#pragma once
#include "matrix.h"
class Shape
{
public:
	enum type { SHAPE_SQUARE, SHAPE_PIRAMIDE };
	int polygonindexes[6][4];
	vector vectors[8];
	Shape(type);
};