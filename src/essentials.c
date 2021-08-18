#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/raylib.h"
#include "../include/utils.h"

//functions for pong
void Ballmovement(struct Ball_pong *ball)
{

    //updating the postition of ball with kinetic equations
    //s=ut+1/2at^2
    //but here t is taken as 1

    if (ball->active)
    {
        if (ball->velocity.x > 20)
            ball->velocity.x = 20; //limiting the max velocities of the ball
        if (ball->velocity.y > 20)
            ball->velocity.y = 20;
        ball->pos.x += ball->velocity.x + (ball->acceleration.x * 0.5);
        ball->pos.y += ball->velocity.y + (ball->acceleration.y * 0.5);

        ball->velocity.x += ball->acceleration.x;
        ball->velocity.y += ball->acceleration.y;

        if (ball->pos.x > 1600)
            ball->pos.x = 1585;
        if (ball->pos.x < 0)
            ball->pos.x = 15;
        if (ball->pos.y < 0)
            ball->pos.y = 15;
        if (ball->pos.y > 900)
            ball->pos.y = 885;
        if (ball->velocity.x > 20)
            ball->velocity.x = 20; //limiting the max velocities of the ball
        if (ball->velocity.y > 20)
            ball->velocity.y = 20;
    }
    else
    {
        ball->velocity.x = 0;
        ball->velocity.y = 0;
        ball->acceleration.y = 0;
        ball->acceleration.x = 0;
        ball->pos.x = 800;
        ball->pos.y = 450;
        ball->active = 1;
    }

    //fixing ball glitches;
}

void Check_Inputs(struct Slider_pong *player1, struct Slider_pong *player2)
{
    //checkin player inputs

    if (IsKeyDown(KEY_W) && player1->rect.y > 5)
    {
        player1->rect.y -= 5;
    }
    if (IsKeyDown(KEY_S) && player1->rect.y + player1->rect.height < 895)
    {
        player1->rect.y += 5;
    }
    if (IsKeyDown(KEY_UP) && player2->rect.y > 5)
    {
        player2->rect.y -= 5;
    }
    if (IsKeyDown(KEY_DOWN) && player2->rect.y + player2->rect.height < 895)
    {
        player2->rect.y += 5;
    }
}

void Render_Pong(struct Slider_pong *player1,
                 struct Slider_pong *player2,
                 Rectangle red1,
                 Rectangle red2,
                 Rectangle blue1,
                 Rectangle blue2,
                 struct Ball_pong *ball,
                 struct Bricks_pong *bricks)
{
    //bricks color logic
    Color brickcolor;

    DrawRectangle(800, 0, 1, 900, DARKGRAY); //midfeild

    //drawing elements
    //DrawRectanglePro(player1.rect,(Vector2){0,0},player1.rotation,(Color){ 10, 10, 10, 240 } );
    //DrawRectanglePro(player2.rect,(Vector2){0,0},player2.rotation,(Color){ 10, 10, 10, 240 } );
    DrawRectangleRounded(player1->rect, 0.5f, 100, WHITE);
    DrawRectangleRounded(player2->rect, 0.5f, 100, WHITE);

    DrawRectanglePro(red1, (Vector2){0, 0}, 0.0f, DARKGRAY);
    DrawRectanglePro(red2, (Vector2){0, 0}, 0.0f, DARKGRAY);
    DrawRectanglePro(blue1, (Vector2){0, 0}, 0.0f, DARKGRAY);
    DrawRectanglePro(blue2, (Vector2){0, 0}, 0.0f, DARKGRAY);

    if (ball->active)
        DrawCircleGradient(ball->pos.x, ball->pos.y, ball->radius, WHITE, PINK);
    else
        Game_End();
    for (int i = 0; i < 60; i++)
    {
        if ((bricks + i)->is_active)
        {
            switch ((bricks + i)->health)
            {
            //changing color based on health
            case 3:
                brickcolor = BLUE;
                break;
            case 2:
                brickcolor = YELLOW;
                break;
            case 1:
                brickcolor = RED;
                break;

            default:
                break;
            }
            /*
            void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);               // Draw rectangle with rounded edges
            void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, int lineThick, Color color);*/
            //DrawRectanglePro((bricks+i)->rect,(Vector2){0,0},0.0f,brickcolor);

            DrawRectangleRoundedLines((bricks + i)->rect, 0.4f, 0, 3, brickcolor);
        }
    }
}

