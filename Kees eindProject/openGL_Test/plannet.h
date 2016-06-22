#pragma once
#include "WorldObject.h"
class plannet : public tmp12::WorldObject
{
public:
	plannet(float x, float y, float z,bool isMoon);
	~plannet();
	void draw();
	void update();
	tmp12::WorldObject* moon;
	float rotation;

	
};

