#ifndef GAME_H
#define GAME_H

#define FRAMES_PER_SECOND  25
#define TIME_PER_FRAME     (1000 / FRAMES_PER_SECOND)

#include "screen.h"
#include "cache.h"
#include "grid.h" // Test only

void game_active_listener(bool active, void *data);

class Game
{
public:
	Game();
	~Game();

	int loop();
	int close();

private:
	Screen *screen;
	Cache *cache;
	unsigned long timer;
	bool active;
	int id; // Teste only
	Grid *grid; // Teste only

	void waitFixedFrame();

friend void game_active_listener(bool active, void *data);
};

#endif

