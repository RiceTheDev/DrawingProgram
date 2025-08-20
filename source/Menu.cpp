#include "raylib.h"
#include "raygui.h"
#include "Screens.hpp"
#include "images/logo.h"
#include "images/github.h"
//#include "images/avatar.h"
#include "Components/GuiFloatingWindow.hpp"

bool showNewFileMenu = false;
bool showAbout = false;
Texture2D logo;
Texture2D github_logo;
Texture2D avatar;

// Window New Sprite
static Vector2 window_position = { 200, 200 };
static Vector2 window_size = { 175, 180 };
static bool minimized = false;
static bool moving = false;
static bool resizing = false;
static Vector2 scroll;

// About Window
static Vector2 window2_position = { 200, 200 };
static Vector2 window2_size = { 250, 180 };
static bool minimized2 = false;
static bool moving2 = false;
static bool resizing2 = false;
static Vector2 scroll2;
char projectName[64] = "New Project";

void InitMenuScreen(void) {
    SetTargetFPS(60);
    logo = LoadTextureFromImage(LoadImageFromMemory(".png", logo_png, logo_png_len));
    github_logo = LoadTextureFromImage(LoadImageFromMemory(".png", github_logo_png, github_logo_png_len));
    //avatar = LoadTextureFromImage(LoadImageFromMemory(".png", avatar_png, avatar_png_len));
}

static void NewFileContent(Vector2 position, Vector2 scroll) {
    int button = GuiButton(Rectangle {15 + position.x,  150 + position.y, 48, 16}, "Create");
    int button2 = GuiButton(Rectangle {115 + position.x,  150 + position.y, 48, 16}, "Cancel");
    GuiLabel({15 + position.x,  27 + position.y, 160 - 15, 16}, "Project Name");
    GuiTextBox({15 + position.x,  40 + position.y, 160 - 15, 16}, projectName, 19, true);
    if (button == 1) ChangeScreen(1);   
    if (button2 == 1) showNewFileMenu = false;
}

static void AboutContent(Vector2 position, Vector2 scroll) {
    int button = GuiButton(Rectangle {101 + window2_position.x, (165 - 15) + window2_position.y, 48, 16}, "Close");
    DrawTexture(github_logo, 140 + position.x, 48 + position.y, WHITE);
    GuiLabel({20 + window2_position.x, 15 + window2_position.y, 256, 128}, "Made by RiceTheDev\ngithub.com/ricethedev\n\nKeybinds:\nScroll Wheel - Size of brush\nRight Click - Eraser");
    if (button == 1) showAbout = false;
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
            bool result = false;
            GuiWindowFloating(&window2_position, &window2_size, &minimized2, &moving2, &resizing2, &AboutContent, (Vector2) { 150, 150 }, &scroll2, "About", false, result);
        }

        if(showNewFileMenu)
        {
            GuiWindowFloating(&window_position, &window_size, &minimized, &moving, &resizing, &NewFileContent, (Vector2) { 150, 150 }, &scroll, "New File", false, showNewFileMenu);
        }
    EndDrawing();
}

