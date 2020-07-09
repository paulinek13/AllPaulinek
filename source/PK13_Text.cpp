// ==================================================
// file: PK13_Text.cpp
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#include "../include/PK13_Text.h"

#include <stdio.h>

#define PK13_MAX_BUFF_SIZE 64

PK13_TextInfo pk13_draw_string(ALLEGRO_FONT* font, int width, int height, int cx, int cy, ALLEGRO_COLOR color, const char* string)
{
	int font_h = al_get_font_line_height(font);
	int text_w = al_get_text_width(font, string);

	float scalex = width / float(text_w);
	float scaley = height / float(font_h);
	float scale  = scalex < scaley ? scalex : scaley;

	ALLEGRO_TRANSFORM prev_t;
	al_copy_transform(&prev_t, al_get_current_transform());

	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_translate_transform(&t, -cx, -cy);
	al_scale_transform(&t, scale, scale);
	al_translate_transform(&t, cx, cy);
	al_compose_transform(&t, &prev_t);
	al_use_transform(&t);

	al_draw_textf(font, color, cx, cy - (font_h >> 1),
	              ALLEGRO_ALIGN_CENTRE, "%s", string);

	al_use_transform(&prev_t);

	int ahw = (text_w * scale) / 2;
	int ahh = (font_h * scale) / 2;

	return PK13_TextInfo({cx - ahw, cy - ahh, cx + ahw, cy + ahh, ahw << 1, ahh << 1});
}

PK13_TextInfo pk13_draw_integer_number(ALLEGRO_FONT* font, int width, int height, int cx, int cy, ALLEGRO_COLOR color, int number)
{
	char buffer[PK13_MAX_BUFF_SIZE];
	sprintf_s(buffer, PK13_MAX_BUFF_SIZE, "%i", number);

	int font_h = al_get_font_line_height(font);
	int text_w = al_get_text_width(font, buffer);

	float scalex = width / text_w;
	float scaley = height / font_h;
	float scale  = scalex < scaley ? scalex : scaley;

	ALLEGRO_TRANSFORM prev_t;
	al_copy_transform(&prev_t, al_get_current_transform());

	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_translate_transform(&t, -cx, -cy);
	al_scale_transform(&t, scale, scale);
	al_translate_transform(&t, cx, cy);
	al_compose_transform(&t, &prev_t);
	al_use_transform(&t);

	al_draw_textf(font, color, cx, cy - (font_h >> 1),
	              ALLEGRO_ALIGN_CENTRE, "%s", buffer);

	al_use_transform(&prev_t);

	int ahw = (text_w * scale) / 2;
	int ahh = (font_h * scale) / 2;

	return PK13_TextInfo({cx - ahw, cy - ahh, cx + ahw, cy + ahh, ahw << 1, ahh << 1});
}

PK13_TextInfo pk13_draw_float_number(ALLEGRO_FONT* font, int width, int height, int cx, int cy, ALLEGRO_COLOR color, float number)
{
	char buffer[PK13_MAX_BUFF_SIZE];
	sprintf_s(buffer, PK13_MAX_BUFF_SIZE, "%.2f", number);

	int font_h = al_get_font_line_height(font);
	int text_w = al_get_text_width(font, buffer);

	float scalex = width / text_w;
	float scaley = height / font_h;
	float scale  = scalex < scaley ? scalex : scaley;

	ALLEGRO_TRANSFORM prev_t;
	al_copy_transform(&prev_t, al_get_current_transform());

	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_translate_transform(&t, -cx, -cy);
	al_scale_transform(&t, scale, scale);
	al_translate_transform(&t, cx, cy);
	al_compose_transform(&t, &prev_t);
	al_use_transform(&t);

	al_draw_textf(font, color, cx, cy - (font_h >> 1),
	              ALLEGRO_ALIGN_CENTRE, "%s", buffer);

	int ahw = (text_w * scale) / 2;
	int ahh = (font_h * scale) / 2;

	return PK13_TextInfo({cx - ahw, cy - ahh, cx + ahw, cy + ahh, ahw << 1, ahh << 1});
}