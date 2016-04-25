#pragma once
#include "WorldObject.h"
namespace tmp12 {
	class Player: public WorldObject
	{
	public:
		Player();
		~Player();
		float speed;
	};
}
