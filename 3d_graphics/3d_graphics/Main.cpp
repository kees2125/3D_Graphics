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

	int polygonindexespiramide[6][3] = { { 0,1,2 },{ 4,5,6 },{ 0,1,5 },{ 1,2,6 },{ 2,3,7 },{ 3,0,4 } };

	vector pa = vector(-1, -1, 1);
	vector pb = vector(1, -1, 1);
	vector pc = vector(-1, -1, -1);
	vector pd = vector(1, -1, -1);
	vector pe = vector(0, 1, 0);

	Matrix perspect = Matrix::Perspective(90, (6 / 8.0f), 0.1, 20);
	Matrix translate = Matrix::Translate(vector(4, 0, 8));
	//Matrix rotatie = Matrix::Rotate(vector(1,0,0), ALLEGRO_PI / 5);

	Shape square = Shape(Shape::SHAPE_SQUARE);
	
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
			//al_draw_line(1.0f, 1.0f, 200.0f, 200.0f, color , 1.0f);
			
			for (int i = 0; i < 8; i++)
			{
				Matrix rotatie = Matrix::Rotate(vector(0, 1, 0), (ALLEGRO_PI / 16) * angle);
				shape.vectors[i] = rotatie.MultiplyByVector(shape.vectors[i]);
				shape.vectors[i] = perspect.MultiplyByVector(shape.vectors[i]);
				shape.vectors[i] = translate.MultiplyByVector(shape.vectors[i]);
			}

			for (int i = 0; i < 6; i++)
			{
				for (int p = 0; p < 3; p++)
				{
					al_draw_line(160 + shape.vectors[shape.polygonindexes[i][p]].x / shape.vectors[shape.polygonindexes[i][p]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][p]].y / shape.vectors[shape.polygonindexes[i][p]].z * 200, 160 + shape.vectors[shape.polygonindexes[i][p + 1]].x / shape.vectors[shape.polygonindexes[i][p + 1]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][p + 1]].y / shape.vectors[shape.polygonindexes[i][p + 1]].z * 200, color, 1.0f);
				}
				al_draw_line(160 + shape.vectors[shape.polygonindexes[i][3]].x / shape.vectors[shape.polygonindexes[i][3]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][3]].y / shape.vectors[shape.polygonindexes[i][3]].z * 200, 160 + shape.vectors[shape.polygonindexes[i][0]].x / shape.vectors[shape.polygonindexes[i][0]].z * 150, 210 + shape.vectors[shape.polygonindexes[i][0]].y / shape.vectors[shape.polygonindexes[i][0]].z * 200, color, 1.0f);
			}
			//al_draw_line(shape.vectorsTemp[0].x, shape.vectorsTemp[0].y, shape.vectorsTemp[7].x, shape.vectorsTemp[7].y, a, 1.0f);
			al_flip_display();
			t = al_get_time();
			angle++;
		}
	}
	//Matrix translatie = Matrix::Translate();
}