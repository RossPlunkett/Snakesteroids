#ifndef AST_H
#define AST_H

#include "raylib.h"


class Asteroid
{

public:
    Vector2 pos;
    Vector2 vel;
    bool isFood = false;    
    double r;
    Asteroid(double x, double y, double vx, double vy, double r);
    Color color = BLUE;
    static double speed;

    double bounced;
    double bounce_timer;
    double bounce_time;
};

#endif
