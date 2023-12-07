#ifndef STRUCTS_H
#define STRUCTS_H

#include <raylib.h>

typedef struct {
    int width;
    int height;
    int color_data[16 * 16];
} Tile;

typedef Color Palette[256];

enum Color_depth {
    EIGHT_BPP,
    FOUR_BPP,
    TWO_BPP,
};

#endif
