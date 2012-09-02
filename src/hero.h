#ifndef HERO_H
#define HERO_H

#include "interfaces.h"

#define HERO_SPEED 5

#define MEDIA_HERO_128X128 "media/images/hero_128x128.png"
#define MEDIA_HERO_192X128 "media/images/hero_192x128.png"
#define MEDIA_HERO_192X64  "media/images/hero_192x64.png"

class Game;
class Grid;
class Animation;

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
	Game      *game;
	Grid      *grid[3];
	Animation *current;
	Animation *resting;
	Animation *walking;
	Animation *jumping;
	Animation *downing;
	Animation *upping;
	Animation *crawling;
	Animation *throwing;
	Animation *shooting;
	Animation *shootingUp;
	Animation *shootingDown;
	Animation *sniping;
	Animation *dying;
	bool      front;
	char      horizontal;
	char      vertical;
	int       x;
	int       y;
	int       offset_x;
};

#endif
