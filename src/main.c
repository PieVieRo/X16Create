#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

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
    Vector2 palette_cell = { -1, -1 };
    Vector2 canvas_cell = { -1, -1 };
    int current_color = 0;
    while(!WindowShouldClose()) {
        if(!Vector2Equals(palette_cell, (Vector2){ -1, -1 })) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                current_color = palette_cell.y * 16 + palette_cell.x;
            }
        }
        if(!Vector2Equals(canvas_cell, (Vector2){ -1, -1 })) {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                tile.color_data[(int)(canvas_cell.y * tile.width + canvas_cell.x)] = current_color;
            }
        }
        BeginDrawing();
        ClearBackground((Color) {0x18, 0x18, 0x18});

        drawPalette(current_palette, &palette_cell);

        drawCanvas(&tile, current_palette, canvas_size, &canvas_cell);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
