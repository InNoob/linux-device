#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#ifndef __DEF_H__
#define __DEF_H__

#define MOUSE_BTN_LEFT 1
#define MOUSE_BTN_RIGHT 3
#define MOUSE_BTN_MIDDLE 2

typedef struct _MOUSE_INFO
{
	int* fd;
	XEvent *xevent;
	int positionX;
	int positionY;
} MOUSE_INFO, *PMOUSE_INFO;

typedef struct _KEYBOARD_INFO
{
	int* fd;
	XEvent *xevent;
	unsigned int key;
	char* keySym;
} KEYBOARD_INFO, *PKEYBOARD_INFO;

int InitXEvent(XEvent *);

PMOUSE_INFO InitPMouseInfo(XEvent *);

PKEYBOARD_INFO InitPKeyboardInfo(XEvent *);

PMOUSE_INFO ConvertMouseInfo(void*);

int RefreshMousePosition(XEvent *);

int set_mouse_move(PMOUSE_INFO);
int set_mouse_move_slow(PMOUSE_INFO);

int set_mouse_position(PMOUSE_INFO);
int set_mouse_position_slow(PMOUSE_INFO);

void* pthread_moveX(void*);
void* pthread_moveY(void*); 

int mouse_keydown(PMOUSE_INFO);
int mouse_keyup(PMOUSE_INFO);
int mouse_click(PMOUSE_INFO);

int kbd_press(PKEYBOARD_INFO);
int kbd_down(PKEYBOARD_INFO);
int kbd_up(PKEYBOARD_INFO);
int char2key(PKEYBOARD_INFO);

#endif