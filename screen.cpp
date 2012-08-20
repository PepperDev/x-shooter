#include <iostream>

#include "screen.h"
#include "api/graphic.h"

Screen::Screen()
{
	gui_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
}


void Screen::close()
{
	gui_quit();
}
