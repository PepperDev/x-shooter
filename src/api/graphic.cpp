#include "graphic.h"
#include <map>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

static std::map<int, SDL_Surface*> surfaces;
static int surfaces_last = 0;
static void (*active_listener)(bool, void*) = NULL;
static void *active_listener_data = NULL;
static key_listener key_down_listener = NULL, key_up_listener = NULL;
static void *key_listener_data = NULL;


int gui_init(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cerr << "Couldn't init video." << std::endl;
		exit(-1);
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (screen == NULL)
	{
		std::cerr << "Couldn't create a video surface." << std::endl;
		exit(-1);
	}

	SDL_WM_SetCaption(title, NULL);
	SDL_ShowCursor(SDL_DISABLE);

	surfaces.insert(std::make_pair(surfaces_last, screen));
	return surfaces_last++;
}

void gui_quit()
{
	SDL_Quit();
}


void gui_clear(int id)
{
	SDL_Surface *surface = surfaces.find(id)->second;
	SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0, 0, 0));
}

void gui_update(int id)
{
	SDL_Flip(surfaces.find(id)->second);
}


static int gui_event_key_translate(SDLKey key) {
	switch (key)
	{
		case SDLK_UP: return KEY_UP;
		case SDLK_DOWN: return KEY_DOWN;
		case SDLK_RIGHT: return KEY_RIGHT;
		case SDLK_LEFT: return KEY_LEFT;
		case SDLK_SPACE: return KEY_SPACE;
		case SDLK_RCTRL: case SDLK_LCTRL: return KEY_CONTROL;
		case SDLK_RSHIFT: case SDLK_LSHIFT: return KEY_SHIFT;
		case SDLK_ESCAPE: return KEY_ESCAPE;
		default: return 0;
	}
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
		case SDL_ACTIVEEVENT:
			if (active_listener && event.active.state & SDL_APPACTIVE == SDL_APPACTIVE) active_listener(event.active.gain != 0, active_listener_data);
			break;
		case SDL_KEYDOWN:
			if (key_down_listener) key_down_listener(gui_event_key_translate(event.key.keysym.sym), active_listener_data);
			break;
		case SDL_KEYUP:
			if (key_up_listener) key_up_listener(gui_event_key_translate(event.key.keysym.sym), active_listener_data);
			break;
		}
	}

	return quit;
}

void gui_event_set_key_listener(key_listener key_down, key_listener key_up, void *data)
{
	key_down_listener = key_down;
	key_up_listener = key_up;
	key_listener_data = data;
}

void gui_event_set_active_listener(void (*activate)(bool, void*), void *data)
{
	active_listener = activate;
	active_listener_data = data;
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

	if (image == NULL)
	{
		std::cerr << "Image \"" << filename << "\" not found." << std::endl;
		exit(-1);
	}

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

int gui_image_create_flipped(int image_id, bool flip_x, bool flip_y)
{
	SDL_Surface *image   = surfaces.find(image_id)->second;
	SDL_Surface *flipped = NULL;

	flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, (image->flags & SDL_SRCCOLORKEY == SDL_SRCCOLORKEY) ? 0 : image->format->Amask);

	if (SDL_MUSTLOCK(image)) SDL_LockSurface(image);

	for (int x = image->w; x--; )
	{
		for (int y = image->h; y--; )
		{
			((Uint32*) flipped->pixels)[(flip_y ? image->h - y - 1 : y ) * image->w + (flip_x ? image->w - x -1 : x)] = ((Uint32*) image->pixels)[y * image->w + x];
		}
	}

	if (SDL_MUSTLOCK(image)) SDL_UnlockSurface(image);

	if (image->flags & SDL_SRCCOLORKEY == SDL_SRCCOLORKEY) SDL_SetColorKey(flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, image->format->colorkey);

	surfaces.insert(std::make_pair(surfaces_last, flipped));
	return surfaces_last++;
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
