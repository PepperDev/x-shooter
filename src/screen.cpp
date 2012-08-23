#include <iostream>

#include "screen.h"
#include "image.h"
#include "api/graphic.h"

Screen::Screen()
{
	id = gui_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
}


void Screen::clear()
{
	gui_clear(id);
}

void Screen::update()
{
	gui_update(id);
}

void Screen::close()
{
	gui_quit();
}


void Screen::paint(int x, int y, Image *image, int top, int left, int width, int height)
{
	gui_image_paint(image->id, x, y, id, top, left, width, height);
}
