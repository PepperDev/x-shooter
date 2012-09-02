#include <iostream>

#include "api/graphic.h"

#include "interfaces.h"

#include "screen.h"
#include "image.h"

Screen::Screen()
{
	id = gui_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
}


void Screen::draw()
{
	gui_clear(id);

	for (int layer = 0; layer < LAYER_MAX; layer++)
	{
		for (std::set<Drawable*>::iterator it = drawers[layer].begin(); it != drawers[layer].end(); it++)
		{
			(*it)->draw();
		}
	}

	gui_update(id);
}

void Screen::close()
{
	gui_quit();
}


void Screen::addDrawer(int layer, Drawable *drawer)
{
	drawers[layer].insert(drawer);
}


void Screen::paint(int x, int y, Image *image, int top, int left, int width, int height, bool flip_x, bool flip_y)
{
	gui_image_paint(image->id[(flip_x ? 1: 0) + (flip_y ? 2 : 0)], x, y, id, top, left, width, height);
}
