#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\color.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"

void init()
{
	al_init();
	al_init_font_addon();
	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	ALLEGRO_FONT* font = al_create_builtin_font();
	al_flip_display();
	al_init_primitives_addon();


}
int main()
{
	init();

	//int polygonindexes[6][4] = { {0,1,2,3}, {4,5,6,7}, {0,1,4,5}, ;


	vector a = vector(-1, -1, -1);
	vector b = vector( 1, -1, -1);
	vector c = vector( 1,  1, -1);
	vector d = vector(-1,  1, -1);
	vector e = vector(-1, -1,  1);
	vector f = vector( 1, -1,  1);
	vector g = vector( 1,  1,  1);
	vector h = vector( -1, 1,  1);

	vector list[8] = { a,b,c,d,e,f,g,h };

	Matrix perspect = Matrix::Perspective(90, (6 / 8.0f), 0.1, 20);
	Matrix translate = Matrix::Translate(vector(5, 0, 5));
	//Matrix rotatie = Matrix::Rotate(vector(1, 1, 1), ALLEGRO_PI / 5);

	for (int i = 0; i < 8; i++)
	{
		list[i] = perspect.MultiplyByVector(list[i]);
		list[i] = translate.MultiplyByVector(list[i]);
		//list[i] = rotatie.MultiplyByVector(list[i]);

	}
	
	while (true)
	{
		
		ALLEGRO_COLOR color = ALLEGRO_COLOR();
		color.g = 255;
		//al_draw_line(1.0f, 1.0f, 200.0f, 200.0f, color , 1.0f);
		
		for (int i = 0; i < 8; i ++)
		{
			al_draw_line(160 + list[i].x /list[i].z * 150, 210 + list[i].y / list[i].z * 200, 160 + list[i + 1].x / list[i + 1].z * 150, 210 + list[i + 1].y / list[i + 1].z * 200, color , 1.0f);
		}
		al_flip_display();
	}
	//Matrix translatie = Matrix::Translate();
}