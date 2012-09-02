#include "api/graphic.h"

#include "hero.h"
#include "game.h"
#include "screen.h"
#include "cache.h"
#include "grid.h"

Hero::Hero(Game *game) : game(game), horizontal(0), vertical(0)
{
	image = game->getCache()->image("media/images/hero_128x128.png");
	grid = new Grid(image, 128, 128);
	game->addUpdater(this);
	game->addDrawer(LAYER_HERO, this);
	game->addTyper(this);
}

Hero::~Hero()
{
	delete grid;
}

void Hero::update()
{
	x += horizontal;
	y += vertical;
}

void Hero::draw()
{
	grid->paint(0, x, y);
}

void Hero::keyDown(int key)
{
	switch (key)
	{
		case KEY_LEFT:  horizontal--; break;
		case KEY_RIGHT: horizontal++; break;
		case KEY_UP:    vertical--; break;
		case KEY_DOWN:  vertical++; break;
	}
}

void Hero::keyUp(int key)
{
	switch (key)
	{
		case KEY_LEFT:  horizontal++; break;
		case KEY_RIGHT: horizontal--; break;
		case KEY_UP:    vertical++; break;
		case KEY_DOWN:  vertical--; break;
	}
}
