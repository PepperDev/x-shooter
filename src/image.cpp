#include "api/graphic.h"
#include "image.h"
#include "screen.h"

Image::Image(Screen *screen, std::string filename) : screen(screen), filename(filename)
{
	reload();
}

Image::~Image()
{
	release();
}


void Image::paint(int x, int y, int top, int left, int width, int height, bool flip_x, bool flip_y)
{
	if (top < 0) top = this->width + top;
	if (left < 0) left = this->height + left;
	if (width < 0) width = this->width + width + 1;
	if (height < 0) height = this->height + height + 1;

	if (flip_x || flip_y)
	{
		int i = (flip_x ? 1: 0) + (flip_y ? 2 : 0);
		if (!id[i]) id[i] = gui_image_create_flipped(id[0], flip_x, flip_y);
	}

	screen->paint(x, y, this, top, left, width, height, flip_x, flip_y);
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

void Image::release()
{
	for (int i = 3; i--; )
	if (id[i]) {
		gui_image_destroy(id[i]);
		id[i] = 0;
	}
}

void Image::reload()
{
	id[0] = gui_image_load(filename.c_str());
	width = gui_image_width(id[0]);
	height = gui_image_height(id[0]);
}
