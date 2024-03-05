// rope simulation using raylib

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"

#define FPS 60
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
float rad=20.0f;
Color bgcolor = {20,20,20,255};
#define KNOTS 10

bool checkIfCursorOnHead(Vector2 center, float rad, Vector2 mouse) {
   if ((mouse.x-center.x)*(mouse.x-center.x)+(mouse.y-center.y)*(mouse.y-center.y) <= rad*rad) return true;
   return false;
}

Vector2* generateKnots() {
    Vector2* it = (Vector2*)malloc(KNOTS*sizeof(Vector2));
    for (int i=0; i<KNOTS; ++i) { 
         Vector2 tmp = {rand()%(SCREEN_WIDTH-(int)rad), rand()%(SCREEN_HEIGHT-(int)rad)};
         *(it+i) = tmp;
    }
    return it;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "rope simulation");
    SetTargetFPS(FPS);
    Vector2 center = {(float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2};
    Vector2 mouse;
    bool cursorOnCircle;
    bool dragging = false;
    Vector2* knotsAt;
    knotsAt = generateKnots(); 
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bgcolor);
        DrawCircleV(center, rad, RED);
        /* for (int i=0; i<KNOTS; ++i) { */
        /*     DrawCircleV(*(knotsAt+i), rad, RED); */
        /* } */
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
        cursorOnCircle = checkIfCursorOnHead(center, rad, mouse);
        if (cursorOnCircle) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                dragging = true;
            }
            else dragging = false;
        }
        if (dragging) {
            // TODO: fix the circle moving to the cursor
            center.x = mouse.x;
            center.y = mouse.y;       
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
