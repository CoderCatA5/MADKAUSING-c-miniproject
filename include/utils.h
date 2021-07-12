#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"

//some colors
#define CANARY (Color){250, 255, 129, 1};
#define Pong_Blue (Color){19, 255, 244, 1};
#define Pong_Yellow (Color){255, 247, 20, 1};
#define Pong_Red (Color){255, 37, 19, 1};

int Game_Window;

//some structs we are using for pong
struct Slider_pong
{
    //struct for all rectangles;
    //nested struct;
    Rectangle rect;
    float rotation;
    int lives;
};
struct Ball_pong
{
    //struct for ball
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;
    int radius;
    int active;
};
struct Bricks_pong
{
    Rectangle rect;
    int is_active;
    int health;
};

//function prototypes pong
void Ballmovement(struct Ball_pong *ball);

void Check_Inputs(struct Slider_pong *player1, struct Slider_pong *player2);

void Render_Pong(struct Slider_pong *player1,
                 struct Slider_pong *player2,
                 Rectangle red1,
                 Rectangle red2,
                 Rectangle blue1,
                 Rectangle blue2,
                 struct Ball_pong *ball,
                 struct Bricks_pong *bricks);

void Pong_check_collisions(
    struct Ball_pong *ball,
    struct Slider_pong *player1,
    struct Slider_pong *player2,
    Rectangle red1,
    Rectangle red2,
    Rectangle blue1,
    Rectangle blue2,
    struct Bricks_pong *bricks);

void Render_Lives(

    struct Slider_pong *player1,
    struct Slider_pong *player2);

void Draw_Pong(
    struct Slider_pong *player1,
    struct Slider_pong *player2,
    Rectangle red1,
    Rectangle red2,
    Rectangle blue1,
    Rectangle blue2,
    struct Ball_pong *ball,
    struct Bricks_pong *bricks);

//tictactoe
struct game
{
    int mode;   //game mode 1-Single player , 2 - Double player
    int winner; // 0 - draw , 1 - Player1 wins , 2 - Player2 wins
    int round;
    int pos[9]; // 0 - empty , 1 - Selected by p1 , 2 - Selected by p2
    bool game_end;
};

struct Button
{
    int btn_state;        //animation state of the button= 0-Not on button, 1-Hover over button, 2-Button clicked
    int btn_action;       //activation status of the button
    Rectangle btn_bounds; //position of the button
    Color btn_color;      //color of the button
    Texture2D img;
};

void check_button(struct Button *b, struct game *g, Vector2 mousePoint, Texture2D X, Texture2D O);

void make_grid(struct Button *b, int WindowWidth, int WindowHeight, Texture2D grid);

bool check_win_condition(struct game *g);

void Draw_TicTacToe(
    int WINHEIGHT,
    int WINWIDTH,
    Vector2 mousePoint,
    Texture2D Cross,
    Texture2D Nought,
    Texture2D grid_texture,
    struct Button *b,
    struct game *g);

//Menu stuff
void Menu_button(struct Button *b, int Game_window, Vector2 mousePoint);

void Draw_Menu(struct Button *b);
