#include <iostream>

#include "game.h"
#include "api/graphic.h"

void game_active_listener(bool active, void *data)
{
	Game *game = (Game*)data;

	game->active = active;

	if (active) game->cache->reload();
	else game->cache->release();
}


Game::Game() : active(true)
{
	screen  = new Screen();
	cache = new Cache(screen);
	// For test only
	Image *image = cache->image("media/images/hero1.png");
	grid = new Grid(image, 5, 4);
	id = 0;

	gui_event_set_active_listener(game_active_listener, this);
	// TODO: set activer listener, set key listener
}

Game::~Game()
{
	delete cache;
	delete screen;
}

int Game::loop()
{
	timer = gui_time();
	while (!gui_event_loop())
	{
		if (active)
		{
			screen->clear();

			// For test only
#define COEFFICIENT 2
#define OFFSET      0
			grid->paint((((id / COEFFICIENT) > 4)?8 - (id / COEFFICIENT):(id / COEFFICIENT)) + OFFSET * 5, 10, 10);
			id++;
			if (id > 8 * COEFFICIENT) id = 0;

			// TODO: update

			screen->update();
		}

		waitFixedFrame();
	}

	return 0;
}

int Game::close()
{
	screen->close();
}


void Game::waitFixedFrame()
{
	unsigned long elapsed_time = gui_time() - timer;

	if (elapsed_time < TIME_PER_FRAME) gui_wait(TIME_PER_FRAME - elapsed_time + 1);
	else if (elapsed_time > TIME_PER_FRAME) std::cerr << "Overlapped time: " << elapsed_time - TIME_PER_FRAME << std::endl;

	timer += TIME_PER_FRAME;
}
