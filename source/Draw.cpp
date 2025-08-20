#include "raylib.h"
#include "raygui.h"
#include "Screens.hpp"
#include <iostream>
#if defined(__wasm__)
#include <emscripten/emscripten.h>
#endif

int radius = 5;
RenderTexture2D canvas;
bool showColorPicker = false;
Color color = BLACK;

void DrawCheckerboard() {
    int checkerSize = 16;

    Color lightGray = {200, 200, 200, 255};
    Color darkGray = {150, 150, 150, 255};

    for (int y = 35; y < screenHeight; y += checkerSize) {
        for (int x = 0; x < screenWidth; x += checkerSize) {
            int checkerX = x / checkerSize;
            int checkerY = (35 - y) / checkerSize;
            Color checkerColor = ((checkerX + checkerY) % 2 == 0) ? lightGray : darkGray;
            DrawRectangle(x, y, checkerSize, checkerSize, checkerColor);

        }
    }
}

void UpdateDrawScreen(RenderTexture2D display) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    DrawCheckerboard();

    GuiStatusBar(Rectangle {0, 0, screenWidth, 35}, "");
    int colorButton = GuiButton(Rectangle {5, 5, 25, 25}, "#26#");
    int saveButton = GuiButton(Rectangle {32.5, 5, 25, 25}, "#02#");
    
    if (colorButton) showColorPicker = !showColorPicker;
    if (saveButton) {
        Image image = LoadImageFromTexture(canvas.texture);
        ImageFlipVertical(&image);
        ExportImage(image, "my_amazing_texture_painting.png");
        UnloadImage(image);
#if defined(__wasm__)
        EM_ASM({
            const filename = "my_amazing_texture_painting.png";
            const data = FS.readFile(filename);
            const blob = new Blob([data], {type: "image/png"});
            const url = URL.createObjectURL(blob);
            const a = document.createElement("a");
            a.href = url;
            a.download = filename;
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            URL.revokeObjectURL(url);
            console.log("download started");
        });
#endif
    }
    
    radius += ((float)GetMouseWheelMove());
    if (radius < 1) radius = 1;
    
    bool isErasing = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    bool isDrawing = IsMouseButtonDown(MOUSE_LEFT_BUTTON) || (GetGestureDetected() == GESTURE_DRAG);
    
    if (isDrawing) {
        BeginTextureMode(canvas);
        
        if (!showColorPicker) {
            if (isErasing) {
                BeginBlendMode(BLEND_SUBTRACT_COLORS);
                DrawCircle(GetMouseX(), GetMouseY() - 35, radius, (Color){255, 255, 255, 0});
                EndBlendMode();
            } else {
                DrawCircle(GetMouseX(), GetMouseY() - 35, radius, color);
            }
        } else {
            if (!CheckCollisionPointRec(GetMousePosition(), Rectangle {30, 30, 180, 150})) {
                if (isErasing) {
                    BeginBlendMode(BLEND_SUBTRACT_COLORS);
                    DrawCircle(GetMouseX(), GetMouseY() - 35, radius, (Color){255, 255, 255, 0});
                    EndBlendMode();
                } else {
                    DrawCircle(GetMouseX(), GetMouseY() - 35, radius, color);
                }
            }
        }
        
        EndTextureMode();
    }
    
    DrawTextureRec(canvas.texture,
        Rectangle { 0, 0, (float)canvas.texture.width, -(float)canvas.texture.height },
        Vector2 {0, 35},
        WHITE);
    
    if (showColorPicker) {
        GuiColorPicker(Rectangle {30, 30, 150, 150}, "Color Picker", &color);
    }
    
    EndDrawing();
}

void InitDrawScreen() {
    SetTargetFPS(0);
    std::cout << "[LOG] Initing Drawing\n";
    canvas = LoadRenderTexture(screenWidth, screenHeight);
    
    BeginTextureMode(canvas);
    ClearBackground(BLANK);
    EndTextureMode();
}