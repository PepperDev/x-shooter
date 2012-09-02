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
	Animation();
	~Animation();

	void add(int frames, Grid *grid, int id, int offset_x = 0, int offset_y = 0); // TODO: collisor

	void play(int x, int y);
	void reset();

private:
	int id;
	int times;
	std::vector<AnimationStep*> steps;
};

#endif
