#include "raylib.h"

int main() {
    const int ScreenWidth = 600;
    const int ScreenHeight = 400;
    InitWindow(ScreenWidth, ScreenHeight, "a window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("HEllo world", 10, 100, 10, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
