version = RAYGUI_IMPLEMENTATION;
import raylib;
import raygui;

import globals;

import palette;
import drawing;

int main()
{
    const(int) screen_width  = 1280;
    const(int) screen_height = 720;

    InitWindow(screen_width, screen_height, "X16Create");
    SetWindowState(ConfigFlags.FLAG_WINDOW_RESIZABLE);

    current_palette = default_palette;

    SetTargetFPS(60);
    scope (exit)
        CloseWindow();

    while(!WindowShouldClose()) {
        if(IsWindowResized()) {
            updateScale();
        }
        
        inputLoop();

        BeginDrawing();
        ClearBackground(Color(0x18, 0x18, 0x18, 0xFF));
        drawingLoop();
        EndDrawing();
    }
    return 0;
}
