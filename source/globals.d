import raylib;

import palette;

public enum depth {
    eight_bpp,
    four_bpp,
    two_bpp,
};
public ubyte current_depth = depth.eight_bpp;
public Palette current_palette;


public const(int)   font_size = 10;
public const(Color) font_color = Color(0x8C, 0xAC, 0xB4, 0xFF);
