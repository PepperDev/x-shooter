#ifndef GRID_H
#define GRID_H

#include "image.h"

class Grid
{
public:
	Grid(Image *image, int split_x = 1, int split_y = 1);

	void paint(int id, int x, int y); // TODO: layer

private:
	Image *image;
	int split_x;
	int split_y;
	int width;
	int height;
};

#endif
