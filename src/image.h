#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Screen;

class Image
{
public:
	Image(Screen *screen, std::string filename);
	~Image();

	void paint(int x = 0, int y = 0, int top = 0, int left = 0, int width = -1, int height = -1, bool flip_x = false, bool flip_y = false);
	int getWidth();
	int getHeight();
	void release();
	void reload();
private:
	Screen *screen;
	std::string filename;
	int id[4];
	int width;
	int height;

friend class Screen;
};

#endif
