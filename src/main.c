#include <raylib.h>


// non-MSVC pragmas
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// MSVC pragmas
#pragma warning( push )
#pragma warning( disable : 4189)
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#pragma warning( pop )
#pragma GCC pop

Vector2 palette_cell = { -1, -1 };
Vector2 canvas_cell = { -1, -1 };

#include "drawing.h"
#include "structs.h"
#include "defaults.h"
#include "globals.h"

int main() {
    InitWindow(screen_width, screen_height, "X16Create");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    Tile tile = { 8, 8, {0} };
    Palette current_palette = { 0 };
    memcpy(current_palette, default_palette, sizeof(Palette));
    int current_color = 0;
    while(!WindowShouldClose()) {
        if(IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
            updateScale();
        }

        handleDrawing(&current_color, &tile, &palette_cell, &canvas_cell);
        BeginDrawing();
        ClearBackground((Color) {0x18, 0x18, 0x18, 0xFF});

        drawRightSide(current_palette, &palette_cell, current_color);

        drawLeftSide(&tile, current_palette, &canvas_cell);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
