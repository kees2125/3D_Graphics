#pragma once
#include "WorldObject.h"
namespace tmp12 {
	class Cube : public WorldObject
	{
	public:
		Cube();
		~Cube();
		bool pointInCube(float x, float y, float z);
		int cubeID;
		float size = 0.5f;
		void drawCube();
	private:
		
	};
}
