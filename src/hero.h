#ifndef HERO_H
#define HERO_H

#include "interfaces.h"

class Game;
class Image;
class Grid;

class Hero : public Updatable, public Drawable, public Typeable
{
public:
	Hero(Game *game);
	~Hero();

	void update();
	void draw();
	void keyDown(int key);
	void keyUp(int key);

private:
	Game *game;
	Image *image;
	Grid *grid;
	char horizontal;
	char vertical;
	int x;
	int y;
};

#endif