void Pong_check_collisions(
    struct Ball_pong *ball,
    struct Slider_pong *player1,
    struct Slider_pong *player2,
    Rectangle red1,
    Rectangle red2,
    Rectangle blue1,
    Rectangle blue2,
    struct Bricks_pong *bricks)
{
    if (player1->lives && player2->lives)
    {
        //checks for collisions:
        if (CheckCollisionCircleRec(ball->pos, ball->radius, red1))
        {
            ball->velocity.x *= -1;
            player1->lives -= 1;
        }
        if (CheckCollisionCircleRec(ball->pos, ball->radius, red2))
        {
            ball->velocity.x *= -1;
            player2->lives -= 1;
        }

        if (CheckCollisionCircleRec(ball->pos, ball->radius, blue1) ||
            CheckCollisionCircleRec(ball->pos, ball->radius, blue2))
        {
            ball->velocity.y *= -1;
        }

        //collision logic for sliders
        if (CheckCollisionCircleRec(ball->pos, ball->radius, player1->rect))
        {
            ball->velocity.x *= -1;
            ball->velocity.y = (ball->pos.y - (player1->rect.y + (176 / 2))) / (player2->rect.height / 2) * 5;
        }
        if (CheckCollisionCircleRec(ball->pos, ball->radius, player2->rect))
        {
            ball->velocity.x *= -1;
            ball->velocity.y = (ball->pos.y - (player2->rect.y + (176 / 2))) / (player2->rect.height / 2) * 5;
        }

        //colission logic for bricks
        for (int i = 0; i < 60; i++)
        {

            if (CheckCollisionCircleRec(ball->pos, ball->radius, (bricks + i)->rect) && (bricks + i)->is_active)
            {
                (bricks + i)->health--;
                ball->velocity.x *= -1;
                if ((bricks + i)->health == 0)
                    (bricks + i)->is_active = 0;
            }
        }
        //player2->rect.y=ball->pos.y;
        //single player moment;
    }
    else
        ball->active = 0;
}

void Render_Lives(
    struct Slider_pong *player1,
    struct Slider_pong *player2)
{
    char snum1[5];
    char snum2[5];
    itoa(player1->lives, snum1, 10);
    itoa(player2->lives, snum2, 10);

    DrawFPS(10, 10);
    DrawText(snum1, 500, 300, 80, RAYWHITE);
    DrawText(snum2, 1100, 300, 80, RAYWHITE);
}

void Draw_Pong(
    struct Slider_pong *player1,
    struct Slider_pong *player2,
    Rectangle red1,
    Rectangle red2,
    Rectangle blue1,
    Rectangle blue2,
    struct Ball_pong *ball,
    struct Bricks_pong *bricks)
{
    BeginDrawing();
    ClearBackground(BLACK);
    Pong_check_collisions(&*ball, &*player1, &*player2, red1, red2, blue1, blue2, bricks);
    Render_Pong(&*player1, &*player2, red1, red2, blue1, blue2, ball, bricks);
    Check_Inputs(&*player1, &*player2);
    Render_Lives(&*player1, &*player2);
    Ballmovement(&*ball);
    EndDrawing();
}

//functions for tictactoe

void check_button(struct Button *b, struct game *g, Vector2 mousePoint, Texture2D X, Texture2D O)
{
    for (int i = 0; i < 9; i++)
    {
        //if statement checks if the mouse is over the button and the user has left clicked on the button
        if (CheckCollisionPointRec(mousePoint, (b + i)->btn_bounds))
        {
            //Technically the button is pressed when you release the left mouse button but that's fine
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                (b + i)->btn_action = 1;
        }
        if ((b + i)->btn_action == 1 && g->pos[i] == 0)
        {
            //In this block you write the code that is executed when the button is pressed
            if (g->round % 2 == 0)
            {
                (b + i)->img = X;
                (b + i)->btn_color = BLUE;
                g->pos[i] = 1;
            }
            else if (g->round % 2 == 1)
            {
                (b + i)->img = O;
                (b + i)->btn_color = PINK;
                g->pos[i] = 2;
            }
            g->round++;
            (b + i)->btn_action = 2;
            // printf("%d\n",g->pos[i]);
        }
    }
}

void make_grid(struct Button *b, int WindowWidth, int WindowHeight, Texture2D grid)
{
    DrawTexture(grid, WindowWidth / 2 - grid.width / 2, WindowHeight / 2 - grid.height / 2, WHITE);
    for (int i = 0; i < 9; i++)
    {
        //DrawRectangleRec((b+i)->btn_bounds,(b+i)->btn_color);
        DrawTexture((b + i)->img, (b + i)->btn_bounds.x, (b + i)->btn_bounds.y, (b + i)->btn_color);
    }
}

