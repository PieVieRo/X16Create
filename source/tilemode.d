import std.string : toStringz;
import std.conv : to;
import std.format;
import core.stdc.math : sqrtf;

import raylib;
import raygui;

import globals;

import drawing;
import tile;

Vector2 palette_cell = Vector2(-1,-1);
Vector2 canvas_cell = Vector2(-1,-1);
ubyte current_color = 0;
Tile current_tile;

public void tileModeInputLoop() {
    with(MouseButton) {
        if(!Vector2Equals(palette_cell, Vector2(-1, -1))) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                current_color = (palette_cell.y * 16 + palette_cell.x).to!ubyte;
            }
        }
        if(!Vector2Equals(canvas_cell, Vector2(-1, -1))) {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                current_tile.color_data[(canvas_cell.y * 16 + canvas_cell.x).to!int] = current_color;
            }
        }
    }
}

public void drawTileMode() {
    drawRightSide();
    drawLeftSide();
}

private void drawLeftSide() {
    drawCanvas();
    drawDropdowns();
}

bool dropdown_depth_lock = 0;
private void drawDropdowns() {
    // DEPTH DROPDOWN
    if(GuiDropdownBox(
                Rectangle(0, 0, 125*scale, 25*scale), 
                toStringz("8bpp (256 colors);4bpp (16 colors);2bpp (4 colors)"),
                cast(int*)(&current_depth), dropdown_depth_lock
                )
            ) 
        dropdown_depth_lock = !dropdown_depth_lock;
}

private int calculatePixelOffset(int val) {
    return val/current_tile.width*16 + val%current_tile.width;
}
private void drawCanvas() {
    int canvas_size = (30 * scale).to!int;
    int grid_width = current_tile.width * canvas_size;
    int grid_height = current_tile.width * canvas_size;
    int grid_x = (two_thirds_width/2 - grid_width/2).to!int;
    int grid_y = (screen_height/2 - grid_height/2).to!int;
    for(int i=0; i < (current_tile.width * current_tile.height); i++) {
        int current_pixel_offset = calculatePixelOffset(i);
        DrawRectangle(grid_x + (i % current_tile.width * canvas_size), grid_y + ((i / current_tile.width) * canvas_size),
            canvas_size, canvas_size,
            current_palette[current_tile.color_data[current_pixel_offset]],
            );
    }
    canvas_cell = GuiGrid(Rectangle(grid_x, grid_y, grid_width, grid_height), toStringz(""), canvas_size, 1);
}

alias ui_element_func=int function(const(int));
private void draw_element(ref int drawing_height, ui_element_func func) {
    drawing_height += func(drawing_height) + padding;
}
private void drawRightSide() {
    const(ui_element_func)[] elements = [
        &drawPalette, 
        &drawInfo
    ];
    int drawing_height = (screen_height*0.01).to!int;
    foreach(ui_element_func element; elements) {
        draw_element(drawing_height, element);
    }
}

private int getCurrentPalette(ubyte current_color) {
    return current_color / 16;
}

private int drawPalette(const(int) drawing_height) {
    const(int) pixel_size = (15*scale).to!int;

    const(float) palette_grid_length = 16 * pixel_size;
    float palette_grid_x = (two_thirds_width + screen_width - palette_grid_length)/2;
    Rectangle palette_grid_rectangle = Rectangle(
            palette_grid_x,
            drawing_height + padding,
            palette_grid_length,
            palette_grid_length
            );

    Rectangle palette_group_box = Rectangle(
            palette_grid_x - padding,
            drawing_height,
            palette_grid_length + 2*padding,
            palette_grid_length + 2*padding,
            );
    
    if(current_depth != depth.eight_bpp) {
        const(int) triangle_side = pixel_size;
        const(float) triangle_height = (triangle_side * sqrtf(3))/2;
        const(float) grid_tri_padding  = padding / 2 * scale;
        Vector2[3] triangle_coords; 
        triangle_coords[0] = Vector2(
                palette_grid_x + palette_grid_length + grid_tri_padding,
                drawing_height + padding + (pixel_size/2) + (getCurrentPalette(current_color) * pixel_size),
                );
        triangle_coords[1] = Vector2(
                triangle_coords[0].x + triangle_height,
                drawing_height + padding + pixel_size + (getCurrentPalette(current_color) * pixel_size),
                );
        triangle_coords[2] = Vector2(
                triangle_coords[0].x + triangle_height,
                drawing_height + padding + (getCurrentPalette(current_color) * pixel_size),
                );
        DrawTriangle(triangle_coords[0], triangle_coords[1], triangle_coords[2], Colors.RAYWHITE);

        palette_group_box.width += grid_tri_padding + triangle_height;
    }

    GuiGroupBox(palette_group_box, "Palette");
    foreach(idx, Color color; current_palette) {
        DrawRectangle(((idx % 16 * pixel_size) + palette_grid_rectangle.x).to!int, ((idx / 16 * pixel_size) + palette_grid_rectangle.y).to!int,
                pixel_size, pixel_size, color);
    }
    palette_cell = GuiGrid(palette_grid_rectangle, toStringz(""), pixel_size, 1);
    return palette_group_box.height.to!int;
}

immutable(char)*[] current_depth_text = [
    "8bpp (256 colors)\0".ptr,
    "4bpp (16 colors)\0".ptr,
    "2bpp (4 colors)\0".ptr,
];
private int drawInfo(const(int) drawing_height) {
    int scaled_font_size = (font_size*scale).to!int;
    int scaled_padding = (padding*scale).to!int;
    int pixel_size = (100*scale).to!int;
    int color_x = ((two_thirds_width + screen_width - pixel_size)/2).to!int;
    int next_element_height = drawing_height + (padding*scale).to!int;
    immutable(char)* current_depth_string = current_depth_text[current_depth];
    DrawText(current_depth_string, color_x, next_element_height, scaled_font_size, font_color);
    int text_width = MeasureText(current_depth_string, scaled_font_size);
    next_element_height += scaled_font_size + scaled_padding;
    Rectangle color_rectangle = Rectangle(color_x, next_element_height, pixel_size, pixel_size);
    next_element_height += (color_rectangle.height + scaled_padding).to!int;
    Rectangle group_box_rectangle = Rectangle(
            color_rectangle.x - scaled_padding,
            drawing_height,
            (text_width > color_rectangle.width ? text_width : color_rectangle.width) + scaled_padding*2,
            next_element_height - drawing_height,
            );
    GuiGroupBox(group_box_rectangle, "Info");
    DrawRectangleRec(color_rectangle, current_palette[current_color]);
    return group_box_rectangle.height.to!int;
}
