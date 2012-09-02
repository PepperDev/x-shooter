#include "api/graphic.h"

#include "hero.h"
#include "game.h"
#include "screen.h"
#include "cache.h"
#include "grid.h"
#include "animation.h"

Hero::Hero(Game *game) : game(game), horizontal(0), vertical(0), x(0), y(0), front(true), offset_x(0)
{
	Image *image = game->getCache()->image(MEDIA_HERO_128X128);
	grid[0] = new Grid(image, 128, 128);

	image = game->getCache()->image(MEDIA_HERO_192X128);
	grid[1] = new Grid(image, 192, 128);

	image = game->getCache()->image(MEDIA_HERO_192X64);
	grid[2] = new Grid(image, 192, 64);

	resting = new Animation();
	resting->add(1, grid[0], 0);

	walking = new Animation();
	walking->add(3, grid[0], 2);
	walking->add(3, grid[0], 1);
	walking->add(3, grid[0], 2);
	walking->add(3, grid[0], 0);
	walking->add(3, grid[0], 4);
	walking->add(3, grid[0], 3);
	walking->add(3, grid[0], 4);
	walking->add(3, grid[0], 0);

	current = resting;
	game->addUpdater(this);
	game->addDrawer(LAYER_HERO, this);
	game->addTyper(this);
}

Hero::~Hero()
{
	delete resting;
	delete walking;
	/*
	delete jumping;
	delete downing;
	delete upping;
	delete crawling;
	delete throwing;
	delete shooting;
	delete shootingUp;
	delete shootingDown;
	delete sniping;
	delete dying;
	*/

	delete grid[0];
	delete grid[1];
	delete grid[2];
}

void Hero::update()
{
	x += horizontal * HERO_SPEED;
	y += vertical;

	if (horizontal == 0 && current != resting)
	{
		current = resting;
		current->flip(!front);
		current->reset();
	}
	else if (horizontal != 0 && current != walking)
	{
		front = horizontal > 0;
		offset_x = front ? 0 : -32;

		current = walking;
		current->flip(!front);
		current->reset();
	}
}

void Hero::draw()
{
	current->play(x + offset_x, y);
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
