#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def.h"

int InitXEvent(XEvent *xevent)
{
	XInitThreads();

	if((xevent->xmotion.display= XOpenDisplay(NULL))==NULL)
	{
		printf("opendisplay error");
		return 0;
	}
	
	xevent->xmotion.root= DefaultRootWindow(xevent->xmotion.display);
	Screen* psren = DefaultScreenOfDisplay(xevent->xmotion.display);
	
	xevent->xmotion.x = psren->width;
	xevent->xmotion.y = psren->height;
	

	XAllowEvents(xevent->xmotion.display, AsyncBoth, CurrentTime);


	return xevent->type;
}

PMOUSE_INFO InitPMouseInfo(XEvent *xevent)
{
	PMOUSE_INFO minfo = (PMOUSE_INFO)malloc(sizeof(PMOUSE_INFO));

	if(!minfo)
	{
		printf("minfo malloc error");
		return NULL;
	}

	minfo->positionX = xevent->xmotion.x;
	minfo->positionY = xevent->xmotion.y;
	minfo->xevent = xevent;
	
	return minfo;
}

PKEYBOARD_INFO InitPKeyboardInfo(XEvent *xevent)
{
	PKEYBOARD_INFO kinfo = (PKEYBOARD_INFO)malloc(sizeof(PKEYBOARD_INFO));

	if(!kinfo)
	{
		printf("minfo malloc error");
		return NULL;
	}

	kinfo->xevent = xevent;
	kinfo->key = kinfo->xevent->xbutton.button;
	
	return kinfo;
}

MOUSE_INFO ConstantMouseInfo(void * pinfo)
{
	MOUSE_INFO minfo;
	minfo.fd = ((PMOUSE_INFO)pinfo)->fd;
	minfo.positionX = ((PMOUSE_INFO)pinfo)->positionX;
	minfo.positionY = ((PMOUSE_INFO)pinfo)->positionY;
	minfo.xevent = ((PMOUSE_INFO)pinfo)->xevent;
	
	return minfo;
}

int RefreshMousePosition(XEvent *xevent)
{
	XAllowEvents(xevent->xmotion.display, AsyncBoth, CurrentTime);
	XGrabPointer(xevent->xmotion.display, xevent->xmotion.root, 1,
				 PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
				 GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

	// XEventsQueued(xevent->xmotion.display,100);
	// XNextEvent(xevent->xmotion.display,xevent);
	// XFreeEventData(xevent->xmotion.display,&(xevent->xcookie));
	// XPeekEvent(xevent->xmotion.display,xevent);
	PMOUSE_INFO minfo = InitPMouseInfo(xevent);
	minfo->positionX = 0;
	minfo->positionY = 0;

	set_mouse_move(minfo);
	XPeekEvent(xevent->xmotion.display, xevent);

	XGetEventData(xevent->xmotion.display, &(xevent->xcookie));

	free(minfo);
	minfo=NULL;

	return 1;
}