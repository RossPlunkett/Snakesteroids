#ifndef TAIL_H
#define TAIL_H

#include "raylib.h"

class TailCell
{
public:
	int r;
	int pre_moves;
	double moves;
	Color color = GREEN;
	Vector2 pos;
	TailCell();
	TailCell(double x, double y, int moves);
	static int starting_moves;
	static int default_moves;
	static int increment;
};

#endif

