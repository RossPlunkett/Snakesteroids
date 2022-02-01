#include "TailCell.h"

TailCell::TailCell() {}
TailCell::TailCell(double x, double y, int moves) {
	this->moves = moves;
	r = 18;
	pos.x = x;
	pos.y = y;

	pre_moves = 10;
}

int TailCell::default_moves = 30;
int TailCell::increment = 15;
int TailCell::starting_moves = TailCell::default_moves;
