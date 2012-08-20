#include "graphic.h"
#include <SDL/SDL.h>

void gfx_init(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) throw "Couldn't init video.";

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (screen == NULL) throw "Couldn't create a video surface.";

	SDL_WM_SetCaption(title, NULL);
	SDL_ShowCursor(SDL_DISABLE);
}

void gfx_quit()
{
	SDL_Quit();
}


bool gfx_event_loop()
{
	SDL_Event event;
	bool quit = false;

	while (SDL_PollEvent (&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		// TODO: case key
		}
	}

	return quit;
}
