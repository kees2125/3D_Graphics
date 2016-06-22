#pragma once
#include "WorldObject.h"
namespace tmp12 {
	class Player: public WorldObject
	{
	public:
		Player();
		~Player();
		float speed;
		float Gspeed;
		void draw();
		float height;
		float width;
		float depth;
		float xMin;
		float xMax;
		float yMin;
		float yMax;
		float zMin;
		float zMax;
		void updatePlayer();
	};
}
