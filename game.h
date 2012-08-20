#ifndef GAME_H
#define GAME_H

#define FRAMES_PER_SECOND  25
#define TIME_PER_FRAME     (1000 / FRAMES_PER_SECOND)

#include "screen.h"

class Game
{
public:
	Game();
	~Game();

	int loop();
	int close();

private:
	Screen *screen;
	unsigned long timer;

	void waitFixedFrame();
};

#endif

