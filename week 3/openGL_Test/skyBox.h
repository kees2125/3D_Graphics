#pragma once
#include "WorldObject.h"

namespace tmp12 {
	class skyBox
	{
	public:
		skyBox();
		~skyBox();
		void drawSkybox(float size);
		void killskybox();
		void initskybox();
	};

}