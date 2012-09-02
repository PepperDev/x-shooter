#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <map>

class Screen;
class Image;

class Cache
{
public:
	Cache(Screen *screen);
	~Cache();

	Image* image(std::string filename);

	void release();
	void reload();

private:
	Screen *screen;
	std::map<std::string, Image*> images;
};

#endif
