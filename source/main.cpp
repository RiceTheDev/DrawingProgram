#include "raylib.h"
#include "Screens.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int current_scene = 0;

int main(void)
{
    bool DrawAlreadyInited = false;
    bool MenuAlreadyInited = false;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    RenderTexture2D display = LoadRenderTexture(screenWidth, screenHeight);
    SetTargetFPS(60); 
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (current_scene == 0) {
            if (!MenuAlreadyInited) {
                InitMenuScreen(); 
                MenuAlreadyInited = true;
            }

            UpdateMenuScreen();
        }

        if (current_scene == 1) { 
            if (!DrawAlreadyInited) {
                InitDrawScreen(); 
                DrawAlreadyInited = true;
            }

            UpdateDrawScreen(display);
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void ChangeScreen(int scene) {

    current_scene = scene;
}