#include "game.h"
#include "screen.h"
#include "api/graphic.h"

Game::Game()
{
	gfx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
}

Game::~Game()
{
	
}

int Game::loop()
{
	while (!gfx_event_loop())
	{
		// TODO: update
	}
}

int Game::close()
{
	gfx_quit();
}
