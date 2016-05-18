#include "ParticalEmitter.h"





ParticalEmitter::ParticalEmitter( int Intensity, float Interval,float X, float Y, float Z)
{
	//BaseParticel = p;
	intensity = Intensity;
	interval = Interval;
	x = X;
	y = Y;
	z = Z;
	Init();
}

ParticalEmitter::~ParticalEmitter()
{
}

void ParticalEmitter::setPartical(Partical p, int Intensity, float Interval,float X, float Y, float Z)
{
	BaseParticel = p;
	intensity = Intensity;
	interval = Interval;
	x = X;
	y = Y;
	z = Z;
	
}

void ParticalEmitter::drawParticals()
{
	update();
	for (Partical *p : particalList)
	{
		p->draw();
	}
}

void ParticalEmitter::update()
{
	for (int i = 0; i < particalList_size; i++)
	{
		if (particalList[i]->y >= 10)
		{
			particalList.erase(particalList.begin() + i);
			particalList_size--;
		}	
		else
		{
			particalList[i]->y += 0.01f;;
		}
			
	}
	counter++;
	if (counter == 30)
	{
		Init();
		counter = 0;
	}

}

void ParticalEmitter::Init()
{
	printf("%d,", rand());
	for (int i = intensity; i > 0; i--)
	{
		particalList.push_back(new BubblePartical(x + 1.0f*rand()/30000, y , z + 1.0f * rand() / 30000));
	}
	particalList_size = particalList.size();
}

