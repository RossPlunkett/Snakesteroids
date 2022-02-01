/*******************************************************************************************
*
*   Snakesteroids!
*
*   Uses the C library Raylib
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Snakesteroids game by Ross Plunkett
*
********************************************************************************************/


int screenWidth = 1920;
int screenHeight = 1080;

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include "Asteroid.h"
#include "Player.h"
#include "PlayerEffects.h"

using std::cout;
using std::vector;
using std::endl;


void randomize_asteroids(vector<Asteroid>& asteroids, Vector2 playerPos) {
    for (int i = 0; i < asteroids.size(); i++) {

        asteroids[i].pos.x = GetRandomValue(0.0f, screenWidth);
        asteroids[i].pos.y = GetRandomValue(0.0f, screenHeight);

        if ((abs(asteroids[i].pos.x - playerPos.x) < 300
            && (abs(asteroids[i].pos.y - playerPos.y) < 300))) {
            i--;
            continue;
        }

        asteroids[i].vel.x = GetRandomValue(0.0f, 22.0f) / 5;
        asteroids[i].vel.y = GetRandomValue(0.0f, 22.0f) / 5;


        asteroids[i].color = BLUE;
        asteroids[i].isFood = false;
    }
    int food_num = GetRandomValue(0.0f, asteroids.size() - 1);
    asteroids[food_num].color = GREEN;
    asteroids[food_num].isFood = true;

}

void reset_roid(Asteroid& asteroid) {
    asteroid.pos.x = GetRandomValue(0.0f, screenWidth);
    asteroid.pos.y = GetRandomValue(0.0f, screenHeight);

    asteroid.vel.x = GetRandomValue(0.0f, 22.0f) / 5;
    asteroid.vel.y = GetRandomValue(0.0f, 22.0f) / 5;
}

void reset_game(vector<Asteroid>& asteroids, Player& player) {
    player.pos.x = (screenWidth / 2);
    player.pos.y = (screenHeight / 2);
    player.Tail.clear();
    TailCell::starting_moves = TailCell::default_moves;
    randomize_asteroids(asteroids, player.pos);
}




int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Texture2D pic = LoadTexture("noteball.png");

    Player Player1;
    Player1.pos = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Player* p1;
    p1 = &Player1;
    PlayerEffects PE1(p1);


    vector<Asteroid> balls;
    int number_of_balls = 20;
    for (int i = 0; i < number_of_balls; i++) {
        Asteroid ast(0, 0, 0, 0, 30);
        balls.push_back(ast);
    }

    bool reversed = false;
    double reverse_time = 0.5f;
    double reverse_timer = 0.0f;


    randomize_asteroids(balls, Player1.pos);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


        if (IsKeyPressed(KEY_SPACE)) currentShader++;

        if (currentShader >= MAX_POSTPRO_SHADERS) currentShader = 0;
        else if (currentShader < 0) currentShader = MAX_POSTPRO_SHADERS - 1;

        double dt = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------

        Player1.update(dt);
        if (Player1.hitting_tail()) { reset_game(balls, Player1); }

        PE1.update(dt);

        //update asteroids
        for (int i = 0; i < balls.size(); i++) {
            // asteroid move
            double x_vel = balls[i].vel.x; double y_vel = balls[i].vel.y;
            if (reversed) { x_vel = -x_vel; y_vel = -y_vel; }
            balls[i].pos.x += x_vel * Asteroid::speed; balls[i].pos.y += y_vel * Asteroid::speed;
            // asteroid wrap
            if (balls[i].pos.y > screenHeight) { balls[i].pos.y = 0; }
            else if (balls[i].pos.y < 0) { balls[i].pos.y = screenHeight; }
            if (balls[i].pos.x > screenWidth) { balls[i].pos.x = 0; }
            else if (balls[i].pos.x < 0) { balls[i].pos.x = screenWidth; }

            // bounce timer
            if (balls[i].bounced) {
                balls[i].bounce_timer -= dt;
                if (balls[i].bounce_timer <= 0) {
                    balls[i].bounced = false;
                }
            }

            // check for asteroid collision with player
            if (CheckCollisionCircles(balls[i].pos, balls[i].r, Player1.pos, Player1.r)) {
                if (!balls[i].isFood) {
                    if (PE1.growing) {
                        if (!balls[i].bounced) {
                            balls[i].bounced = true;
                            balls[i].bounce_timer = balls[i].bounce_time;
                            balls[i].vel.x *= -1.5f;
                            balls[i].vel.y *= -1.5f;
                        }
                        else {
                            // nothing
                        }
                    }
                    else {
                        reset_game(balls, Player1);
                        break;
                    }
                }
                else { // if it's food
                    reset_roid(balls[i]); // reset food location
                    TailCell::starting_moves += TailCell::increment;
                    for (int q = 0; q < Player1.Tail.size(); q++) {
                        Player1.Tail[q].moves += TailCell::increment; // add frames to existing tail segments
                    }
                }
            }

        }




        // if (IsKeyDown(KEY_SPACE)) {
         //    if (!reversed) {
         //        reversed = true;
           //      reverse_timer = reverse_time;
         //    }
        // }

        if (IsKeyDown(KEY_SPACE)) {
            PE1.grow(dt);
        }
        if (reversed) {
            reverse_timer -= dt;
            cout << "timer: " << reverse_timer << endl;

            if (reverse_timer <= 0) {
                reversed = false;
                //reverse_roids(balls);
            }
        }



        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        //DrawText("Constellations discovered:", 10, 30, 20, RAYWHITE);
        //DrawText("Constellations discovered:", 10, 60, 20, RAYWHITE);

        int  t_tailsize = Player1.Tail.size();
        for (int i = 0; i < t_tailsize; i++) {
            DrawCircle(Player1.Tail[i].pos.x, Player1.Tail[i].pos.y, Player1.Tail[i].r, Player1.Tail[i].color);
        }

        DrawCircleV(Player1.pos, Player1.r, GREEN);

        int t_asteroids = balls.size();
        for (int i = 0; i < t_asteroids; i++) {
            DrawCircle(balls[i].pos.x, balls[i].pos.y, balls[i].r, balls[i].color);
            //DrawTexture(pic, balls[i].pos.x, balls[i].pos.y, RAYWHITE);
        }
        DrawFPS(10, 90);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

/**

buffs:

- slow balls -- slow music
- fast snake -- fast music
- invincibility against asteroids -- solo

nerfs:
- direction shift - all asteroids switch direction - music goes backwards?
- big head - music wavers in pitch

abilities -
shock wave with cooldown
time-reverse with cooldown

powerup implementation





*/
