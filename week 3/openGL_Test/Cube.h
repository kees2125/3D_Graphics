#pragma once
#include "WorldObject.h"
namespace tmp12 {
	class Cube : public WorldObject
	{
	public:
		Cube();
		Cube(float X, float Y, float Z, float Size, int ID, float Pitch, float Yaw);
		~Cube();
		bool pointInCube(float x, float y, float z);
		int cubeID;
		
		float size = 0.5f;
		void draw();
		static void initCube();
		
	private:
		
	};
}
