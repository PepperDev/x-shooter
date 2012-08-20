#include <iostream>

#include "game.h"
#include "api/graphic.h"

Game::Game()
{
	screen  = new Screen();
}

Game::~Game()
{
	delete screen;
}

int Game::loop()
{
	timer = gui_time();
	while (!gui_event_loop())
	{
		// TODO: update

		waitFixedFrame();
	}
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