bool check_win_condition(struct game *g)
{
    int sign;
    if (g->round % 2 == 1)
    {
        sign = 1;
    }
    else if (g->round % 2 == 0)
    {
        sign = 2;
    }
    //horizontal row check
    int flag = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            flag = 0;
        if (g->pos[i] == sign)
            flag++;
        if (flag == 3)
        {
            g->winner = sign;
        }
    }

    flag = 0;
    //vertical row check
    for (int i = 0; i < 3; i++)
    {
        for (int k = i; k <= i + 6; k += 3)
        {
            if (g->pos[k] == sign)
                flag++;
        }
        if (flag == 3)
        {
            g->winner = sign;
        }
        flag = 0;
    }

    flag = 0;

    if ((g->pos[0] == sign && g->pos[4] == sign && g->pos[8] == sign) || (g->pos[2] == sign && g->pos[4] == sign && g->pos[6] == sign))
    {
        g->winner = sign;
    }
    if (g->winner != 0)
    {
        g->game_end = true;
    }
    return g->game_end;
}

void Draw_TicTacToe(
    int WINHEIGHT,
    int WINWIDTH,
    Vector2 mousePoint,
    Texture2D Cross,
    Texture2D Nought,
    Texture2D grid_texture,
    struct Button *b,
    struct game *g)
{
    mousePoint = GetMousePosition();
    // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    //     printf("%f %f\n",mousePoint.x,mousePoint.y);
    //     // printf("%d\n",g.round);
    // }

    BeginDrawing();
    ClearBackground(BLACK);
    if (!check_win_condition(&*g) && g->round < 9)
    {
        check_button(b, &*g, mousePoint, Cross, Nought);
        //Draws a grid of red lines marking the board
        make_grid(b, WINWIDTH, WINHEIGHT, grid_texture);
        switch (g->round % 2)
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
        switch (g->winner)
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
        Game_End();
    }
    EndDrawing();
}

//rpsls functions

void Draw_rpsls(int WINHEIGHT,
                int WINWIDTH,
                Texture2D rock,
                Texture2D paper,
                Texture2D scissors,
                Texture2D lizard,
                Texture2D spock,
                struct Button *b,
                struct game_rpsls *g_r)
{
    Vector2 mousePoint = GetMousePosition();
    char choice_names[5][10] = {"Rock", "Paper", "Scissor", "Lizard", "Spock"};

    BeginDrawing();
    ClearBackground(BLACK);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        printf("%d %d %d \n", g_r->p_choice, g_r->c_choice, g_r->winner);

    Render_rpsls(b, g_r, rock, paper, scissors, lizard, spock);

    if (g_r->winner == 0)
        check_button_rpsls(b, g_r, mousePoint);
    if (g_r->winner != 0)
    {
        DrawText(FormatText("You picked: %s", choice_names[g_r->p_choice]), 550, 250, 50, RAYWHITE);
        DrawText(FormatText("Computer picked: %s", choice_names[g_r->c_choice]), 480, 180, 50, RAYWHITE);

        switch (g_r->winner)
        {
        case 1:
            DrawText("You win.", 690, 650, 60, GREEN);
            break;
        case 2:
            DrawText("You lose.", 690, 650, 60, RED);
            break;
        case 3:
            DrawText("Draw.", 690, 650, 60, GRAY);
            break;
        }
        Game_End();
    }

    EndDrawing();
}

int comp_turn()
{
    int rig_mode = GetRandomValue(0, 4);
    return rig_mode;
}

void Render_rpsls(struct Button *b,
                  struct game_rpsls *game,
                  Texture2D rock,
                  Texture2D paper,
                  Texture2D scissors,
                  Texture2D lizard,
                  Texture2D spock)
{
    DrawTexture(rock, b->btn_bounds.x, b->btn_bounds.y, b->btn_color);
    DrawTexture(paper, (b + 1)->btn_bounds.x, (b + 1)->btn_bounds.y, (b + 1)->btn_color);
    DrawTexture(scissors, (b + 2)->btn_bounds.x, (b + 2)->btn_bounds.y, (b + 2)->btn_color);
    DrawTexture(lizard, (b + 3)->btn_bounds.x, (b + 3)->btn_bounds.y, (b + 3)->btn_color);
    DrawTexture(spock, (b + 4)->btn_bounds.x, (b + 4)->btn_bounds.y, (b + 4)->btn_color);
}

