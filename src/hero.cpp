#include "api/graphic.h"

#include "hero.h"
#include "game.h"
#include "screen.h"
#include "cache.h"
#include "grid.h"
#include "animation.h"

Hero::Hero(Game *game) : game(game), horizontal(0), vertical(0), x(0), y(352), forward(true), offset_x(0), offset_y(0)
{
	Image *image = game->getCache()->image(MEDIA_HERO_128X128);
	grid[0] = new Grid(image, 128, 128);

	image = game->getCache()->image(MEDIA_HERO_192X64);
	grid[1] = new Grid(image, 192, 64);

	image = game->getCache()->image(MEDIA_HERO_192X128);
	grid[2] = new Grid(image, 192, 128);

	resting = new Animation(false);
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

	jumpingUp = new Animation(false);
	jumpingUp->add(3, grid[0], 10);
	jumpingUp->add(3, grid[0], 11);
	jumpingUp->add(3, grid[0], 12);
	jumpingUp->add(5, grid[0], 13); // Air
	jumpingUp->add(5, grid[0], 14);

	jumpingDown = new Animation(false);
	jumpingDown->add(3, grid[0], 10);
	jumpingDown->add(3, grid[0], 11);
	jumpingDown->add(3, grid[0], 0);

	downing = new Animation(false);
	downing->add(3, grid[0], 20);
	downing->add(3, grid[0], 21);
	downing->add(3, grid[2], 0);
	downing->add(3, grid[2], 1);

	upping = new Animation(false);
	upping->add(3, grid[2], 1);
	upping->add(3, grid[2], 0);
	upping->add(3, grid[0], 21);
	upping->add(3, grid[0], 20);

	laying = new Animation(false);
	laying->add(1, grid[1], 0);

	crawling = new Animation();
	crawling->add(3, grid[1], 1); // Sniping shot 1
	crawling->add(3, grid[1], 2);
	crawling->add(3, grid[1], 3);
	crawling->add(3, grid[1], 4);
	crawling->add(3, grid[1], 3); // Sniping shot 2
	crawling->add(3, grid[1], 2);

	throwing = new Animation(false);
	throwing->add(1, grid[0], 16);
	throwing->add(1, grid[0], 17);
	throwing->add(1, grid[0], 18);
	throwing->add(5, grid[0], 19); // Throw
	throwing->add(3, grid[0], 17);

	shooting = new Animation();
	shooting->add(3, grid[0], 5);
	shooting->add(3, grid[0], 0);

	shootingUp = new Animation();
	shootingUp->add(3, grid[0], 6);
	shootingUp->add(3, grid[0], 7);

	shootingDown = new Animation();
	shootingDown->add(3, grid[0], 6);
	shootingDown->add(3, grid[0], 7);

	shootingAir = new Animation();
	shootingAir->add(3, grid[0], 14);
	shootingAir->add(3, grid[0], 15);

	sniping = new Animation();
	sniping->add(3, grid[1], 5);
	sniping->add(3, grid[1], 6);

	dying = new Animation(false);
	dying->add( 1, grid[0], 22);
	dying->add( 1, grid[0], 23);
	dying->add( 1, grid[2], 5);
	dying->add( 1, grid[2], 6);
	dying->add( 1, grid[2], 7);
	dying->add(10, grid[2], 8);

	current = resting;
	game->addUpdater(this);
	game->addDrawer(LAYER_HERO, this);
	game->addTyper(this);
}

Hero::~Hero()
{
	delete resting;
	delete walking;
	delete jumpingUp;
	delete jumpingDown;
	delete downing;
	delete upping;
	delete laying;
	delete crawling;
	delete throwing;
	delete shooting;
	delete shootingUp;
	delete shootingDown;
	delete shootingAir;
	delete sniping;
	delete dying;

	delete grid[0];
	delete grid[1];
	delete grid[2];
}

void Hero::update()
{
	if (current == resting || current == walking) // shooting?
	{
		if (vertical > 0)
		{
			current = downing;
			current->flip(!forward);
			current->reset();
		}
		else if (vertical < 0)
		{
			horizontal_jump = horizontal;
			force = HERO_JUMP_FORCE;
			current = jumpingUp;
			current->flip(!forward);
			current->reset();
		}
		else if (horizontal != 0)
		{
			x += horizontal * HERO_WALK_SPEED;
			if (current != walking)
			{
				current = walking;
				current->flip(!forward);
				current->reset();
			}

			if (forward != horizontal > 0)
			{
				forward = horizontal > 0;
				offset_x = forward ? 0 : -32;
				current->flip(!forward);
			}	
		}
		else if (horizontal == 0 && current != resting)
		{
			current = resting;
			current->flip(!forward);
			current->reset();
		}
	}
	else if (current == downing && current->end())
	{
		current = laying;
		current->flip(!forward);
		current->reset();
		offset_y = 64;
	}
	else if (current == laying || current == sniping || current == crawling)
	{
		if (vertical < 0)
		{
			current = upping;
			current->flip(!forward);
			current->reset();
			offset_y = 0;
		}
		else if (horizontal != 0)
		{
			x += horizontal * HERO_CRAWL_SPEED;
			if (current != crawling)
			{
				current = crawling;
				current->flip(!forward);
				current->reset();
			}

			if (forward != horizontal > 0)
			{
				forward = horizontal > 0;
				offset_x = forward ? 0 : -32;
				current->flip(!forward);
			}
		}
		else if (horizontal == 0 && current != laying)
		{
			current = laying;
			current->flip(!forward);
			current->reset();
		}
	}
	else if (current == upping && current->end())
	{
		current = resting;
		current->flip(!forward);
		current->reset();
	}
	else if (current == jumpingUp)
	{
		x += horizontal_jump * HERO_WALK_SPEED;
		y += force;
		force++;
		if (force > 0 && y >= 352)
		{
			y = 352;
			current = jumpingDown;
			current->flip(!forward);
			current->reset();
		}
	}
	else if (current == jumpingDown && current->end())
	{
		current = resting;
		current->flip(!forward);
		current->reset();
	}
}

void Hero::draw()
{
	current->play(x + offset_x, y + offset_y);
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
