#include <iostream>
#include "ConsoleGameEngine.h"

class Example : public ConsoleGameEngine {
public:
    Example() {

    }

    virtual bool OnUserCreate() {
        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime) {
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

        for (int c = 0; c < 16; c++) {
            Fill(0, c * 6, 5, c * 6 + 5, PIXEL_QUARTER, c);
            Fill(6, c * 6, 11, c * 6 + 5, PIXEL_HALF, c);
            Fill(12, c * 6, 17, c * 6 + 5, PIXEL_THREEQUARTERS, c);
            Fill(18, c * 6, 23, c * 6 + 5, PIXEL_SOLID, c);
            Fill(24, c * 6, 29, c * 6 + 5, PIXEL_THREEQUARTERS, c | BG_WHITE);
            Fill(30, c * 6, 35, c * 6 + 5, PIXEL_HALF, c | BG_WHITE);
            Fill(36, c * 6, 41, c * 6 + 5, PIXEL_QUARTER, c | BG_WHITE);

        }

        return true;
    }
};

int main() {

    Example demo;
    demo.ConstructConsole(160, 100, 8, 8);
    demo.Start();

    return 0;
}