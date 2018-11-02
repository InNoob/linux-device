#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "def.h"

int main(int argc,char** argv)
{
	int positionX = 0;
	int positionY = 0;
	unsigned int button = 0;
	unsigned char* func;

	switch(argc)
	{
		case 2 : {
			func = argv[1];
			break;
		}
		case 3 : {
			func = argv[1];
			button = atoi(argv[2]);
			XEvent xevent;
			InitXEvent(&xevent);

			PMOUSE_INFO minfo = InitPMouseInfo(&xevent);
			minfo->xevent->xbutton.button = button;

			PKEYBOARD_INFO kinfo = InitPKeyboardInfo(&xevent);
			kinfo->key = button;
			// kinfo->keySym = *argv[2];
			kinfo->keySym = "tab";

			if(!strcmp(func,"mouseKeyDown")){
				mouse_keydown(minfo);
			}else if(!strcmp(func,"mouseKeyUp")){
				mouse_keyup(minfo);
			}else if(!strcmp(func,"mouseClick")){
				mouse_click(minfo);
			}else if(!strcmp(func,"keyDown")){
				kbd_down(kinfo);
			}else if(!strcmp(func,"keyPress")){
				kbd_press(kinfo);
			}else if(!strcmp(func,"keyUp")){
				kbd_up(kinfo);
			}else if(!strcmp(func,"c2key")){
				printf("keycode: %d\n",char2key(kinfo));
			}

			free(minfo);
			minfo=NULL;
			free(kinfo);
			kinfo=NULL;
			XCloseDisplay(xevent.xmotion.display);
			break;
		}
		case 4 : {
			func = argv[1];
			positionX = atoi(argv[2]);
			positionY = atoi(argv[3]);

			XEvent xevent;
			InitXEvent(&xevent);
			PMOUSE_INFO minfo = InitPMouseInfo(&xevent);
			minfo->positionX = positionX;
			minfo->positionY = positionY;

			if(!strcmp(func,"setMouseMove")){
				set_mouse_move(minfo);
			}else if(!strcmp(func,"setMousePosition")){
				set_mouse_position(minfo);
			}else if(!strcmp(func,"setMouseMoveSlow")){
				set_mouse_move_slow(minfo);
			}else if(!strcmp(func,"setMousePositionSlow")){
				set_mouse_position_slow(minfo);
			}

			free(minfo);
			minfo=NULL;
			XCloseDisplay(xevent.xmotion.display);
			break;
		}
		default : {
			exit(0);
		}
	}

	while(--argc>0)
	{
		printf("argv->%s \n",argv[argc] );
	}

	printf("func: %s, button: %d, pX: %d, pY: %d\n",func,button,positionX,positionY);

	return 1;
	
}
