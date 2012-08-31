#ifndef HERO_H
#define HERO_H

#include "game.h"
#include "interfaces.h"

class Hero : Updatable, Drawable, Typeable
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
};

#endif
