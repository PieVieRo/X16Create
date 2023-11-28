#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

Vector2 palette_cell = { -1, -1 };
Vector2 canvas_cell = { -1, -1 };

#include "functions.h"
#include "structs.h"
#include "defaults.h"

int main() {
    int screen_width = 1280;
    int screen_height = 720;
    InitWindow(screen_width, screen_height, "X16Create");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    Tile tile = { 8, 8, {0} };
    int canvas_size = 30;
    Palette current_palette = { 0 };
    memcpy(current_palette, default_palette, sizeof(Palette));
    int current_color = 0;
    while(!WindowShouldClose()) {
        handleInput(&current_color, &tile, &palette_cell, &canvas_cell);
        BeginDrawing();
        ClearBackground((Color) {0x18, 0x18, 0x18});

        drawPalette(current_palette, &palette_cell);

        drawCanvas(&tile, current_palette, canvas_size, &canvas_cell);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
