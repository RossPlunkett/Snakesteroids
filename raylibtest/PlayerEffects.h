#ifndef PLYR_H
#define PLYR_H

#include "raylib.h"
#include "Player.h"

class PlayerEffects
{
public:
	void update(double dt);
	Player* p;
	PlayerEffects(Player* player);

	// growing stuff
	void grow(double dt);
	bool growing;
	double grow_timer;
	double grow_time;
	int grow_size;
};

#endif

