#pragma once
#include "WorldObject.h"
namespace tmp12 {
	class Cube : public WorldObject
	{
	public:
		Cube();
		Cube(float X, float Y, float Z, float Size, int type, float Pitch, float Yaw);
		~Cube();
		static enum type { grass, dirt, wood, rose };
		bool pointInObject(float X, float Y, float Z);
		bool cubeInObject(float Xmin, float Xmax, float Ymin, float Ymax, float Zmin, float Zmax);
		int cubeID;
		int blockType;
		bool moveingForward;
		float xMin;
		float xMax;
		float yMin;
		float yMax;
		float zMin;
		float zMax;
		float size = 0.5f;
		void draw();
		static void initCube();
		
	private:
		
	};
}
