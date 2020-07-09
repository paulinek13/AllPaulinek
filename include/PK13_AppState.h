// ==================================================
// file: PK13_AppState.h
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#ifndef PK13_APP_STATE_H
#define PK13_APP_STATE_H

#include "PK13_App.h"
#include "PK13_Transition.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <memory>

#define PK13_EXIT_STATE (-1)

// represents single app state
// (ex.menu, settings, playing scene, etc.);
// by default handles basic events like
// closing display, resizing display and
// transforms camera and mouse positions when needed;
// indicates when to draw app state content
// and update logic based on timer speed;
struct PK13_AppState
{
	bool _end     = false; // if end app state
	bool _draw    = false; // if draw app state content
	bool _pressed = false; // if at least one key is pressed
	bool _clicked = false; // if at least one mouse button is clicked

	float _mx     = 0.f; // mouse position x (depends on camera x position)
	float _my     = 0.f; // mouse position y (depends on camera y position)
	float _mx_gui = 0.f; // mouse GUI position x (camera independent)
	float _my_gui = 0.f; // mouse GUI position y (camera independent)

	int _next_state = PK13_EXIT_STATE; // which state goes after this one (it should be changed in state loop)

	std::unique_ptr<PK13_Transition> _transition = 0; // unique pointer to a transition struct

	ALLEGRO_TRANSFORM _trans_resize = {0}; // transformation after resizing display
	ALLEGRO_TRANSFORM _trans_camera = {0}; // transformation after camera change

	// inits some variables
	// for example it can make a uniue pointer for a transition
	// returns false if failed
	virtual bool Init();

	// cleans everything that was allocated in Init()
	// returns false if failed
	virtual void Clean();

	// draws app state content
	virtual void Draw();

	// handles app state events and app logic
	virtual void Events(ALLEGRO_EVENT event);

	// loops through the state loop
	// at first it calls Init() and loops through transition loop
	// then it calls Draw() and Events() methods in loop
	// at the end it calls Clean() method
	// returns next app state
	int _Loop(PK13_App* app);

	// ends the current state and starts the next state
	void _EndTheState(int next_state);

	// call it before drawing GUI content (only if camera can be changed in app state otherwise there is no need)
	void _StartDrawingGUI();

	// call it after drawing GUI (only if StartDrawingGUI() was called before)
	void _StopDrawingGUI();

  private:
	// resizes display properly and makes app content responsive to that changes
	void _TransformDisplay(PK13_App* app);

	// transforms mouse coordinates
	void _TransformMouse(ALLEGRO_EVENT& event);

	// transforms mouse coordinates based on mouse state
	void _TransformMouse();
};

#endif // !PK13_APP_STATE_H