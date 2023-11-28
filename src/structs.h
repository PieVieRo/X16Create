#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int width;
    int height;
    int color_data[16 * 16];
} Tile;

typedef Color Palette[256];

#endif
