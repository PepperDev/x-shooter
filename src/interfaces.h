#ifndef INTERFACES_H
#define INTERFACES_H

class Typeable
{
public:
	virtual void keyDown (int key) = 0;
	virtual void keyUp (int key) = 0;
};

class Updatable
{
public:
	virtual void update() = 0;
};

class Drawable
{
public:
	virtual void draw() = 0;
};

#endif
