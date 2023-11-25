#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

#include "structs.h"

void drawPalette(Palette palette, Vector2* palette_cell) {
    const int two_thirds_width = GetScreenWidth() - (GetScreenWidth() / 3);
    const int pixel_size = 15;
    Rectangle grid_rectangle = {
        two_thirds_width + (GetScreenWidth() - two_thirds_width)/2 - ((pixel_size * 16)/2),
        GetScreenHeight() * 0.01 + 10,
        pixel_size * 16,
        pixel_size * 16,
    };
    const int padding = 10;
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

#endif
