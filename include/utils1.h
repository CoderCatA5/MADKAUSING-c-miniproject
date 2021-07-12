#include<stdio.h>
#include"raylib.h"


struct game{
    int mode;//game mode 1-Single player , 2 - Double player
    int winner;// 0 - draw , 1 - Player1 wins , 2 - Player2 wins
    int round;
    int pos[9];// 0 - empty , 1 - Selected by p1 , 2 - Selected by p2
    bool game_end;
};

//The structure of the button duh
struct Button{
    int btn_state;//animation state of the button= 0-Not on button, 1-Hover over button, 2-Button clicked
    int btn_action;//activation status of the button
    Rectangle btn_bounds;//position of the button
    Color btn_color;//color of the button
    Texture2D img;
};

void check_button(struct Button *b, struct game *g, Vector2 mousePoint, Texture2D X, Texture2D O);

void make_grid(struct Button *b,int WindowWidth, int WindowHeight,Texture2D grid);

bool check_win_condition(struct game *g);
