#pragma once
#include <GL\freeglut.h>
namespace tmp12 {
	class WorldObject
	{
	public:
		WorldObject();
		~WorldObject();
		virtual bool pointInObject(float x, float y, float z);
		float x;
		float y;
		float z;
		float pitch;
		float yaw;
		bool gravityEffected;
	/*	float getX();
		float getY();
		float getZ();
		float getYaw();
		float getPitch();*/

	protected:
		
	};
}