void check_button_rpsls(struct Button *b_rpsls, struct game_rpsls *g_r, Vector2 mousePoint)
{
    for (int i = 0; i < 5; i++)
    {

        //if statement checks if the mouse is over the button and the user has left clicked on the button
        if (CheckCollisionPointRec(mousePoint, (b_rpsls + i)->btn_bounds))
        {
            //btn_state will be used when textures are implemented
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                (b_rpsls + i)->btn_action = 1;
        }

        if ((b_rpsls + i)->btn_action == 1)
        {
            g_r->p_choice = i;
            check_winner_rpsls(g_r);
            if (g_r->winner == 1)
                (b_rpsls + i)->btn_color = GREEN;
            else if (g_r->winner == 2)
                (b_rpsls + i)->btn_color = RED;
            else if (g_r->winner == 3)
                (b_rpsls + i)->btn_color = BLUE;
        }
    }
}

void check_winner_rpsls(struct game_rpsls *g_r)
{
    if (g_r->winner == 0) //if the game has not been played yet. Make the comp pick a move.
        g_r->c_choice = comp_turn();
    switch (g_r->p_choice)
    {
    case 0:
        if (g_r->c_choice == 2 || g_r->c_choice == 3)
            g_r->winner = 1;
        else
            g_r->winner = 2;
        break;
    case 1:
        if (g_r->c_choice == 0 || g_r->c_choice == 4)
            g_r->winner = 1;
        else
            g_r->winner = 2;
        break;
    case 2:
        if (g_r->c_choice == 1 || g_r->c_choice == 3)
            g_r->winner = 1;
        else
            g_r->winner = 2;
        break;
    case 3:
        if (g_r->c_choice == 1 || g_r->c_choice == 4)
            g_r->winner = 1;
        else
            g_r->winner = 2;
        break;
    case 4:
        if (g_r->c_choice == 0 || g_r->c_choice == 2)
            g_r->winner = 1;
        else
            g_r->winner = 2;
        break;
    }
    if (g_r->p_choice == g_r->c_choice) //draw
        g_r->winner = 3;
}
/////

void Menu_button(struct Button *b, int Game_window, Vector2 mousePoint)
{
    mousePoint = GetMousePosition();
    for (int i = 0; i < 4; i++)
    {
        //if statement checks if the mouse is over the button and the user has left clicked on the button
        if (CheckCollisionPointRec(mousePoint, (b + i)->btn_bounds))
        {
            //Technically the button is pressed when you release the left mouse button but that's fine
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                (b + i)->btn_action = 1;
        }
        if ((b + i)->btn_action == 1)
        {

            Game_Window = i + 1;
        }
    }
}

void Draw_Menu(struct Button *b, Texture2D ponglogo, Texture2D tictactoelogo, Texture2D rpssllogo, Texture2D mkslogo)
{
    BeginDrawing();
    ClearBackground(BLACK);
    //for (int i = 0; i < 3; i++)
    //{
    //DrawRectangleRec((b + i)->btn_bounds, (b + i)->btn_color);
    //DrawTexture(ponglogo,(b+i)->btn_bounds.x,(b+i)->btn_bounds.y,BLANK);
    //}
    char text[] = "M A D K A U S I N G";

    DrawText(text, 300, 50, 100, WHITE);
    DrawTexture(rpssllogo, (b + 0)->btn_bounds.x, (b + 0)->btn_bounds.y, WHITE);
    DrawTexture(tictactoelogo, (b + 1)->btn_bounds.x, (b + 1)->btn_bounds.y, WHITE);
    DrawTexture(ponglogo, (b + 2)->btn_bounds.x, (b + 2)->btn_bounds.y, WHITE);
    DrawTexture(mkslogo, (b + 3)->btn_bounds.x, (b + 3)->btn_bounds.y, WHITE);
    EndDrawing();
}
void Display_credits()
{
    BeginDrawing();
    ClearBackground(BLACK);
    char credits1[] = {"C R E A T E D  B Y"};
    char credits2[] = {"AYUSH SINGH"};
    char credits3[] = {"AYUSHMAAN KAUSHIK"};
    char credits4[] = {"BHAVINI MADHURANATH"};
    char credits5[] = {"A R T  B Y"};
    char credits6[] = {"SEJAL SURYAWANSHI"};
    DrawText(credits1, 300, 50, 100, WHITE);
    DrawText(credits2, 600, 170, 60, WHITE);
    DrawText(credits3, 460, 270, 60, WHITE);
    DrawText(credits4, 430, 370, 60, WHITE);
    DrawText(credits5, 550, 500, 100, WHITE);
    DrawText(credits6, 500, 620, 60, WHITE);
    Game_End();
    EndDrawing();
}
void Game_End()
{
    char text[] = "PRESS ENTER TO GO BACK TO MAIN MENU";
    DrawText(text, 250,800 , 50, WHITE);
    if (IsKeyPressed(KEY_ENTER))
    {
        Game_Window = 6;
    }
}