#include <stddef.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>

#include "drawing.h"
#include "defines.h"
#include "defaults.h"
#include "globals.h"

const int FONT_SIZE = 10;
const Color FONT_COLOR = { 0x8C, 0xAC, 0xB4, 0xFF };
float scale = 1;

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

void updateScale() {
    scale = fmin((float)screen_height / default_screen_height, (float)screen_width / default_screen_width);
}

float getTwoThirdsWidth() {
    return screen_width - (screen_width / 3);
}

int getCurrentPalette(int current_color) {
    return current_color / 16;
}

void drawPalette(Palette palette, Vector2* palette_cell, int current_color, float* y_cursor);
void drawInfo(Palette palette, int current_color, float* y_cursor);
void drawRightSide(Palette palette, Vector2* palette_cell, int current_color) {
    float y_cursor = screen_height * 0.01;
    drawPalette(palette, palette_cell, current_color, &y_cursor);
    y_cursor += MARGIN;
    drawInfo(palette, current_color, &y_cursor);
}

void drawPalette(Palette palette, Vector2* palette_cell, int current_color, float* y_cursor) {
    const int pixel_size = 15 * scale;
    const int two_thirds_width = getTwoThirdsWidth();
    
    float palette_grid_x          = two_thirds_width + (screen_width - two_thirds_width)/2 - ((pixel_size * 16)/2);
    float palette_grid_length     = 16 * pixel_size;
    const int triangle_side       = pixel_size;
    const float triangle_height   = (triangle_side * sqrtf(3)) / 2;
    const float grid_tri_padding  = PADDING / 2 * scale;
    if(color_depth > EIGHT_BPP) {

        palette_grid_x -= (triangle_height + grid_tri_padding)/2;
        
        const Vector2 triangle_coords[3] = {
            (Vector2) { 
                .x = palette_grid_x + palette_grid_length + grid_tri_padding,
                .y = *y_cursor + PADDING + (pixel_size/2) + (getCurrentPalette(current_color) * pixel_size),

            },
            (Vector2) {
                .x = triangle_coords[0].x + triangle_height,
                .y = *y_cursor + PADDING + pixel_size + (getCurrentPalette(current_color) * pixel_size),
            },
            (Vector2) {
                .x = triangle_coords[0].x + triangle_height,
                .y = *y_cursor + PADDING + (getCurrentPalette(current_color) * pixel_size),
            },
        };
        DrawTriangle(triangle_coords[0], triangle_coords[1], triangle_coords[2], RAYWHITE);
    }

    Rectangle palette_grid_rectangle = {
        .x      = palette_grid_x,
        .y      = *y_cursor + PADDING,
        .width  = palette_grid_length,
        .height = palette_grid_length,
    };
    Rectangle palette_group_box = {
        .x      = palette_grid_x - PADDING,
        .y      = *y_cursor,
        .width  = palette_grid_length + 2*PADDING,
        .height = palette_grid_length + 2*PADDING,
    };
    if(color_depth > EIGHT_BPP) {   
        palette_group_box.width += grid_tri_padding + triangle_height;
    }   
    GuiGroupBox(palette_group_box, "Palette");
    for(int i = 0; i < 256; ++i) {
        DrawRectangle((i % 16 * pixel_size) + palette_grid_rectangle.x, (i / 16 * pixel_size) + palette_grid_rectangle.y,
                pixel_size, pixel_size, palette[i]);
    }
    GuiGrid(palette_grid_rectangle, NULL, pixel_size, 1, palette_cell);
    *y_cursor += palette_group_box.height;
}

char* current_depth_text[] = {
    "8bpp (256 colors)",
    "4bpp (16 colors)",
    "2bpp (4 colors)",
};
void drawInfo(Palette palette, int current_color, float* y_cursor) {
    int two_thirds_width = getTwoThirdsWidth();
    int pixel_size = 100*scale;
    float beginning_y = *y_cursor;
    float draw_x = two_thirds_width + (screen_width - two_thirds_width)/2 - ((pixel_size)/2);
    *y_cursor += PADDING*scale;
    DrawText(current_depth_text[color_depth], draw_x, *y_cursor, FONT_SIZE*scale, FONT_COLOR);
    int text_width = MeasureText(current_depth_text[color_depth], FONT_SIZE*scale);
    *y_cursor += (FONT_SIZE + PADDING) * scale;
    Rectangle color_rectangle = {
        draw_x,
        *y_cursor,
        pixel_size,
        pixel_size,
    };
    *y_cursor += color_rectangle.height + PADDING*scale;
    Rectangle group_box_rectangle = {
        color_rectangle.x - PADDING*scale,
        beginning_y,
        (text_width > color_rectangle.width ? text_width : color_rectangle.width) + PADDING*2*scale,
        *y_cursor - beginning_y,
    };
    GuiGroupBox(group_box_rectangle, "Info");
    DrawRectangleRec(color_rectangle, palette[current_color]);
}

void drawCanvas(Tile* tile, Palette palette, Vector2* canvas_cell);
void drawDropdowns();
void drawLeftSide(Tile* tile, Palette palette, Vector2* canvas_cell) {
    drawCanvas(tile, palette, canvas_cell);
    drawDropdowns();
}

void drawCanvas(Tile* tile, Palette palette, Vector2* canvas_cell) {
    int canvas_size = 30 * scale;
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

int dropdown_bit_depth_lock = 0;
void drawDropdowns() {
    // BIT DEPTH DROPDOWN
    if(GuiDropdownBox((Rectangle){0, 0, 125*scale, 25*scale}, "8bpp (256 colors);4bpp (16 colors);2bpp (4 colors)", (int*)&color_depth, dropdown_bit_depth_lock)) dropdown_bit_depth_lock = !dropdown_bit_depth_lock;
}

