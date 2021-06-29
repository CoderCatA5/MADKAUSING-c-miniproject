#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "raylib.h"

//some colors
#define CANARY (Color){250, 255, 129,1}



//some structs we are using  
struct Slider_pong{
    //struct for all rectangles; 
    //nested struct;
    Rectangle rect;
    float rotation;
    int lives;
};
struct Ball_pong{
    //struct for ball
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;
    int radius;
    int active;
};
struct Bricks_pong{
    Rectangle rect;
    int is_active;
    int health;
};
void Ballmovement(struct Ball_pong *ball);

void Check_Inputs(struct Slider_pong *player1,struct Slider_pong *player2);

void Render_Pong(struct Slider_pong player1,
            struct Slider_pong player2,
                Rectangle red1,
                Rectangle red2,
                Rectangle blue1,
                Rectangle blue2,
                struct Ball_pong ball,
                struct Bricks_pong *bricks);

void Pong_check_collisions(
    struct Ball_pong *ball,
    struct Slider_pong *player1,
    struct Slider_pong *player2,
    Rectangle red1,
    Rectangle red2,
    Rectangle blue1,
    Rectangle blue2,
    struct  Bricks_pong *bricks);

void Render_Lives(
    
                struct Slider_pong *player1,
                struct Slider_pong *player2);