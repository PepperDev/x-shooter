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

void game_key_down_listener(int key, void *data)
{
	Game *game = (Game*)data;

	for (std::set<Typeable*>::iterator it = game->typers.begin(); it != game->typers.end(); it++)
	{
		(*it)->keyDown(key);
	}
}

void game_key_up_listener(int key, void *data)
{
	Game *game = (Game*)data;

	for (std::set<Typeable*>::iterator it = game->typers.begin(); it != game->typers.end(); it++)
	{
		(*it)->keyUp(key);
	}
}


Game::Game() : active(true)
{
	screen = new Screen();
	cache = new Cache(screen);

	gui_event_set_active_listener(game_active_listener, this);
	gui_event_set_key_listener(game_key_down_listener, game_key_up_listener, this);
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
			//screen->clear();

			for (std::set<Updatable*>::iterator it = updaters.begin(); it != updaters.end(); it++)
			{
				(*it)->update();
			}

			//screen->update();
			screen->draw();
		}

		waitFixedFrame();
	}

	return 0;
}

int Game::close()
{
	screen->close();
}


const Cache* Game::getCache()
{
	return cache;
}

const Screen* Game::getScreen()
{
	return screen;
}


void Game::addUpdater(Updatable *updater)
{
	updaters.insert(updater);
}

void Game::addDrawer(int layer, Drawable *drawer)
{
	screen->addDrawer(layer, drawer);
}

void Game::addTyper(Typeable *typer)
{
	typers.insert(typer);
}


void Game::waitFixedFrame()
{
	unsigned long elapsed_time = gui_time() - timer;

	if (elapsed_time < TIME_PER_FRAME) gui_wait(TIME_PER_FRAME - elapsed_time + 1);
	else if (elapsed_time > TIME_PER_FRAME) std::cerr << "Overlapped time: " << elapsed_time - TIME_PER_FRAME << std::endl;

	timer += TIME_PER_FRAME;
}
