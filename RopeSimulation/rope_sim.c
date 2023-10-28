// rope simulation using raylib

#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

bool checkIfCursorOnCircle(Vector2 center, float rad, Vector2 mouse) {
   if ((mouse.x-center.x)*(mouse.x-center.x)+(mouse.y-center.y)*(mouse.y-center.y) <= rad*rad) return true;
   return false;
}

int main(void) {
    const int screen_width=600;
    const int screen_height=400;
    InitWindow(screen_width, screen_height, "first window");
    SetTargetFPS(60);
    
    Vector2 center = {(float)screen_width/2, (float)screen_height/2};
    float rad = 50.0f;
    Vector2 mouse;
    bool cursorOnCircle;
    bool dragging = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(center, rad, RED);
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
        cursorOnCircle = checkIfCursorOnCircle(center, rad, mouse);
        if (cursorOnCircle) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                printf("clicked");
                dragging = true;
            }
            else dragging = false;
        }
        if (dragging) {
            center.x = mouse.x;
            center.y = mouse.y;       
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
