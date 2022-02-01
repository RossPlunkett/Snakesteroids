#include "PlayerEffects.h"
#include <iostream>
#include "raymath.h"

PlayerEffects::PlayerEffects(Player* player) {
    p = player;
    growing = false;
    grow_time = 5.0f;
    grow_timer = grow_time;
    grow_size = 80;
}

void PlayerEffects::grow(double dt) {
    if (!growing) {
        growing = true;
        grow_timer = grow_time;
    }
}

void PlayerEffects::update(double dt) {

    if (growing) {

        double stage_1 = 0.925;
        double stage_2 = 0.075;
        double stage_timer;
        grow_timer -= dt;

        if (grow_timer >= (grow_time * stage_1)) {
             stage_timer = (grow_timer / grow_time);
             stage_timer = 1.0f - ( 1.0f * (stage_timer - stage_1) / (1.0f - stage_1) );
             // y = y0 + (y1 - y0) * (x - x0) / (x1 - x0) // scale formula
             p->r = lround(p->base_r + (stage_timer * (grow_size - p->base_r) ) );
        }
        else if ((grow_timer < (grow_time * stage_1)) && (grow_timer > (grow_time * stage_2))) {
            p->r = grow_size;
        }
        else if (grow_timer <= (grow_time * stage_2)) {
            stage_timer = (grow_timer / grow_time) * (1.0f / stage_2);
            p->r = lround(p->base_r + (stage_timer * (grow_size - p->base_r)));
        }

        if (grow_timer <= 0) {
            p->r = p->base_r;
            growing = false;
        }
    }

    // perhaps if there is a collision while grown/growing,
    // the balls are reversed in direction and increased in speed


}

