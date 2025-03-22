#include "raylib.h"
#include "raygui.h"
#include "Screens.hpp"
#include "Components/GuiFloatingWindow.hpp"

bool showNewFileMenu = false;
bool showAbout = false;
Texture2D logo;

// Window New Sprite
static Vector2 window_position = { 200, 200 };
static Vector2 window_size = { 175, 180 };
static bool minimized = false;
static bool moving = false;
static bool resizing = false;
static Vector2 scroll;

// About Window
static Vector2 window2_position = { 200, 200 };
static Vector2 window2_size = { 175, 180 };
static bool minimized2 = false;
static bool moving2 = false;
static bool resizing2 = false;
static Vector2 scroll2;

void InitMenuScreen(void) {
    logo = LoadTexture("../assets/Logo.png");
}

static void NewFileContent(Vector2 position, Vector2 scroll) {
    int button = GuiButton(Rectangle {15 + position.x,  150 + position.y, 48, 16}, "Create");
    int button2 = GuiButton(Rectangle {115 + position.x,  150 + position.y, 48, 16}, "Cancel");
    if (button == 1) ChangeScreen(1);
    if (button2 == 1) showNewFileMenu = false;
}

void UpdateMenuScreen(void) {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, WHITE);
        GuiStatusBar(Rectangle {0, 0, screenWidth, 30}, "");
        if(GuiLabelButton(Rectangle {10, 0, 48, 32}, "New File")) showNewFileMenu = true;
        if(GuiLabelButton(Rectangle {65, 0, 64, 32}, "About")) showAbout = true;
        if (showAbout)
        {
            int result = GuiWindowBox(Rectangle {50, 25, 300, 200}, "About");
            if (result == 1) showAbout = false;
        }

        if(showNewFileMenu)
        {
            GuiWindowFloating(&window_position, &window_size, &minimized, &moving, &resizing, &NewFileContent, (Vector2) { 150, 150 }, &scroll, "New File", false, showNewFileMenu);
        }
    EndDrawing();
}

