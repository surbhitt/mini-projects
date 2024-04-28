

// #define _UNICODE
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <string>
#include "ConsoleGameEngine.h"
#include <windows.h>
#include <thread>
#include <chrono>
//#pragma comment(lib, "user32.lib")

class GameOfLife: public ConsoleGameEngine {

private:
    int* m_CurrentGen;
    int*m_NextGen;
    int m_nPathWidth, m_nGenCount;
    int m_nGridWidth, m_nGridHeight;
    int m_nAlive, m_nDead;

public:
    GameOfLife () {
        m_sAppName = L"Conway's Game Of Life";
        m_nGridHeight = 20;
        m_nGridWidth = 20;
        m_nGenCount = 0;
    }

protected: 
    void UpdateState() {

        m_nAlive = 0;
        m_nDead = 0;

        for (int x = 0; x < m_nGridWidth; ++x) {
            for (int y = 0; y < m_nGridHeight; ++y) {
                int nActiveNeighbours = 0;
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        int dx = (x + i + m_nGridWidth) % m_nGridWidth;
                        int dy = (y + j + m_nGridHeight) % m_nGridHeight;
                        if (dx < m_nGridWidth && dx >= 0 && dy < m_nGridHeight && dy >= 0)
                            if (m_CurrentGen[dy * m_nGridWidth + dx])
                                nActiveNeighbours++;
                    }
                }

                int nCurrentState = m_CurrentGen[y * m_nGridWidth + x];
                int nNextState = m_CurrentGen[y * m_nGridWidth + x];
                if ( nCurrentState == 0 && nActiveNeighbours == 3) {
                   nNextState = 1;
                }
                else if (nCurrentState == 1 && (nActiveNeighbours < 2 || nActiveNeighbours > 3)) {
                   nNextState = 0;
                }
                if (nNextState) m_nAlive++;
                
                m_NextGen[y * m_nGridWidth + x] = nNextState;
                
            }
            m_nDead = (m_nGridHeight * m_nGridWidth) - m_nAlive;
        }

        for (int x = 0; x < m_nGridWidth; ++x) {
            for (int y = 0; y < m_nGridHeight; ++y) {
                m_CurrentGen[y * m_nGridWidth + x] =m_NextGen[y * m_nGridWidth + x];
            }
        }

        memset(m_NextGen, 0, m_nGridWidth * m_nGridHeight * sizeof(int));
    }

    void DrawBoundary () {
        return;
    }

    bool OnUserCreate () {
        
        m_CurrentGen = new int[m_nGridWidth * m_nGridHeight];
        m_nPathWidth = 3;

       m_NextGen = new int[m_nGridWidth * m_nGridHeight];
        memset(m_NextGen, 0, m_nGridWidth * m_nGridHeight * sizeof(int));
        
        for (int i = 0; i < m_nGridWidth * m_nGridHeight; ++i) {
            m_CurrentGen[i] = rand()%2 ? 1: 0;
        }

        return true;  
    } 

    bool OnUserUpdate (float fElapsedTime) {
        m_nGenCount++;
        Fill(0, 0, m_nScreenHeight, m_nScreenWidth, L' ');
        // DrawBoundary();
        // strings to be drawn
        DrawString(3, 5, L"   _____                               __   _      _  __", FG_CYAN);
        DrawString(3, 6, L"  / ____|                             / _| | |    (_)/ _|", FG_CYAN);
        DrawString(3, 7, L" | |  __  __ _ _ __ ___   ___    ___ | |_  | |     _| |_ ___", FG_CYAN);
        DrawString(3, 8, L" | | |_ |/ _` | '_ ` _ \\ / _ \\  / _ \\|  _| | |    | |  _/ _ \\", FG_CYAN);
        DrawString(3, 9, L" | |__| | (_| | | | | | |  __/ | (_) | |   | |____| | ||  __/", FG_CYAN);
        DrawString(3,10, L"  \\_____|\\__,_|_| |_| |_|\\___|  \\___/|_|   |______|_|_| \\___|", FG_CYAN);

        std::wstring wstr_Generation = L"Generation : ";
        wstr_Generation += std::to_wstring(m_nGenCount);
        std::wstring wstr_Alive = L"Alive : ";
        wstr_Alive += std::to_wstring(m_nAlive);
        std::wstring wstr_Dead = L"Dead : ";
        wstr_Dead += std::to_wstring(m_nDead);
        DrawString(100, 20, wstr_Generation);
        DrawString(100, 22, wstr_Alive);
        DrawString(100, 24, wstr_Dead);

        // DrawString(5, 5, L"CONWAYS GAME OF LIFE ^~^");
        
        for (int x = 0; x < m_nGridWidth; x++) {
            for (int y = 0; y < m_nGridHeight; y++) {
                for (int dx = 0; dx < m_nPathWidth; dx++) {
                    for (int dy = 0; dy < m_nPathWidth; dy++) {
                        if (m_CurrentGen[y*m_nGridWidth+x])
                            Draw(x*(m_nPathWidth+1)+dx+5, y*(m_nPathWidth+1)+dy+15, PIXEL_SOLID, FG_GREEN);
                        else
                            Draw(x*(m_nPathWidth+1)+dx+5, y*(m_nPathWidth+1)+dy+15, PIXEL_SOLID, FG_RED);

                    }
                }
            } 
        }

        // getch();
        
        UpdateState();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (GetAsyncKeyState('Q') & 0x8000) {
            return false;
        }
        return true;
    }
};

int main (int argc, char* argv[]) {
    
    GameOfLife gol;
    gol.ConstructConsole(160, 100, 6, 6);
    gol.Start();

    return 0;
}
