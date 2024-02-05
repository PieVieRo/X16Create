import std.stdio;
import core.stdc.stdlib : exit;
import std.conv : to;

import globals;
import tileset;

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

public void saveTileset(string filename, Tileset tileset, ubyte saving_depth) {
    File bin_file = File(filename, "w+");
    foreach(Tile tile; tileset.tiles) {
        for(ubyte i = 0; i < tileset.height; i++) {
            int start = i*16;
            int end = i*16 + tileset.width;
            import std.algorithm;
            ubyte[] tile_row = tile.color_data[start..end];
            switch(saving_depth) {
                case depth.eight_bpp:
                    bin_file.rawWrite(tile_row);
                    break;
                case depth.four_bpp:
                    // HACK: awful
                    // its 10.30 pm and its the best i could come up with
                    // i apologize to everyone who is about to read this...
                    foreach(idx, val; tile_row) {
                        tile_row[idx] = val%16;
                    }
                    ubyte[] reduced;
                    for(int idx = 0; idx < tile_row.length/2; idx+=2) {
                        reduced ~= to!ubyte((tile_row[idx] << 4) + tile_row[idx+1]);
                    }
                    bin_file.rawWrite(reduced);
                    break;
                case depth.two_bpp:
                    // HACK: awful
                    // ditto
                    foreach(idx, val; tile_row) {
                        tile_row[idx] = val%16;
                    }
                    ubyte[] reduced;
                    for(int idx = 0; idx < tile_row.length/2; idx+=4) {
                        reduced     ~= to!ubyte(tile_row[idx]   << 6);
                        reduced[idx] = to!ubyte(tile_row[idx+1] << 4);
                        reduced[idx] = to!ubyte(tile_row[idx+2] << 2);
                        reduced[idx] = to!ubyte(tile_row[idx+3]);
                    }
                    bin_file.rawWrite(reduced);
                    break;
                default:
                    stderr.writefln("[ERROR] unknown bit depth %s", saving_depth);
            }
        }
    }
    bin_file.close();
    writefln("[DEBUG] Wrote a %sx%s tileset!", tileset.width, tileset.height);
    return;
}

