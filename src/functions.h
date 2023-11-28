#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

void drawPalette(Palette palette, Vector2* palette_cell);

void drawCanvas(Tile* tile, Palette palette, int canvas_size, Vector2* canvas_cell);

void handleInput(int* current_color, Tile* tile, Vector2* palette_cell, Vector2* canvas_cell);

#endif

