#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


typedef struct {
    int pixels;
    int pixels_size;
} Sprite;

int main() {
    int screen_width = 1280;
    int screen_height = 720;
    InitWindow(screen_width, screen_height, "X16Create");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    Sprite sprite = { 8, 25 };
    while(!WindowShouldClose()) {
        if(IsWindowResized()) {
            screen_width = GetScreenWidth();
            screen_height = GetScreenHeight();
        }
        BeginDrawing();
        ClearBackground((Color) {0x18, 0x18, 0x18});

        Vector2 mouse_cell = { 0 };
        int two_thirds_width = screen_width - screen_width/3;
        int grid_size = sprite.pixels * sprite.pixels_size;
        GuiGrid((Rectangle) { two_thirds_width/2 - grid_size/2 , screen_height / 2 - 100,  grid_size, grid_size }, "", sprite.pixels_size, 1, &mouse_cell);
        GuiGroupBox((Rectangle) { two_thirds_width, screen_height * 0.01, 16*4 + 18*2 + 10, 16*4 + 18*2 + 10 }, "Palette");
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
