// ==================================================
// file: PK13_AppState.cpp
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#include "../include/PK13_AppState.h"

#include "../include/PK13_Camera.h"

#define FILL_DEST_STATE                     \
	al_set_target_bitmap(app->_dest_state); \
	Draw();                                 \
	al_set_target_backbuffer(app->_display);
#define FILL_PREV_STATE                     \
	al_set_target_bitmap(app->_prev_state); \
	Draw();                                 \
	al_set_target_backbuffer(app->_display);

bool PK13_AppState::Init()
{
	return false; // app state will not run by default
}

void PK13_AppState::Clean()
{
}

void PK13_AppState::Draw()
{
}

void PK13_AppState::Events(ALLEGRO_EVENT event)
{
}

int PK13_AppState::_Loop(PK13_App* app)
{
	if(app && Init())
	{
		_TransformDisplay(app);
		_TransformMouse();

		if(!(app->_dest_state))
			app->_dest_state = al_create_bitmap(app->_w, app->_h);
		FILL_DEST_STATE;

		app->_camera.Reset(app->_w, app->_h);

		if(_transition)
		{
			std::unique_ptr<PK13_Transition> transition(std::move(_transition));
			if(!transition->_Loop(app))
				_end = true; // the transition failed or display has been closed
		}

		// since transition is finished there is no need for these bitmaps
		if(app->_dest_state)
		{
			al_destroy_bitmap(app->_dest_state);
			app->_dest_state = 0;
		}
		if(app->_prev_state)
		{
			al_destroy_bitmap(app->_prev_state);
			app->_prev_state = 0;
		}

		/////////////////////////////////////////////////////
		// < STATE LOOP

		al_start_timer(app->_timer);
		while(!_end)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(app->_event_queue, &event);
			switch(event.type)
			{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
				{
					_end = true;
					break;
				}
				case ALLEGRO_EVENT_DISPLAY_RESIZE:
				{
					al_acknowledge_resize(app->_display);
					_TransformDisplay(app);
					app->_camera.update = true;
					break;
				}
				case ALLEGRO_EVENT_TIMER:
				{
					_draw = true;
					if(app->_camera.update)
					{
						app->_camera.update = false;

						al_identity_transform(&_trans_camera);

						al_translate_transform(&_trans_camera, -app->_camera.cx, -app->_camera.cy);
						al_scale_transform(&_trans_camera, app->_camera.scale, app->_camera.scale);
						al_translate_transform(&_trans_camera, app->_camera.cx, app->_camera.cy);

						al_translate_transform(&_trans_camera, -app->_camera.cx + app->_hw, -app->_camera.cy + app->_hh);
						al_compose_transform(&_trans_camera, &_trans_resize);
						al_use_transform(&_trans_camera);
					}
					break;
				}
				case ALLEGRO_EVENT_MOUSE_AXES:
				{
					_TransformMouse(event);
					break;
				}
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				{
					_clicked = true;
					break;
				}
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				{
					_clicked = false;
					break;
				}
				case ALLEGRO_EVENT_KEY_DOWN:
				{
					_pressed = true;
					break;
				}
				case ALLEGRO_EVENT_KEY_UP:
				{
					_pressed = false;
					break;
				}

				default: break;
			}

			Events(event); // input and logic

			if(_draw && al_is_event_queue_empty(app->_event_queue))
			{
				_draw = false;
				Draw();
			}
		}
		al_stop_timer(app->_timer);
		al_flush_event_queue(app->_event_queue);

		// > STATE LOOP
		/////////////////////////////////////////////////////

		if(!(app->_prev_state))
			app->_prev_state = al_create_bitmap(app->_w, app->_h);
		FILL_PREV_STATE;
	}
	else
		_next_state = PK13_EXIT_STATE;

	Clean();

	return _next_state;
}

void PK13_AppState::_EndTheState(int next_state)
{
	_end        = true;
	_next_state = next_state;
}

void PK13_AppState::_StartDrawingGUI()
{
	al_use_transform(&_trans_resize);
}

void PK13_AppState::_StopDrawingGUI()
{
	al_use_transform(&_trans_camera);
}

void PK13_AppState::_TransformDisplay(PK13_App* app)
{
	float scaleX = al_get_display_width(app->_display) / (app->_hw * 2.f);
	float scaleY = al_get_display_height(app->_display) / (app->_hh * 2.f);
	float scale  = scaleX < scaleY ? scaleX : scaleY;

	al_identity_transform(&_trans_resize);
	al_scale_transform(&_trans_resize, scale, scale);
	if(scale == scaleX)
	{
		float y = ((al_get_display_height(app->_display) >> 1)) - ((app->_hh * scale));
		al_translate_transform(&_trans_resize, 0, y);
	}
	else if(scale == scaleY)
	{
		float x = ((al_get_display_width(app->_display) >> 1)) - ((app->_hw * scale));
		al_translate_transform(&_trans_resize, x, 0);
	}
	al_use_transform(&_trans_resize);
}
void PK13_AppState::_TransformMouse(ALLEGRO_EVENT& event)
{
	_mx = _mx_gui = event.mouse.x;
	_my = _my_gui = event.mouse.y;

	ALLEGRO_TRANSFORM t = {0};

	al_copy_transform(&t, al_get_current_transform());
	al_invert_transform(&t);
	al_transform_coordinates(&t, &_mx, &_my);

	al_copy_transform(&t, &_trans_resize);
	al_invert_transform(&t);
	al_transform_coordinates(&t, &_mx_gui, &_my_gui);
}
void PK13_AppState::_TransformMouse()
{
	ALLEGRO_MOUSE_STATE mouse_state;
	al_get_mouse_state(&mouse_state);

	_mx = _mx_gui = mouse_state.x;
	_my = _my_gui = mouse_state.y;

	ALLEGRO_TRANSFORM t = {0};

	al_copy_transform(&t, al_get_current_transform());
	al_invert_transform(&t);
	al_transform_coordinates(&t, &_mx, &_my);

	al_copy_transform(&t, &_trans_resize);
	al_invert_transform(&t);
	al_transform_coordinates(&t, &_mx_gui, &_my_gui);
}