#include <stddef.h>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>

#include "functions.h"

void drawPalette(Palette palette, Vector2* palette_cell) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int two_thirds_width = screen_width - (screen_width / 3);
    int pixel_size = 15;
    Rectangle grid_rectangle = {
        two_thirds_width + (screen_width - two_thirds_width)/2 - ((pixel_size * 16)/2),
        screen_height * 0.01 + 10,
        pixel_size * 16,
        pixel_size * 16,
    };
    int padding = 10;
    Rectangle group_box_rectangle = {
        grid_rectangle.x - padding,
        grid_rectangle.y - padding,
        grid_rectangle.width + padding*2,
        grid_rectangle.height + padding*2,
    };
    GuiGroupBox(group_box_rectangle, "Palette");
    for(int i = 0; i < 256; ++i) {
        DrawRectangle((i % 16 * pixel_size) + grid_rectangle.x, (i / 16 * pixel_size) + grid_rectangle.y,
                pixel_size, pixel_size, palette[i]);
    }
    GuiGrid(grid_rectangle, NULL, pixel_size, 1, palette_cell);
}

void drawCanvas(Tile* tile, Palette palette, int canvas_size, Vector2* canvas_cell) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int two_thirds_width = screen_width - (screen_width / 3);
    int grid_width = tile->width * canvas_size;
    int grid_height = tile->height * canvas_size;
    int grid_x = two_thirds_width/2 - grid_width/2;
    int grid_y = screen_height/2 - grid_height/2;
    for(int i = 0; i < (tile->width * tile->height); i++) {
        DrawRectangle(
                grid_x + ((i % tile->width) * canvas_size),
                grid_y + ((i / tile->width) * canvas_size),
                canvas_size,
                canvas_size,
                palette[tile->color_data[i]]
                );
    }
    GuiGrid((Rectangle) { grid_x, grid_y,  grid_width, grid_height }, "", canvas_size, 1, canvas_cell);
}

void handleInput(int* current_color, Tile* tile, Vector2* palette_cell, Vector2* canvas_cell) {
    if(!Vector2Equals(*palette_cell, (Vector2){ -1, -1 })) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *current_color = palette_cell->y * 16 + palette_cell->x;
        }
    }
    if(!Vector2Equals(*canvas_cell, (Vector2){ -1, -1 })) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            tile->color_data[(int)(canvas_cell->y * tile->width + canvas_cell->x)] = *current_color;
        }
    }
}