#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\color.h>
#include <math.h>
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
	Matrix translate = Matrix::Translate(vector(1, 1, 1));
	Matrix rotatie = Matrix::Rotate(vector(1, 1, 1), ALLEGRO_PI / 2);
	
	int temp = 1;
	while (true)
	{
		
		temp++;
		if (temp > 10)
		{
			temp = 1;
		}
		vector listTemp[8];
		for (int i = 0; i < 8;i++)
		{
			listTemp[i] = perspect.MultiplyByVector(list[i]);
			listTemp[i] = translate.MultiplyByVector(list[i]);
			listTemp[i] = rotatie.MultiplyByVector(list[i]);
			
		}
		ALLEGRO_COLOR at = ALLEGRO_COLOR();
		at.g = 255;
		//al_draw_line(1.0f, 1.0f, 200.0f, 200.0f, a , 1.0f);
		for (int i = 0; i < 8; i += 2)
		{
			al_draw_line( listTemp[i].x/listTemp[i].z +400 * 400, listTemp[i].y/listTemp[i].z+300 *300, listTemp[i++].x / listTemp[i++].z + 400 * 400, listTemp[i++].y / listTemp[i++].z + 300 * 300,at,1.0f);
		}
		//al_draw_line(listTemp[0].x, listTemp[0].y, listTemp[7].x, listTemp[7].y, a, 1.0f);
		al_flip_display();
	}
	//Matrix translatie = Matrix::Translate();
}