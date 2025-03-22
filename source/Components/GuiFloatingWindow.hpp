#include "raygui.h"
#include <cstddef>
#include <raylib.h>

// Copied from the RayGui examples
inline void GuiWindowFloating(Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing, void (*draw_content)(Vector2, Vector2), Vector2 content_size, Vector2 *scroll, const char* title, bool resizable, bool toggle) {
    #if !defined (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
        #define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
    #endif
    #if !defined (RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE)
        #define RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE 18
    #endif

    int close_title_size_delta_half = (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE) / 2;

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !*moving && !*resizing) {
        Vector2 mouse_position = GetMousePosition();

        Rectangle title_colision_rect = { position->x, position->y, size->x - (RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE + close_title_size_delta_half), RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT };
        Rectangle resize_colision_rect = { position->x + size->x - 20, position->y + size->y - 20, 20, 20 };

        if (CheckCollisionPointRec(mouse_position, title_colision_rect)) {
            *moving = true;
        } else if(!*minimized && CheckCollisionPointRec(mouse_position, resize_colision_rect)) {
            *resizing = true;
        }
    }

    if (*moving) {
        Vector2 mouse_delta = GetMouseDelta();
        position->x += mouse_delta.x;
        position->y += mouse_delta.y;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            *moving = false;

            if(position->x < 0) position->x = 0;
            else if (position->x > GetScreenWidth() - size->x) position->x = GetScreenWidth() - size->x;
            if(position->y < 0) position->y = 0;
            else if (position->y > GetScreenHeight()) position->y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
        }
    } else if (*resizing) {
        Vector2 mouse = GetMousePosition();
        if (resizable){
            if (mouse.x > position->x)
                size->x = mouse.x - position->x;
            if (mouse.y > position->y)
                size->y = mouse.y - position->y;

            if (size->x < 100) size->x = 100;
            else if(size->x > GetScreenWidth()) size->x = GetScreenWidth();
            if(size->y < 100) size->y = 100;
            else if (size->y > GetScreenHeight()) size->y = GetScreenHeight();
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                *resizing = false;
            }
        }
    }

    if (*minimized) {
        GuiStatusBar((Rectangle){ position->x, position->y, size->x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, title);
        if (GuiButton((Rectangle){ position->x + size->x - RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE - close_title_size_delta_half,
            position->y + close_title_size_delta_half,
            RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE,
            RAYGUI_WINDOWBOX_CLOSEBUTTON_SIZE },
            "#120#")) {
            *minimized = false;
        }
    } else {
        *minimized = GuiWindowBox((Rectangle) { position->x, position->y, size->x, size->y }, title);

        // scissor and draw content within a scroll panel
        if(draw_content != NULL) {
            Rectangle scissor = { 0 };
            GuiScrollPanel((Rectangle) { position->x, position->y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, size->x, size->y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT },
                                        NULL,
                                        (Rectangle) { position->x, position->y, content_size.x, content_size.y },
                                        scroll,
                                        &scissor);

            bool require_scissor = size->x < content_size.x || size->y < content_size.y;

            if(require_scissor) {
                BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
            }

            draw_content(*position, *scroll);

            if(require_scissor) {
                EndScissorMode();
            }
        }
    }
}