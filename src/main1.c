#include <stdio.h>
#include "../include/raylib.h"
#include "../include/utils.h"

int main()
{
    const int WindowWidth = 1600;
    const int WindowHeight = 900;

    InitWindow(WindowWidth, WindowHeight, "MyGame");

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

    //declare and intitialise button struct.
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

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
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
            make_grid(b, WindowWidth, WindowHeight, grid_texture);
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
    }
    UnloadTexture(Cross);
    UnloadTexture(Nought);
    UnloadTexture(grid_texture);
    UnloadTexture(blank);
}