#include "grid.h"
#include "image.h"

Grid::Grid(Image *image, int split_x, int split_y, bool divide) : image(image), split_x(split_x), split_y(split_y), divide(divide)
{
	width  = image->getWidth();
	height = image->getHeight();
}

void Grid::paint(int id, int x, int y)
{
	int divisor = divide ? split_x : (this->width + split_x - 1) / split_x;
	int id_x    = id % divisor;
	int id_y    = id / divisor;
	int top     = divide ? this->width  * id_x / split_x : id_x * split_x;
	int left    = divide ? this->height * id_y / split_y : id_y * split_y;
	int width   = divide ? this->width  * (id_x + 1) / split_x - left : (left + split_x > this->width ) ? this->width  - left: split_x;
	int height  = divide ? this->height * (id_y + 1) / split_y - top  : (top  + split_y > this->height) ? this->height - top : split_y;
	image->paint(x, y, top, left, width, height);
}
