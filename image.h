#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "screen.h"

class Image
{
public:
	Image(Screen &screen, std::string filename);
	~Image();

	void paint(int x = 0, int y = 0, int top = 0, int left = 0, int width = -1, int height = -1); // TODO: layer
	int getWidth();
	int getHeight();
	void release();
	void reload();
private:
	Screen &screen;
	std::string filename;
	int image_id; // friendly Screen
	int width;
	int height;
};

#endif
