// ==================================================
// file: PK13_Transition.h
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

#ifndef PK13_TRANSITION_H
#define PK13_TRANSITION_H

#include "PK13_App.h"

// responsible for making transition between
// two app states;
// just operates on two bitmaps
// (ex. changes their positions, scale them, etc.);
// the first bitmap is filled with previous app state
// and the second one with destination app state;
struct PK13_Transition
{
	bool _end  = false; // if end transition
	bool _draw = false; // if draw transition content

	// inits some variables
	// returns false if failed
	virtual bool Init();

	// returns false if failed
	virtual void Clean();

	// changes some bitmaps' properties
	// it has to make a condition under which transition should end
	virtual void OnTimer();

	// draws ransition
	// it can use bitmaps with previous and destination state (app pointer)
	virtual void Draw(PK13_App* app);

	// makes transition (calls Init(), Draw() and OnTimer() in loop, Clean() methods)
	// returns false if failed or everything should be closed
	bool _Loop(PK13_App* app);
};

#endif // !PK13_TRANSITION_H