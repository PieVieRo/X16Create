#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "functions.h"
#include "structs.h"

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
    while(!WindowShouldClose()) {
        if(IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
        }
        BeginDrawing();
        ClearBackground((Color) {0x18, 0x18, 0x18});

        Vector2 palette_cell = { 0 };
        drawPalette(current_palette, &palette_cell);

        int two_thirds_width = screen_width - screen_width/3;
        int grid_width = tile.width * canvas_size;
        int grid_height = tile.height * canvas_size;
        Vector2 mouse_cell = { 0 };
        GuiGrid((Rectangle) { two_thirds_width/2 - grid_width/2 , screen_height/2 - grid_height/2,  grid_width, grid_height }, "", canvas_size, 1, &mouse_cell);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
