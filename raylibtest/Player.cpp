#include "Player.h"




Player::Player() {
    moved_this_frame = false;
    move_speed = 16.0f;
    base_r = 40;
    r = base_r;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
}

void Player::update(double dt) {

    // movement

    moved_this_frame = false;

    if (IsKeyDown(KEY_RIGHT)) { pos.x += move_speed; moved_this_frame = true; }
    if (IsKeyDown(KEY_LEFT)) { pos.x -= move_speed; moved_this_frame = true; }
    if (IsKeyDown(KEY_UP)) { pos.y -= move_speed; moved_this_frame = true; }
    if (IsKeyDown(KEY_DOWN)) { pos.y += move_speed; moved_this_frame = true; }

    // wrap around screen
    if (pos.y > screenHeight) { pos.y = 0; }
    else if (pos.y < 0) { pos.y = screenHeight; }
    if (pos.x > screenWidth) { pos.x = 0; }
    else if (pos.x < 0) { pos.x = screenWidth; }


    // tail creation

    if (moved_this_frame)
    {
        Tail.push_back(TailCell(pos.x, pos.y, TailCell::starting_moves));

        for (int i = 0; i < Tail.size(); i++) {
            if (Tail[i].pre_moves > 0) {
                Tail[i].pre_moves--;
            }
            else {
                Tail[i].moves--;
                if (Tail[i].moves <= 0) {
                    Tail.erase(Tail.begin() + i);
                    i--;
                }
            }
        }
    }



}


bool Player::hitting_tail() {
    int rando = GetRandomValue(0, 2);
    for (int f = rando; f < Tail.size(); f+=3) {
        if (CheckCollisionCircles(pos, r, Tail[f].pos, Tail[f].r)
            && Tail[f].pre_moves <= 0) {
            return true;
        }
    }
    return false;
}

