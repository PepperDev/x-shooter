#include "grid.h"

Grid::Grid(Image *image, int split_x, int split_y) : image(image), split_x(split_x), split_y(split_y)
{
	width = image->getWidth();
	height = image->getHeight();
}

void Grid::paint(int id, int x, int y)
{
	int id_x = id % split_x;
	int id_y = id / split_x;
	int top = width * id_x / split_x;
	int left = height * id_y / split_y;
	int top2 = width * (id_x + 1) / split_x;
	int left2 = height * (id_y + 1) / split_y;
	image->paint(x, y, top, left, top2 - top, left2 - left);
}
