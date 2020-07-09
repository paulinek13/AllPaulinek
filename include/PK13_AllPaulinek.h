// ==================================================
// file: PK13_AllPaulinek.h
// project: AllPaulinek
// author: Paulina Kalicka
// ==================================================

/////////////////////////////////////////////////////
/*
   This is the main header file of the
   AllPaulinek library.
*/
/////////////////////////////////////////////////////

#ifndef PK13_ALLPAULINEK_H
#define PK13_ALLPAULINEK_H

/////////////////////////////////////////////////////
// < USEFUL MACROS

#define PK13_INIT_ALLEGRO \
	if(!al_init()) return -1
#define PK13_INIT_ACODEC_ADDON \
	if(!al_init_acodec_addon()) return -1
#define PK13_INIT_FONT_ADDON \
	if(!al_init_font_addon()) return -1
#define PK13_INIT_IMAGE_ADDON \
	if(!al_init_image_addon()) return -1
#define PK13_INIT_NATIVE_DIALOG_ADDON \
	if(!al_init_native_dialog_addon()) return -1
#define PK13_INIT_PRIMITIVES_ADDON \
	if(!al_init_primitives_addon()) return -1
#define PK13_INIT_TTF_ADDON \
	if(!al_init_ttf_addon()) return -1
#define PK13_INIT_VIDEO_ADDON \
	if(!al_init_video_addon()) return -1

#define PK13_INSTALL_AUDIO \
	if(!al_install_audio()) return -1
#define PK13_INSTALL_JOYSTICK \
	if(!al_install_joystick()) return -1
#define PK13_INSTALL_KEYBOARD \
	if(!al_install_keyboard()) return -1
#define PK13_INSTALL_MOUSE \
	if(!al_install_mouse()) return -1
#define PK13_INSTALL_TOUCH_INPUT \
	if(!al_install_touch_input()) return -1

// > USEFUL MACROS
/////////////////////////////////////////////////////

#include "PK13_App.h"
#include "PK13_AppState.h"

#include <allegro5/allegro.h>

#endif // !PK13_ALLPAULINEK_H