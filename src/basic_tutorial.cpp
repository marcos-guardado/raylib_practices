#include <raylib.h>

#define WIN_SIZE 800

int main()
{
    InitWindow(WIN_SIZE, WIN_SIZE, "Play Terraria");
    SetTargetFPS(80);
    int xPos = (WIN_SIZE / 2);
    int yPos = (WIN_SIZE / 2);

    while (WindowShouldClose() == false)
    {
        // if(IsKeyDown(KEY_D)){
        //     xPos += 3;
        // } 
        
        // if(IsKeyDown(KEY_A)){
        //     xPos -= 3;
        // }
        
        // if(IsKeyDown(KEY_W)){
        //     yPos -= 3;
        // }
        
        // if(IsKeyDown(KEY_S)){
        //     yPos += 3;
        // }

        BeginDrawing();
        // ClearBackground(BLACK);
        // DrawText("Nef es gay", xPos, yPos, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}