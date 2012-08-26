#include "cache.h"

Cache::Cache(Screen *screen) : screen(screen)
{
}

Cache::~Cache()
{
	for (std::map<std::string, Image*>::iterator it = images.begin(); it != images.end(); it++)
	{
		delete it->second;
	}
	images.clear();
}


Image* Cache::image(std::string filename)
{
	if (images.count(filename) > 0) return images.find(filename)->second;

	Image *image = new Image(screen, filename);
	images.insert(std::make_pair(filename, image));
	return image;
}


void Cache::release()
{
	for (std::map<std::string, Image*>::iterator it = images.begin(); it != images.end(); it++)
	{
		it->second->release();
	}
}

void Cache::reload()
{
	for (std::map<std::string, Image*>::iterator it = images.begin(); it != images.end(); it++)
	{
		it->second->reload();
	}
}
