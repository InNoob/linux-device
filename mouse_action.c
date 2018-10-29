#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "def.h"



int set_mouse_position(PMOUSE_INFO minfo)
{

	if (!minfo->xevent->xmotion.display )
		return 0;
	XWarpPointer(minfo->xevent->xmotion.display, None, minfo->xevent->xmotion.root, 0, 0, 0, 0, minfo->positionX, minfo->positionY);
	XFlush(minfo->xevent->xmotion.display);

	return 1;
}

int set_mouse_position_slow(PMOUSE_INFO minfo)
{

	RefreshMousePosition(minfo->xevent);
	minfo->positionX -= minfo->xevent->xmotion.x_root;
	minfo->positionY -= minfo->xevent->xmotion.y_root;
	
	set_mouse_move_slow(minfo);

	XFlush(minfo->xevent->xmotion.display);

	return 1;
}

int set_mouse_move(PMOUSE_INFO minfo)
{
	if (!minfo->xevent)
	{
		return 0;
	}
	XWarpPointer(minfo->xevent->xmotion.display, None, None, 0, 0, 0, 0, minfo->positionX, minfo->positionY);
	XFlush(minfo->xevent->xmotion.display);

	return 1;
}

int set_mouse_move_slow(PMOUSE_INFO minfo)
{
	pthread_t ptX;
	pthread_t ptY;

	if (pthread_create(&ptX, NULL, pthread_moveX, (void *)minfo) < 0)
	{
		printf("pthread_moveX create error\n");
		return 0;
	}

	if (pthread_create(&ptY, NULL, pthread_moveY, (void *)minfo) < 0)
	{
		printf("pthread_moveY create error\n");
		return 0;
	}

	void *ret;
	if (pthread_join(ptX, &ret) < 0)
	{
		printf("join pthread_moveX error\n");
		return 0;
	}
	if (pthread_join(ptY, &ret) < 0)
	{
		printf("join pthread_moveY error\n");
		return 0;
	}

	XFlush(minfo->xevent->xmotion.display);

	return 1;
}

void *pthread_moveX(void *pinfo)
{
	int pX = ((PMOUSE_INFO)pinfo)->positionX;
	Display *display = ((PMOUSE_INFO)pinfo)->xevent->xmotion.display;
	unsigned int ts = abs(1000000/(pX==0?1:pX)); 
	if (pX >= 0)
	{
		for (int i = 0; i < pX; i++)
		{
			XWarpPointer(display, None, None, 0, 0, 0, 0, 1, 0);
			usleep(ts);
			XFlush(display);
		}
	}
	else
	{
		for (int i = 0; i > pX; i--)
		{
			XWarpPointer(display, None, None, 0, 0, 0, 0, -1, 0);
			usleep(ts);
			XFlush(display);
		}
	}
}

void *pthread_moveY(void *pinfo)
{
	int pY = ((PMOUSE_INFO)pinfo)->positionY;
	Display *display = ((PMOUSE_INFO)pinfo)->xevent->xmotion.display;
	unsigned int ts = abs(1000000/(pY==0?1:pY));

	if (pY >= 0)
	{
		for (int i = 0; i < pY; i++)
		{
			XWarpPointer(display, None, None, 0, 0, 0, 0, 0, 1);
			usleep(ts);
			XFlush(display);
		}
	}
	else
	{
		for (int i = 0; i > pY; i--)
		{
			XWarpPointer(display, None, None, 0, 0, 0, 0, 0, -1);
			usleep(ts);
			XFlush(display);
		}
	}
}


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