#include "image.h"
#include "screen.h"
#include "api/graphic.h"

Image::Image(Screen *screen, std::string filename) : screen(screen), filename(filename), id(-1)
{
	reload();
}

Image::~Image()
{
	release();
}


void Image::paint(int x, int y, int top, int left, int width, int height)
{
	if (top < 0) top = this->width + top;
	if (left < 0) left = this->height + left;
	if (width < 0) width = this->width + width + 1;
	if (height < 0) height = this->height + height + 1;
	screen->paint(x, y, this, top, left, width, height);
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
	if (id == -1) return;
	gui_image_destroy(id);
	id = -1;
}

void Image::reload()
{
	if (id != -1) return;
	id = gui_image_load(filename.c_str());
	width = gui_image_width(id);
	height = gui_image_height(id);
}
