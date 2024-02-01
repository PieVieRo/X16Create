import raylib;
import raygui;

import globals;

import palette;

// functions related to the Tile Mode
import tilemode;

const(int) padding = 10;

import std.algorithm.comparison : min, max;
public void updateScale() {
    screen_width  = GetScreenWidth();
    screen_height = GetScreenHeight();
    scale = min(screen_width / 1280.0, screen_height / 720.0);
    setTwoThirdsWidth();
}
public float scale = 1;
public float screen_width  = 1280;
public float screen_height = 720;

public float two_thirds_width = 1280*2/3;
public void setTwoThirdsWidth() {
    two_thirds_width = screen_width * 2 / 3;
}

public void inputLoop() {
    tileModeInputLoop();
}

public void drawingLoop() {
    drawTileMode();
}
