#ifndef DRAWING_H
#define DRAWING_H

#include "structs.h"

void handleDrawing(int* current_color, Tile* tile, Vector2* palette_cell, Vector2* canvas_cell);

void drawRightSide(Palette palette, Vector2* palette_cell, int current_color);

void drawLeftSide(Tile* tile, Palette palette, int canvas_size, Vector2* canvas_cell);

#endif

