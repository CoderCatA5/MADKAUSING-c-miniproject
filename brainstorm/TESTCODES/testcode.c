#include "include/raylib.h"


int WindowHeight=1280;
int WindowWidth=720;

struct Rect
{
    int x;
    int y;
    int height;
    int width;
};


int main(){

    //struct Rect a={100,100,200,200};

    //Vector2 b={300,200};
    //Vector2 c={100,50};//u can deploy 2D position vectors LAB


    //or rectangle coordinates(predefined dont have to use my made struct)
    Rectangle new={400,400,200,100};
    Rectangle new1={400,600,200,100};
    //posx,posy,width,height
    InitWindow(WindowHeight,WindowWidth,"Test");//height followed with width follwed with proj name
    SetTargetFPS(60);

    while(!WindowShouldClose()){ //window should close is a function that detects if window is closed.
        BeginDrawing();
            static float rotation=0.0f;
            rotation += 0.5f;
            //declaring a variable in static memory

            ClearBackground((Color){255,0,255,0});
            ClearBackground(RAYWHITE);
            //color is a struct here with values {255,0,255,0} this is pink which are rgb values
            //to clear black buffer we do this set a background.
            
            //DrawRectangle(a.x,a.y,a.width,a.height,YELLOW);
            //posx,posy,width,height,color

            //DrawRectangleV(b,c,BLUE);//the way u defone stucts in functions is using (structname){structvalues}
            //this was using rectangle coordinates,Vector 2 is an inbulit struct.WOOOOOOO

            //DrawRectangleRec(new,GREEN);
            //using rectangle parameters

            DrawRectanglePro(new,(Vector2){100,50},rotation,GREEN);
            DrawRectanglePro(new1,(Vector2){100,50},rotation,GREEN);

            //rectangle,initial postion,rotation in degrees,color
            //initial postion is a vector relative to the end of the rectangle
            //if (0,0) it rotates about one of its ends
            //if on centre it rotates about its centre

            //DrawRectangleLinesEx((Rectangle){500,500,100,100},10,BLACK);//Ex allows u to set girth 2nd last.
           // DrawCircle(500,300,64,ORANGE);
            //draw circles also has vectors

            //DrawTriangle((Vector2){50,0},(Vector2){0,100},(Vector2){100,100},RED);//requires three points CCW 


            static float timer =0.0f;
            static int sides = 0;

            timer+=GetFrameTime();//Returns time between each frame

            if (timer>0.2f)//every point two secs it adds one side
            {
                timer =0.0f;
                sides++;
            }
            
            DrawPoly((Vector2){600,300},sides % 12,200,0.0,PINK);//center vecotr,no of sides,radius from centre,rotation,color

            


            

        EndDrawing();
        //in raylib we notice functions like begin and end
        //begin camera end camera
        //begin shader end shader
    }
}