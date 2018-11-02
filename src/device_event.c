#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "def.h"


int mouse_keydown(PMOUSE_INFO minfo)
{
	XTestFakeButtonEvent(minfo->xevent->xmotion.display,minfo->xevent->xbutton.button,True,0L);
	XFlush(minfo->xevent->xmotion.display);
	return 1;
}

int mouse_keyup(PMOUSE_INFO minfo)
{
	XTestFakeButtonEvent(minfo->xevent->xmotion.display,minfo->xevent->xbutton.button,False,0L);
	XFlush(minfo->xevent->xmotion.display);
	return 1;
}

int mouse_click(PMOUSE_INFO minfo)
{
	mouse_keydown(minfo);
	usleep(100);
	mouse_keyup(minfo);
}

int kbd_press(PKEYBOARD_INFO kinfo)
{
	kbd_down(kinfo);
	kbd_up(kinfo);
}

int kbd_down(PKEYBOARD_INFO kinfo)
{
	XTestFakeKeyEvent(kinfo->xevent->xmotion.display,kinfo->key,True,0L);
	XFlush(kinfo->xevent->xmotion.display);
}

int kbd_up(PKEYBOARD_INFO kinfo)
{
	XTestFakeKeyEvent(kinfo->xevent->xmotion.display,kinfo->key,False,0L);
	XFlush(kinfo->xevent->xmotion.display);
}

int char2key(PKEYBOARD_INFO kinfo)
{
	return XKeysymToKeycode(kinfo->xevent->xmotion.display,*kinfo->keySym);
}