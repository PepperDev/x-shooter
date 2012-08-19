#include "game.h"
#include "screen.h"

#include <SDL/SDL.h>

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) throw "Couldn't init video.";

	SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (screen == NULL) throw "Couldn't create a video surface.";

	SDL_WM_SetCaption(SCREEN_TITLE, NULL);
	SDL_ShowCursor(SDL_DISABLE);
}

Game::~Game()
{
	
}

int Game::loop()
{
	SDL_Event event;
	bool quit = false;

	for (;;)
	{
		while (SDL_PollEvent (&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		if (quit) break;
	}
}

int Game::close()
{
	SDL_Quit();
}
