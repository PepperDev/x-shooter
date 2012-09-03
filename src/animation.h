#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

class Grid;

typedef struct
{
	int  frames;
	Grid *grid;
	int  id;
	int  x;
	int  y;
} AnimationStep;

class Animation
{
public:
	Animation(bool repeat = true);
	~Animation();

	void add(int frames, Grid *grid, int id, int offset_x = 0, int offset_y = 0); // TODO: collisor

	void play(int x, int y);
	void paint(int x, int y);
	void reset();

	int  position();
	int  size();
	bool end();

	void flip(bool horizontal = false, bool vertical = false);

private:
	int id;
	int times;
	bool repeat;
	bool flip_x;
	bool flip_y;
	std::vector<AnimationStep*> steps;
};

#endif
