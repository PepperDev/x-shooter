#include "animation.h"
#include "grid.h"

Animation::Animation() : id(0), times(0)
{
}

Animation::~Animation()
{
	for (std::vector<AnimationStep*>::iterator it = steps.begin(); it != steps.end(); it++)
	{
		delete (*it);
	}
	steps.clear();
}


void Animation::add(int frames, Grid *grid, int id, int offset_x, int offset_y)
{
	AnimationStep *step = new AnimationStep();

	step->frames = frames;
	step->grid   = grid;
	step->id     = id;
	step->x      = offset_x;
	step->y      = offset_y;

	steps.push_back(step);
}


void Animation::play(int x, int y)
{
	AnimationStep *step = steps.at(id);

	step->grid->paint(step->id, x + step->x, y + step->y);

	times++;
	if (times > step->frames)
	{
		times = 0;
		id++;
		if (id >= steps.size()) id = 0;
	}
}

void Animation::reset()
{
	id    = 0;
	times = 0;
}
