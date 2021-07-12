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
    Game_Window = 2;
    //3 for pong
    InitWindow(WINWIDTH, WINHEIGHT, "MadKauSing");

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

    //initializing for tictactoe

    Image X = LoadImage("resources/X logo.png");
    ImageResize(&X, (float)X.width / 5, (float)X.height / 5);
    Image O = LoadImage("resources/O logo.png");
    ImageResize(&O, (float)O.width / 5, (float)O.height / 5);
    Image grid = LoadImage("resources/grid logo.png");

    Texture2D Cross = LoadTextureFromImage(X);
    Texture2D Nought = LoadTextureFromImage(O);
    Texture2D grid_texture = LoadTextureFromImage(grid);
    Texture2D blank = LoadTexture("resources/blank.jpg");

    Vector2 mousePoint = {0.0f, 0.0f};

    //declare and initialize button struct.
    struct Button b[9];
    for (int i = 0; i < 9; i++)
    {
        b[i].btn_state = 0;
        b[i].btn_action = 0;
        b[i].btn_color = BLUE;
        b[i].img = blank;
    }
    int k = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            b[k].btn_bounds.x = 610 + (grid.width / 3) * i;
            b[k].btn_bounds.y = 270 + (grid.height / 3) * j;
            b[k].btn_bounds.width = 140;
            b[k].btn_bounds.height = 100;
            k++;
        }
    }

    struct game g;
    g.mode = 0;
    g.winner = 0;
    g.round = 0;
    g.game_end = false;
    for (int i = 0; i < 9; i++)
        g.pos[i] = 0;

    SetTargetFPS(240);
    //mainloop which updates every
    while (!WindowShouldClose())
    {
        switch (Game_Window)
        {
            
        case 3:
            Draw_Pong(&player1, &player2, red1, red2, blue1, blue2, &ball, bricks);
            break;

        case 2:
            mousePoint = GetMousePosition();
            // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            //     printf("%f %f\n",mousePoint.x,mousePoint.y);
            //     // printf("%d\n",g.round);
            // }

            BeginDrawing();
            ClearBackground(BLACK);
            if (!check_win_condition(&g) && g.round < 9)
            {
                check_button(b, &g, mousePoint, Cross, Nought);
                //Draws a grid of red lines marking the board
                make_grid(b, WINWIDTH, WINHEIGHT, grid_texture);
                switch (g.round % 2)
                {
                case 0:
                    DrawText("Player 1's turn", 300, 200, 30, BLUE);
                    break;
                case 1:
                    DrawText("Player 2's turn", 1100, 200, 30, GREEN);
                    break;
                }
                // check_win_condition(&g);
                //if(check_win_condition(&g)) break;
            }
            else
            {
                switch (g.winner)
                {
                case 0:
                    DrawText("It's a draw.", 700, 450, 30, YELLOW);
                    break;
                case 1:
                    DrawText("Player 1 wins.", 700, 450, 30, BLUE);
                    break;
                case 2:
                    DrawText("Player 2 wins.", 700, 450, 30, GREEN);
                    break;
                }
            }
            EndDrawing();
            break;
        }
    }
    UnloadTexture(Cross);
    UnloadTexture(Nought);
    UnloadTexture(grid_texture);
    UnloadTexture(blank);

    return 0;
}
