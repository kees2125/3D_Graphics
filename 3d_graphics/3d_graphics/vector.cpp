#include "vector.h"
#include <math.h>



vector::vector()
{
	x = 0;
	y = 0;
	z = 0;
}

vector::vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}


vector::~vector()
{
}

float vector::Length()
{
	return sqrt(x * x + y * y + z * z);
}

void vector::normilise()
{
	float length = this->Length();

	if (length != 0) {
		x = x / length;
		y = y / length;
		z = z / length;
	}

}
