#include "Asteroid.h"




Asteroid::Asteroid(double x, double y, double vx, double vy, double r) {
    pos.x = x; pos.y = y; vel.x = vx; vel.y = vy; this->r = r; // args must have different names
    isFood = false;
    bounced = false;
    bounce_time = 0.75f;
}

double Asteroid::speed = 1.0f;

