#include "animation.h"
#include "grid.h"

Animation::Animation(bool repeat) : repeat(repeat), id(0), times(0), flip_x(false), flip_y(false)
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
	paint(x, y);

	if (!repeat && end()) return;

	times++;
	if (times >= steps.at(id)->frames)
	{
		times = 0;
		id++;
		if (id >= steps.size()) id = 0;
	}
}

void Animation::paint(int x, int y)
{
	AnimationStep *step = steps.at(id);

	int id = step->id;

	int offset_x = step->x;
	int offset_y = step->y;

	if (flip_x || flip_y)
	{
		int count_x = step->grid->countX();
		int count_y = step->grid->countY();
		int id_x = id % count_x;
		int id_y = id / count_x;

		if (flip_x)
		{
			id_x = count_x - id_x - 1;
			offset_x *= -1;
		}
		if (flip_y)
		{
			id_y = count_y - id_y - 1;
			offset_y *= -1;
		}

		id = id_y * count_x + id_x;
	}

	step->grid->paint(id, x + offset_x, y + offset_y, flip_x, flip_y);
}

void Animation::reset()
{
	id    = 0;
	times = 0;
}


int Animation::position()
{
	return id;
}

int Animation::size()
{
	return steps.size();
}

bool Animation::end()
{
	return id >= steps.size() - 1 && times >= steps.front()->frames - 1;
}


void Animation::flip(bool horizontal, bool vertical)
{
	flip_x = horizontal;
	flip_y = vertical;
}
