#include <hero.h>

Hero::Hero(Game *game) : game(game)
{
	image = game->getCache()->image("media/images/hero_192x192.png");
	grid = new Grid(image, 192. 192);
}

Hero::~Hero()
{
	delete grid;
	delete image;
}

void Hero::update()
{
}

void Hero::draw()
{
}

void Hero::keyDown()
{
}

void Hero::keyUp()
{
}
