#include "Food.h"

void Food::reset() {
    this->pos.x = GetRandomValue(0, 1920);
    this->pos.y = GetRandomValue(0, 1080);

    this->vel.x = GetRandomValue(0, 5);
    this->vel.y = GetRandomValue(0, 5);
}
