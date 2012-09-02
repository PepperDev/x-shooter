#ifndef GRID_H
#define GRID_H

class Image;

class Grid
{
public:
	Grid(Image *image, int split_x = 1, int split_y = 1, bool divide = false);

	void paint(int id, int x, int y, bool flip_x = false, bool flip_y = false);

	int countX();
	int countY();

private:
	Image *image;
	int split_x;
	int split_y;
	bool divide;
	int width;
	int height;
};

#endif
