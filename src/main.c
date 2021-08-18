#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/raylib.h"
#include "../include/utils.h"

int WINHEIGHT = 900;
int WINWIDTH = 1600;

int main()
{
    RESET:
    //initializing game window
    Game_Window = 0;
    /*
    0-Menu
    1-RLSPS
    2=TICTACTOE
    3-PONG
    4-CREDITS

    6- RESEST


    */

    //initializing window
    InitWindow(WINWIDTH, WINHEIGHT, "MadKauSing");
    SetWindowIcon(LoadImage("resources/madkausinglogo.png"));

    //initializing elements for PONG

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

    //initializing for TICTACTOE

    //loading images for rendering
    Image X = LoadImage("resources/X logo.png");
    ImageResize(&X, (float)X.width / 5, (float)X.height / 5);
    Image O = LoadImage("resources/O logo.png");
    ImageResize(&O, (float)O.width / 5, (float)O.height / 5);
    Image grid = LoadImage("resources/grid logo.png");

    Texture2D Cross = LoadTextureFromImage(X);
    Texture2D Nought = LoadTextureFromImage(O);
    Texture2D grid_texture = LoadTextureFromImage(grid);
    Texture2D blank = LoadTexture("resources/blank.jpg");

    //vec
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

    //initializing stuff for MENU

    Image pong_logo = LoadImage("resources/ponglogo.png");
    ImageResize(&pong_logo, 400, 400);
    Texture2D ponglogo = LoadTextureFromImage(pong_logo);

    Image rpssl_logo = LoadImage("resources/rpssl.png");
    ImageResize(&rpssl_logo, 400, 400);
    Texture2D rpssllogo = LoadTextureFromImage(rpssl_logo);

    Image tictactoe_logo = LoadImage("resources/tictactoelogo.png");
    ImageResize(&tictactoe_logo, 400, 400);
    Texture2D tictactoelogo = LoadTextureFromImage(tictactoe_logo);

    Image mks_logo = LoadImage("resources/madkausing.png");
    ImageResize(&mks_logo, 400, 400);
    Texture2D mkslogo = LoadTextureFromImage(mks_logo);


    struct Button menu_Button[4];
    for (int i = 0; i < 3; i++)
    {
        menu_Button[i].btn_action = 0;
        menu_Button[i].btn_bounds.x = 200 + 420 * i;
        menu_Button[i].btn_bounds.y = 450;
        menu_Button[i].btn_bounds.height = 400;
        menu_Button[i].btn_bounds.width = 400;
        menu_Button[i].btn_color = YELLOW;
    }
    menu_Button[3].btn_action=0;
    menu_Button[3].btn_bounds.x = 600;
    menu_Button[3].btn_bounds.y = 150;        
    menu_Button[3].btn_bounds.height = 400;
    menu_Button[3].btn_bounds.width = 400;
    menu_Button[3].btn_color = YELLOW;

    //Initialization for RPSLS:

    Image rock_img = LoadImage("resources/rock.png");
    ImageResize(&rock_img, 200, 200);
    Texture2D rock = LoadTextureFromImage(rock_img);
    
    Image paper_img = LoadImage("resources/paper.png");
    ImageResize(&paper_img, 200, 200);
    Texture2D paper = LoadTextureFromImage(paper_img);
    
    Image scissors_img = LoadImage("resources/scissors.png");
    ImageResize(&scissors_img, 200, 200);
    Texture2D scissors = LoadTextureFromImage(scissors_img);
    
    Image lizard_img = LoadImage("resources/lizard.png");
    ImageResize(&lizard_img, 250, 250);
    Texture2D lizard = LoadTextureFromImage(lizard_img);
    
    Image spock_img = LoadImage("resources/spock.png");
    ImageResize(&spock_img, 200, 200);
    Texture2D spock = LoadTextureFromImage(spock_img);
    
    
    //buttons for rlsps
    struct Button b_rpsls[5];
    struct game_rpsls g_r;
    g_r.winner = 0;
    g_r.p_choice = 0;
    for (int i = 0; i < 5; i++)
    {
        b_rpsls[i].btn_state = 0;
        b_rpsls[i].btn_action = 0;
        b_rpsls[i].btn_color = RAYWHITE;
        //b[i].img = blank;
    }
    for (int i = 0; i < 5; i++)
    {
        b_rpsls[i].btn_bounds.x = 100 + 300 * i;
        b_rpsls[i].btn_bounds.y = 350;
        b_rpsls[i].btn_bounds.width = 150;
        b_rpsls[i].btn_bounds.height = 150;
    }

    SetTargetFPS(240);
    //mainloop which updates ever
    //Game_Window=1;
    while (!WindowShouldClose())
    {
        switch (Game_Window)
        {
        case 0:

            Draw_Menu(menu_Button, ponglogo, tictactoelogo, rpssllogo,mkslogo);
            Menu_button(menu_Button, Game_Window, mousePoint);
            break;
        case 1:
            Draw_rpsls(WINHEIGHT,WINHEIGHT,rock,paper,scissors,lizard,spock,b_rpsls,&g_r);
            break;

        case 3:
            Draw_Pong(&player1, &player2, red1, red2, blue1, blue2, &ball, bricks);
            break;

        case 2:
            Draw_TicTacToe(WINHEIGHT, WINWIDTH, mousePoint, Cross, Nought, grid_texture, b, &g);
            break;
        case 4:
            Display_credits();
            break;

        case 6:
            CloseWindow();
            goto RESET;
        }
    }

    //unloading textures from GPU
    UnloadTexture(Cross);
    UnloadTexture(Nought);
    UnloadTexture(grid_texture);
    UnloadTexture(blank);
    UnloadTexture(ponglogo);
    UnloadTexture(rpssllogo);
    UnloadTexture(tictactoelogo);
    UnloadTexture(mkslogo);
    UnloadTexture(rock);
    UnloadTexture(paper);
    UnloadTexture(scissors);
    UnloadTexture(lizard);
    UnloadTexture(spock);
    return 0;
}
