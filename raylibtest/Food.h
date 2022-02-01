#ifndef FOOD_H
#define FOOD_H

#include "Raylib.h"


class Food
{
	int r = 30;
	Vector2 pos;
	Vector2 vel;
	Color color = GREEN;
	void reset();
};

#endif

