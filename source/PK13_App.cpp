// ==================================================
// file: PK13_App.cpp
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#include "../include/PK13_App.h"

#include <limits>

bool PK13_App::_Init(int app_width, int app_height,
                     const char* app_name, const char* font_path, const char* icon_path,
                     double timer_speed, int display_flags)
{
	// these fields should not change from now on
	_w  = app_width;
	_h  = app_height;
	_hw = app_width >> 1;
	_hh = app_height >> 1;

	al_set_app_name(app_name);
	al_set_new_window_title(app_name);

	al_set_new_display_flags(display_flags);

	_display = al_create_display(app_width, app_height);
	if(!_display) return false;

	// center and resize display, based on screen size
	ALLEGRO_MONITOR_INFO info;
	if(al_get_monitor_info(0, &info))
	{
		al_resize_display(_display, info.x2, info.y2);
		al_set_window_position(_display, 0, 0);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();
	}
	else
		return false;

	_timer = al_create_timer(timer_speed);

	_event_queue = al_create_event_queue();
	if(_event_queue)
	{
		// register default event sources that should not be unregistered later
		al_register_event_source(_event_queue, al_get_timer_event_source(_timer));
		al_register_event_source(_event_queue, al_get_display_event_source(_display));
	}

	if(font_path)
		_font = al_load_font(font_path, 32, 0);
	else
		_font = al_create_builtin_font();
	if(icon_path)
	{
		al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
		_icon = al_load_bitmap(icon_path);
		al_set_new_bitmap_flags(0);
		if(_icon)
			al_set_display_icon(_display, _icon);
	}

	_prev_state = al_create_bitmap(app_width, app_height);
	_dest_state = al_create_bitmap(app_width, app_height);

	return (_display && _event_queue && _timer && _font); // icon is not needed
}

void PK13_App::_Clean()
{
	al_destroy_display(_display);
	al_destroy_event_queue(_event_queue);
	al_destroy_timer(_timer);
	al_destroy_font(_font);
	al_destroy_bitmap(_icon);
	al_destroy_bitmap(_prev_state);
	al_destroy_bitmap(_dest_state);
}