#include "graphic.h"
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

static std::map<int, SDL_Surface*> surfaces;
static int surfaces_last = 0;

int gui_init(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) throw "Couldn't init video.";

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (screen == NULL) throw "Couldn't create a video surface.";

	SDL_WM_SetCaption(title, NULL);
	SDL_ShowCursor(SDL_DISABLE);

	surfaces.insert(std::make_pair(surfaces_last, screen));
	return surfaces_last++;
}

void gui_quit()
{
	SDL_Quit();
}


bool gui_event_loop()
{
	SDL_Event event;
	bool quit = false;

	while (SDL_PollEvent(&event))
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


unsigned long gui_time()
{
	return SDL_GetTicks();
}

void gui_wait(unsigned long time)
{
	SDL_Delay(time);
}


int gui_image_load(const char *filename)
{
	SDL_Surface *image = NULL, *otimized = NULL;

	image = IMG_Load(filename);

	if (image == NULL) throw "Image not found.";

	otimized = SDL_DisplayFormat(image);

	if (otimized != NULL)
	{
		SDL_FreeSurface(image);
		image = otimized;
	}

	surfaces.insert(std::make_pair(surfaces_last, image));
	return surfaces_last++;
}

int gui_image_width(int image_id)
{
	return surfaces.find(image_id)->second->w;
}

int gui_image_height(int image_id)
{
	return surfaces.find(image_id)->second->h;
}

void gui_image_destroy(int image_id)
{
	SDL_FreeSurface(surfaces.find(image_id)->second);
}

void gui_image_paint(int source, int x, int y, int target, int left, int top, int width, int height)
{
	SDL_Rect clip;
	clip.x = left;
	clip.y = top;
	clip.w = width;
	clip.h = height;
	SDL_Rect position;
	position.x = x;
	position.y = y;
	SDL_BlitSurface(surfaces.find(source)->second, &clip, surfaces.find(target)->second, &position);
}
