

//extern int screenWidth;
//extern int screenHeight;

#ifndef PLYREFF_H
#define PLYREFF_H



#include "raylib.h"
#include <vector>
#include "TailCell.h"

class Player
{
public:
	Vector2 pos;
	//PlayerEffects Effects(Player* p);
	double move_speed;
	int base_r;
	int r;
	void update(double dt);
	Player();
	std::vector<TailCell> Tail;
	bool moved_this_frame;
	bool hitting_tail();



private:
	int screenWidth;
	int screenHeight;
};

#endif

