#include "raylib.h"
#include "raygui.h"
#include "Screens.hpp"
#include <iostream>

int radius = 5; // Radius of the brush
RenderTexture2D canvas;
bool showColorPicker = false;
bool clicking = false;
Color color = BLACK;
void UpdateDrawScreen(RenderTexture2D display) {
    BeginDrawing();
        GuiStatusBar(Rectangle {0, 0, screenWidth, 35}, "");
        int colorButton = GuiButton(Rectangle {5, 5, 25, 25}, "#26#");
        if (colorButton) { if (showColorPicker) showColorPicker = false; else showColorPicker = true; }
        if (showColorPicker) {
            GuiColorPicker(Rectangle {30, 30, 150, 150}, "Color Picker", &color);
        }
        canvas = display;
        radius += ((float)GetMouseWheelMove());
        ClearBackground(RAYWHITE);
        if (!clicking) DrawCircle(GetMouseX(), GetMouseY(), radius, color);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || (GetGestureDetected() == GESTURE_DRAG)){
            BeginTextureMode(display);
                if (!CheckCollisionPointRec(GetMousePosition(), Rectangle {30, 30, 180, 150})) {
                    if (!clicking) DrawCircle(GetMouseX(), GetMouseY() - 35, radius, color);
                    clicking = false;
                } else {
                    clicking = true;
                }
            EndTextureMode();
        }
        DrawTextureRec(canvas.texture, Rectangle { 0, 0, (float)canvas.texture.width, (float)-canvas.texture.height }, Vector2 {0, 35}, WHITE);
    EndDrawing();
}

void InitDrawScreen() {
    std::cout << "[LOG] Initing Drawing\n";
}