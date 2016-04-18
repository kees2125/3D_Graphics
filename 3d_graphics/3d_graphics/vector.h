#pragma once
class vector
{
public:
	float x;
	float y;
	float z;
	vector();
	vector(float X,float Y , float Z);
	~vector();

	float Length();
	void normilise();
};

