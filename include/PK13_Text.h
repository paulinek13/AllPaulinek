// ==================================================
// file: PK13_Text.h
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#ifndef PK13_TEXT_H
#define PK13_TEXT_H

#include <allegro5/allegro_font.h>

struct PK13_TextInfo
{
	int x1 = 0.f; // most left actual text x position
	int y1 = 0.f; // most up actual text y position
	int x2 = 0.f; // most right actual text x position
	int y2 = 0.f; // most down actual text y position
	int aw = 0.f; // actual text width
	int ah = 0.f; // actual text height
};

// draws string with accurate scale based on given width and height
// returns structure with some information about text after transformation
PK13_TextInfo pk13_draw_string(ALLEGRO_FONT* font, int width, int height, int cx, int cy, ALLEGRO_COLOR color, const char* string);

// draws integer number with accurate scale based on given width and height
// length of buffer has a limit
// returns structure with some information about text after transformation
PK13_TextInfo pk13_draw_integer_number(ALLEGRO_FONT* font, int width, int height, int cx, int cy, ALLEGRO_COLOR color, int number);

// draws floating-point number with accurate scale based on given width and height
// length of buffer has a limit
// precision is set to two digits
// returns structure with some information about text after transformation
PK13_TextInfo pk13_draw_float_number(ALLEGRO_FONT* font, int width, int height, int cx, int cy, ALLEGRO_COLOR color, float number);

#endif // !PK13_TEXT_H