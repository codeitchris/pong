#include <iostream>
#include "raylib.h"

// Global definitions
#define ScreenWidth 1000
#define ScreenHeight 800
#define MinWindowWidth 500
#define MinWindowHeight 200

//Creating Circles structure
struct Circles
    {
        float xvar;
        float yvar;
        float radius;
        Color color;
    };

//Boolean definitions
bool newGamePressed = false;
bool beginGame = false;
bool showOpenScreen = true;

// Code to make a button
void button(float x, float y, char *Text, Color color, bool &state){
    float font = (2.5*GetScreenWidth())/100;
    Rectangle r1 = {
        .x =x,
        .y=y,
        .width = (float) MeasureText(Text, font),
        .height = (float) font,
    };


    if(CheckCollisionPointRec(GetMousePosition(), r1)){
        DrawText(Text, x,y,font,RED);
        if(IsMouseButtonPressed(0)){
           if(state == true)
                state = false;
            else
                state = true;
           
           return; 
        }
    } else {
        DrawText(Text, x,y,font,color);
    }

    return;
}


int main() {
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "begin");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);
        

    int x = GetScreenHeight();
    int y = GetScreenWidth();

        Rectangle r1;
        
        r1.y=.25*(x);
        r1.x = 20;
        r1.width = (2*y)/100;
        r1.height = (35*x/100);

        Rectangle r2;
        r2.y=.25*(x);
        r2.x = ((y-(.02*y))-20);
        r2.width = (2*y)/100;
        r2.height = (35*x/100);  

        Circles ball;
        ball.xvar = y/2.0f;
        ball.yvar =  x/2.0f;
        ball.radius = 5;
        ball.color = WHITE;

        float xballspeed = 300;
        float yballspeed = 300;  

//Draws the window
    while(!WindowShouldClose()){
        
        BeginDrawing();

        ClearBackground(BLUE);

        
        float leftRecSpeed = 300;
        float rightRecSpeed = 300;

        int x = GetScreenHeight();
        int y = GetScreenWidth();
// Creates the rectabgles
        DrawRectangleV (Vector2{(float) r1.x, (float) r1.y},
                        Vector2{(float) r1.width, (float) r1.height}, BLACK);

        DrawRectangleV (Vector2{(float) r2.x, (float) r2.y},
                        Vector2{(float) r2.width, (float) r2.height}, BLACK);
        

        DrawCircle(ball.xvar, ball.yvar, ball.radius, ball.color);

        if(showOpenScreen){
            int font = 2.5*GetScreenWidth()/100;
            char begin[] = "Begin?";
            float holder = MeasureText(begin, font)/2;
            button(GetScreenWidth()/2 - holder, GetScreenHeight()/2, begin, BLACK, beginGame);
        }

// Moves the ball
        if(beginGame == true){
            showOpenScreen = false;
            ball.xvar += xballspeed*GetFrameTime();
            ball.yvar += yballspeed*GetFrameTime();                
        }
        
// Determines if the ball has hit the wall

        if(ball.xvar >= GetScreenWidth()){
            xballspeed =0;
            yballspeed = 0;
            char ending[] = "Game Over";
            int font = 2.5*GetScreenWidth()/100;
            float correcting = MeasureText(ending, font)/2;
            DrawText(ending, GetScreenWidth()/2 - correcting, 40*GetScreenHeight()/100, font, BLACK);

            char newGame[] = "New Game?";
            float holder = MeasureText(newGame, font)/2;
            button(GetScreenWidth()/2 - holder, GetScreenHeight()/2, newGame, BLACK, newGamePressed);
        }

        if(ball.xvar <= 0){
            xballspeed =0;
            yballspeed = 0;
            char ending[] = "Game Over";
            int font = 2.5*GetScreenWidth()/100;
            float correcting = MeasureText(ending, font)/2;
            DrawText(ending, GetScreenWidth()/2 - correcting, 40*GetScreenHeight()/100, font, BLACK);

            char newGame[] = "New Game?";
            float holder = MeasureText(newGame, font)/2;
            button(GetScreenWidth()/2 - holder, GetScreenHeight()/2, newGame, BLACK, newGamePressed);
        }
// Resets everything if new game pressed
        if(newGamePressed == true){
            ball.xvar = y/2.0f;
            ball.yvar =  x/2.0f; 
            r1.y=.25*(x);
            r1.x = 20;
            r2.y=.25*(x);
            r2.x = ((y-(.02*y))-20);
            xballspeed = 300;
            yballspeed = 300; 
            newGamePressed = false;
        }

// Reverses direction if it hits the top or bottom wall
        if(ball.yvar >= GetScreenHeight()){
            ball.yvar = GetScreenHeight();
            yballspeed *= -1;
        }
        if(ball.yvar <= 0){
            ball.yvar = 0;
            yballspeed *= -1;
        }
// Code for key commands
        if(IsKeyDown(KEY_E) && r1.y > 0){
            r1.y -= rightRecSpeed*GetFrameTime();
        }
        if(IsKeyDown(KEY_D) && r1.y < (GetScreenHeight()-r1.height)){ 
            r1.y += rightRecSpeed*GetFrameTime();
        }
        if(IsKeyDown(KEY_UP) && r2.y > 0){
            r2.y -= leftRecSpeed*GetFrameTime();
        }

        if(IsKeyDown(KEY_DOWN) && r2.y < (GetScreenHeight()-r2.height)){
            r2.y += leftRecSpeed*GetFrameTime();
        }

        if(CheckCollisionCircleRec({ball.xvar, ball.yvar}, ball.radius, r1)){
            xballspeed *= -1.1;
            rightRecSpeed *=1.3;
            leftRecSpeed *=1.3;
        }

        if(CheckCollisionCircleRec({ball.xvar, ball.yvar}, ball.radius, r2)){
            xballspeed *= -1.1;
            rightRecSpeed *=1.3;
            leftRecSpeed *=1.3;
        }
        
        
        EndDrawing();


    }
    
    CloseWindow();
    
    return 0;
}
