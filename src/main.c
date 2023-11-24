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
        GuiGrid((Rectangle) { screen_width * 0.0010, screen_height / 2 - 100,  sprite.pixels * sprite.pixels_size, sprite.pixels * sprite.pixels_size}, "", sprite.pixels_size, 1, &mouse_cell);
        GuiGroupBox((Rectangle) {screen_width - screen_width/3, screen_height * 0.01, 16*4 + 18*2 + 10, 16*4 + 18*2 + 10}, "jebac igora");
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
