#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/raylib.h"
#include "../include/utils.h"

int WINHEIGHT = 900;
int WINWIDTH = 1600;

int main()
{
    //initializing game window
    Game_Window = 3;
    //3 for pong

    //initializing elements
    //player1

    struct Slider_pong player1;
    player1.rect.x = 100;
    player1.rect.y = 450;
    player1.rect.width = 15;
    player1.rect.height = 175;
    player1.rotation = 0.0f;
    player1.lives = 5;

    //player2
    struct Slider_pong player2;
    player2.rect.x = 1485;
    player2.rect.y = 450;
    player2.rect.width = 15;
    player2.rect.height = 175;
    player2.rotation = 0.0f;
    player2.lives = 5;

    //Death walls
    Rectangle red1 = {0, 0, 5, 900};
    Rectangle red2 = {1595, 0, 5, 900};

    //Safe wallss
    Rectangle blue1 = {0, 0, 1600, 5};
    Rectangle blue2 = {0, 895, 1600, 5};

    //ball
    struct Ball_pong ball;
    ball.radius = 10;
    ball.pos.x = 800;
    ball.pos.y = 450;
    ball.velocity.x = 5;
    ball.velocity.y = 0;
    ball.acceleration.x = 0;
    ball.acceleration.y = 0.0;
    ball.active = 1;

    //generating all the bricks
    struct Bricks_pong bricks[60];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bricks[3 * i + j].rect.x = 5 + 20 * j;
            bricks[3 * i + j].rect.y = 6 + i * 90;
            bricks[3 * i + j].rect.height = 80;
            bricks[3 * i + j].rect.width = 18;
            bricks[3 * i + j].is_active = 1;
            bricks[3 * i + j].health = 3;

            bricks[60 - (3 * i + j) - 1].rect.x = 1575 - 20 * j;
            bricks[60 - (3 * i + j) - 1].rect.y = 6 + i * 90;
            bricks[60 - (3 * i + j) - 1].rect.height = 80;
            bricks[60 - (3 * i + j) - 1].rect.width = 18;
            bricks[60 - (3 * i + j) - 1].is_active = 1;
            bricks[60 - (3 * i + j) - 1].health = 3;
        }
    }

    InitWindow(WINWIDTH, WINHEIGHT, "PongVer3");
    SetTargetFPS(240);
    //mainloop which updates every
    while (!WindowShouldClose())
    {
        switch (Game_Window)
        {
        case 3:
            Draw_Pong(&player1, &player2, red1, red2, blue1, blue2, &ball, bricks);
            break;

        default:
            break;
        }
    }
    return 0;
}