// ==================================================
// file: PK13_App.h
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#ifndef PK13_APP_H
#define PK13_APP_H

#include "PK13_Camera.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// respresents instance of an app and
// holds information that is shared
// between all appp states;
// should be one per application;
// every derived struct/class has to have:
// Init() method which calls PK13_App::Init(...) and
// Clean() method which calls PK13_App::Clean();
struct PK13_App
{
	ALLEGRO_DISPLAY*     _display     = 0; // the main window
	ALLEGRO_TIMER*       _timer       = 0; // indicates speed for drawing and updating logic
	ALLEGRO_EVENT_QUEUE* _event_queue = 0; // for all events
	ALLEGRO_FONT*        _font        = 0; // the default font
	ALLEGRO_BITMAP*      _icon        = 0; // the display icon
	ALLEGRO_BITMAP*      _prev_state  = 0; // bitmap with a previous state on it (used mainly for transitions)
	ALLEGRO_BITMAP*      _dest_state  = 0; // bitmap with a destination state on it (used mainly for transitions)

	PK13_Camera _camera; // the main camera

	int _w  = 800; // width of the app content (it should be set once and should not change during execution)
	int _h  = 600; // height of the app content (it should be set once and should not change during execution)
	int _hw = 400; // half of the width
	int _hh = 300; // half of the height

	// creates the app base and initializes important fields
	// call it only once at the beginning and remember to call Clean()
	// returns false if failed
	bool _Init(int app_width, int app_height,
	           const char* app_name, const char* font_path, const char* icon_path,
	           double timer_speed, int display_flags);

	// destroys everything that was created in Init() method
	// call it only once at the end (if Init() was called)
	// returns false if failed
	void _Clean();
};

#endif // !PK13_APP_H