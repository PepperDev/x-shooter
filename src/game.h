#ifndef GAME_H
#define GAME_H

#define FRAMES_PER_SECOND  25
#define TIME_PER_FRAME     (1000 / FRAMES_PER_SECOND)

#include <set>
#include "screen.h"
#include "cache.h"
#include "interfaces.h"

void game_active_listener(bool active, void *data);
void game_key_down_listener(int key, void *data);
void game_key_up_listener(int key, void *data);

class Game
{
public:
	Game();
	~Game();

	int loop();
	int close();

	const Cache* getCache();
	const Screen* getScreen();

	void addUpdater(Updatable *updater);
	void addDrawer(int layer, Drawable *drawer);
	void addTyper(Typeable *typer);

private:
	Screen *screen;
	Cache *cache;
	unsigned long timer;
	bool active;
	std::set<Updatable*> updaters;
	std::set<Typeable*> typers;

	void waitFixedFrame();

friend void ::game_active_listener(bool active, void *data);
friend void ::game_key_down_listener(int key, void *data);
friend void ::game_key_up_listener(int key, void *data);
};

#endif

