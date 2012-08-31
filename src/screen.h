#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_TITLE  "X-Shooter"

#define LAYER_BACKGROUND 0
#define LAYER_FOREGROUND 1
#define LAYER_ENTITIES   2
#define LAYER_ENEMIES    3
#define LAYER_HERO       3
#define LAYER_SHOTS      4
#define LAYER_INVENTARY  4
#define LAYER_GUI        5
#define LAYER_MAX        6

#include <set>
#include "interfaces.h"

class Image;

class Screen
{
public:
	Screen();

	void draw();
	void close();

	void addDrawer(int layer, Drawable *drawer);

	void paint(int x, int y, Image *image, int top, int left, int width, int height);
private:
	int id;
	std::set<Drawable*> drawers[LAYER_MAX];
};

#endif
