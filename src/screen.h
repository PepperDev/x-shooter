#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_TITLE  "X-Shooter"

class Image;

class Screen
{
public:
	Screen();

	void clear();
	void update();
	void close();

	void paint(int x, int y, Image *image, int top, int left, int width, int height);
private:
	int id;
};

#endif
