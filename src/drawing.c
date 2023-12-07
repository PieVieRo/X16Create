#include <stddef.h>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>

#include "drawing.h"
#include "defines.h"
#include "defaults.h"
#include "globals.h"

const int FONT_SIZE = 10;
const Color FONT_COLOR = { 0x8C, 0xAC, 0xB4, 0xFF };

void handleDrawing(int* current_color, Tile* tile, Vector2* palette_cell, Vector2* canvas_cell) {
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

float getTwoThirdsWidth() {
    return screen_width - (screen_width / 3);
}

void drawPalette(Palette palette, Vector2* palette_cell, float* y_cursor);
void drawInfo(Palette palette, int current_color, float* y_cursor);
void drawRightSide(Palette palette, Vector2* palette_cell, int current_color) {
    float y_cursor = MARGIN;
    drawPalette(palette, palette_cell, &y_cursor);
    y_cursor += MARGIN;
    drawInfo(palette, current_color, &y_cursor);
}

void drawPalette(Palette palette, Vector2* palette_cell, float* y_cursor) {
    int two_thirds_width = getTwoThirdsWidth();
    int pixel_size = 15;
    Rectangle grid_rectangle = {
        two_thirds_width + (screen_width - two_thirds_width)/2 - ((pixel_size * 16)/2),
        screen_height * 0.01 + 10,
        pixel_size * 16,
        pixel_size * 16,
    };
    Rectangle group_box_rectangle = {
        grid_rectangle.x - PADDING,
        grid_rectangle.y - PADDING,
        grid_rectangle.width + PADDING*2,
        grid_rectangle.height + PADDING*2,
    };
    GuiGroupBox(group_box_rectangle, "Palette");
    for(int i = 0; i < 256; ++i) {
        DrawRectangle((i % 16 * pixel_size) + grid_rectangle.x, (i / 16 * pixel_size) + grid_rectangle.y,
                pixel_size, pixel_size, palette[i]);
    }
    GuiGrid(grid_rectangle, NULL, pixel_size, 1, palette_cell);
    *y_cursor += grid_rectangle.y + grid_rectangle.height;
}

char* current_depth_text[] = {
    "8bpp (256 colors)",
    "4bpp (16 colors)",
    "2bpp (4 colors)",
};
void drawInfo(Palette palette, int current_color, float* y_cursor) {
    int two_thirds_width = getTwoThirdsWidth();
    int pixel_size = 100;
    float beginning_y = *y_cursor;
    float draw_x = two_thirds_width + (screen_width - two_thirds_width)/2 - ((pixel_size)/2);
    *y_cursor += PADDING;
    DrawText(current_depth_text[color_depth], draw_x, *y_cursor, FONT_SIZE, FONT_COLOR);
    int text_width = MeasureText(current_depth_text[color_depth], FONT_SIZE);
    *y_cursor += FONT_SIZE + PADDING;
    Rectangle color_rectangle = {
        draw_x,
        *y_cursor,
        pixel_size,
        pixel_size,
    };
    *y_cursor += color_rectangle.height + PADDING;
    Rectangle group_box_rectangle = {
        color_rectangle.x - PADDING,
        beginning_y,
        (text_width > color_rectangle.width ? text_width : color_rectangle.width) + PADDING*2,
        *y_cursor - beginning_y,
    };
    GuiGroupBox(group_box_rectangle, "Info");
    DrawRectangleRec(color_rectangle, palette[current_color]);
}

void drawCanvas(Tile* tile, Palette palette, int canvas_size, Vector2* canvas_cell);
void drawDropdowns();
void drawLeftSide(Tile* tile, Palette palette, int canvas_size, Vector2* canvas_cell) {
    drawCanvas(tile, palette, canvas_size, canvas_cell);
    drawDropdowns();
}

void drawCanvas(Tile* tile, Palette palette, int canvas_size, Vector2* canvas_cell) {
    int two_thirds_width = getTwoThirdsWidth();
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

void drawDropdowns() {
    // BIT DEPTH DROPDOWN
    int dropdown_bit_depth_lock = 0;
    if(GuiDropdownBox((Rectangle){0, 0, 125, 25}, "8bpp (256 colors);4bpp (16 colors);2bpp (4 colors)", (int*)&color_depth, dropdown_bit_depth_lock)) dropdown_bit_depth_lock = !dropdown_bit_depth_lock;
}

