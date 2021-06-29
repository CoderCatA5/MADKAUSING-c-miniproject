#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "include/raylib.h"

//some structs we are using
struct Slider_pong{
    //struct for all rectangles;
    //nested struct;
    Rectangle rect;
    float rotation;
};

struct Ball_pong{
    //struct for ball
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;
};

void Ballmovement(struct Ball_pong *ball){

    //updating the postition of ball with kinetic equations
    //s=ut+1/2at^2
    //but here t is taken as 1
    ball->pos.x  +=   (ball->velocity.x)+((1/2)*ball->acceleration.x);
    ball->pos.y  +=   (ball->velocity.y)+((1/2)*ball->acceleration.y);

    if(ball->pos.x>1600)ball->pos.x=0;
    if(ball->pos.x<0)ball->pos.x=1600;
}

//function checks collisions;
//void Check_Collisions();

void Check_Inputs(struct Slider_pong *player1,struct Slider_pong *player2){
    if(IsKeyDown(KEY_W)){
        player1->rect.y-=10;
    }
    if(IsKeyDown(KEY_S)){
        player1->rect.y+=10;
    }
    if(IsKeyDown(KEY_UP)){
        player2->rect.y-=10;
    }
    if(IsKeyDown(KEY_DOWN)){
        player2->rect.y+=10;
    }
}

//function to render all elements;
void Render(struct Slider_pong player1,struct Slider_pong player2,Rectangle red1,Rectangle red2,Rectangle blue1,Rectangle blue2,struct Ball_pong ball){
    DrawRectangle(800,0,5,900,RAYWHITE);//midfeild

    //drawing elements
    DrawRectanglePro(player1.rect,(Vector2){0,0},player1.rotation,DARKGRAY);
    DrawRectanglePro(player2.rect,(Vector2){0,0},player2.rotation,DARKGRAY);

    DrawRectanglePro(red1,(Vector2){0,0},0.0f,BLACK);
    DrawRectanglePro(red2,(Vector2){0,0},0.0f,BLACK);
    DrawRectanglePro(blue1,(Vector2){0,0},0.0f,BLACK);
    DrawRectanglePro(blue2,(Vector2){0,0},0.0f,BLACK);

    DrawCircle(ball.pos.x,ball.pos.y,10,BLACK);
}


void pong(){
    //initializing elements

    //player1
    struct Slider_pong player1;
    player1.rect.x=100;
    player1.rect.y=450;
    player1.rect.width=20;
    player1.rect.height=200;
    player1.rotation=0.0f;

    //player2
    struct Slider_pong player2;
    player2.rect.x=100;
    player2.rect.y=450;
    player2.rect.width=20;
    player2.rect.height=200;
    player2.rotation=0.0f;

    //Death walls
    Rectangle red1={0,0,5,900};
    Rectangle red2={0,1595,5,900};

    //Safe walls
    Rectangle blue1={0,0,1600,5};
    Rectangle blue2={0,895,1600,5};

    //ball
    struct Ball_pong ball;
    ball.pos.x=800;
    ball.pos.y=450;
    ball.velocity.x=10;
    ball.velocity.y=0;
    ball.acceleration.x=0;
    ball.acceleration.x=0;


    //mainloop which updates every 
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BEIGE);
            //Check_Collisions();

            Ballmovement(&ball);
            
            Render(player1,player2,red1,red2,blue1,blue2,ball);
            Check_Inputs(&player1,&player2);

        EndDrawing();

    }

}