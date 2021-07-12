#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/raylib.h"
#include "../include/utils.h"

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
