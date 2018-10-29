#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "def.h"

int main(void)
{
	XEvent xevent;
	InitXEvent(&xevent);


	printf("Mouse move : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
	
	PMOUSE_INFO minfo = InitPMouseInfo(&xevent);
	if (!minfo) {
		printf("init error\n");
		return 0;
	}
	minfo->positionX = 200;
	minfo->positionY = 200;
	

	set_mouse_position(minfo);
	
	// xevent.xbutton.button = MOUSE_BTN_LEFT;
	// xevent.xbutton.state = MOUSE_BTN_LEFT;
	// xevent.xbutton.time = 0L;
	
	sleep(1);
	
	minfo->xevent->xbutton.button = MOUSE_BTN_LEFT;
	mouse_keydown(minfo);

	minfo->positionX = 0;
	minfo->positionY = 200;
	set_mouse_move(minfo);
	mouse_keyup(minfo);

	minfo->positionX = -180;
	minfo->positionY = -320;
	sleep(1);
	set_mouse_move(minfo);
	mouse_click(minfo);
	sleep(1);
	mouse_click(minfo);
	minfo->positionX = 180;
	minfo->positionY = 320;
	set_mouse_move(minfo);


	printf("Mouse move : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);

	// minfo->positionX = 900;
	// minfo->positionY = 500;

	// if(!set_mouse_position(minfo)){
	// 	printf("set mouse position error");
	// }


	// get_mouse_position(&xevent);
	// printf("Mouse move : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);

	// minfo->positionX = -857;
	// minfo->positionY = -472;
	// sleep(1);
	// set_mouse_move_slow(minfo);


	// get_mouse_position(&xevent);
	// printf("Mouse move : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
	

	free(minfo);
	minfo=NULL;

	return 1;
	
}
