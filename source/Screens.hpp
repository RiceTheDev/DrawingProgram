#include "raylib.h"

// Screens
void ChangeScreen(int scene);
const int screenWidth = 800;
const int screenHeight = 450;

// Menu
void InitMenuScreen(void);
void UpdateMenuScreen(void);
void FinishMenuScreen(void);

// Draw
void InitDrawScreen(void);
void UpdateDrawScreen(RenderTexture2D display);
void FinishDrawScreen(void);

