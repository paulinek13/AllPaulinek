// ==================================================
// file: PK13_Transition.cpp
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#include "../include/PK13_Transition.h"

bool PK13_Transition::Init()
{
	return false; // it will not run by default
}

void PK13_Transition::Clean()
{
}

void PK13_Transition::OnTimer()
{
}

void PK13_Transition::Draw(PK13_App* app)
{
}

bool PK13_Transition::_Loop(PK13_App* app)
{
	bool result = true;

	if(Init())
	{
		al_start_timer(app->_timer);
		while(!_end)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(app->_event_queue, &event);

			switch(event.type)
			{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
				{
					_end   = true;
					result = false; // should end everything
					break;
				}
				case ALLEGRO_EVENT_TIMER:
				{
					_draw = true;
					OnTimer(); // moves bitmaps, rotates bitmaps, ...
					break;
				}

				default: break;
			}

			if(_draw && al_is_event_queue_empty(app->_event_queue))
			{
				_draw = false;
				al_clear_to_color(al_map_rgb(0, 0, 0));
				Draw(app);
			}
		}
		al_stop_timer(app->_timer);
	}

	Clean();

	return result;
}