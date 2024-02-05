import std.stdio;
import core.stdc.stdlib : exit;
import std.conv : to;

import globals;

public int getCurrentPaletteRow(ubyte current_color) {
    return current_color / 16;
}

public ubyte getPaletteIndex(ubyte idx, ubyte current_depth, ubyte current_color) {
    with(depth) {
        switch(current_depth) {
            case eight_bpp:
                break;
            case four_bpp:
                idx = ((idx % 16) + 16 * getCurrentPaletteRow(current_color)).to!ubyte;
                if(idx % 16 == 0)
                    idx = 0;
                break;
            case two_bpp:
                idx = ((idx % 4) + 16 * getCurrentPaletteRow(current_color)).to!ubyte;
                if(idx % 16 == 0)
                    idx = 0;
                break;
            default:
                stderr.writefln("[ERROR] unknown bit depth %s", current_depth);
                exit(1);
        }
    }
    return idx;
}
