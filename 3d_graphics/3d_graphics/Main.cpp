#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\color.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"
#include "shape.h"

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

	Matrix perspect = Matrix::Perspective(90, (6 / 8.0f), 0.1, 20);
	Matrix translate = Matrix::Translate(vector(4, 0, 8));

	Shape square = Shape(Shape::SHAPE_PIRAMIDE);
	
	double t = al_get_time();
	int angle = 0;
	while (true)
	{
		if (al_get_time() - t > 0.1)
		{
			Shape shape = square;
			ALLEGRO_COLOR color = ALLEGRO_COLOR();
			al_clear_to_color(color);
			color.g = 255;
			
			for (int i = 0; i < 8; i++)
			{
				Matrix rotatie = Matrix::Rotate(vector(0, 1, 0), (ALLEGRO_PI / 16) * angle);
				Matrix rotatie2 = Matrix::Rotate(vector(1, 0, 0), (ALLEGRO_PI));
				shape.vectors[i] = rotatie.MultiplyByVector(shape.vectors[i]);
				shape.vectors[i] = rotatie2.MultiplyByVector(shape.vectors[i]);
				shape.vectors[i] = perspect.MultiplyByVector(shape.vectors[i]);
				shape.vectors[i] = translate.MultiplyByVector(shape.vectors[i]);
			}

			for (int i = 0; i < 6; i++)
			{
				for (int p = 0; p < shape.polygonsize-1; p++)
				{
					al_draw_line(160 + shape.vectors[shape.polygonindexes[i][p]].x / shape.vectors[shape.polygonindexes[i][p]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][p]].y / shape.vectors[shape.polygonindexes[i][p]].z * 200, 160 + shape.vectors[shape.polygonindexes[i][p + 1]].x / shape.vectors[shape.polygonindexes[i][p + 1]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][p + 1]].y / shape.vectors[shape.polygonindexes[i][p + 1]].z * 200, color, 1.0f);
				}
				al_draw_line(160 + shape.vectors[shape.polygonindexes[i][shape.polygonsize-1]].x / shape.vectors[shape.polygonindexes[i][shape.polygonsize-1]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][shape.polygonsize-1]].y / shape.vectors[shape.polygonindexes[i][shape.polygonsize-1]].z * 200, 160 + shape.vectors[shape.polygonindexes[i][0]].x / shape.vectors[shape.polygonindexes[i][0]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][0]].y / shape.vectors[shape.polygonindexes[i][0]].z * 200, color, 1.0f);
			}
			al_flip_display();
			t = al_get_time();
			angle++;
		}
	}
}