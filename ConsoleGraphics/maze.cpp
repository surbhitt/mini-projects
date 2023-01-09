/* 
A maze designer using the recursive backtracker and the ConsoleGameEngine.h 
*/

#include <iostream>
#include <stack>
#include "ConsoleGameEngine.h"

class Maze: public ConsoleGameEngine{
public:
    Maze(){
        m_sAppName = L"MAZE";
    }

private:
    // dimensions of the maze
    int m_nMazeWidth;
    int m_nMazeHeight;            
    // 1D array with values indicating what neighbours it is connected to
    int* m_maze;
    // enum with vals for the m_maze
    enum {
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED = 0x010,
    };
    // the number of cells visited
    int m_nVisitedCells;
    std::stack<std::pair<int,int>> m_stack;
    int m_nPathWidth;

protected:
    bool OnUserCreate(){
        
        // Maze parameters
        m_nMazeWidth = 40;
        m_nMazeHeight = 25;
        // dynamically allocating array
        m_maze = new int[m_nMazeHeight*m_nMazeWidth];
        // initiating with 0
        memset(m_maze, 0x00, m_nMazeHeight*m_nMazeWidth*sizeof(int));
        m_stack.push(std::make_pair(0,0));
        m_maze[0] = CELL_VISITED;
        m_nVisitedCells = 1;
        m_nPathWidth = 3;
        return true;
    }

    bool OnUserUpdate(float fElapsedTime){

        auto offset = [&](int x, int y) {
            return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
        };
        // Maze algorithm
        if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
            
            // creating a set of the unvisited neighbours
            std::vector<int> neighbours;
            // north neighbour
            if (m_stack.top().second > 0 && ((m_maze[offset(0,-1)] & CELL_VISITED) == 0)) {
                neighbours.push_back(0);
            }
            // east neighbour
            if (m_stack.top().first < m_nMazeWidth-1 && ((m_maze[offset(1, 0)] & CELL_VISITED) == 0)) {
                neighbours.push_back(1);
            }
            // south neighbour
            if (m_stack.top().second < m_nMazeHeight-1 && ((m_maze[offset(0, 1)] & CELL_VISITED) == 0)) {
                neighbours.push_back(2);
            }
            // west neighbour
            if (m_stack.top().first > 0 && ((m_maze[offset(-1, 0)] & CELL_VISITED) == 0)) {
                neighbours.push_back(3);
            }

            // check if the stack is empty
            if (!neighbours.empty()) {
                int next_cell_dir = neighbours[rand() % neighbours.size()];
                switch (next_cell_dir) {
                case 0: // North
                    m_maze[offset(0, 0)] |= CELL_PATH_N;
                    m_maze[offset(0, -1)] |= CELL_PATH_S;
                    m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
                    break;
                case 1: // East
                    m_maze[offset(0, 0)] |= CELL_PATH_E;
                    m_maze[offset(1, 0)] |= CELL_PATH_W;
                    m_stack.push(std::make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
                    break;
                case 2: // South
                    m_maze[offset(0, 0)] |= CELL_PATH_S;
                    m_maze[offset(0, 1)] |= CELL_PATH_N;
                    m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
                    break;
                case 3: // West
                    m_maze[offset(0, 0)] |= CELL_PATH_W;
                    m_maze[offset(-1, 0)] |= CELL_PATH_E;
                    m_stack.push(std::make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
                    break;
                }
                // new cell 
                m_maze[offset(0, 0)] |= CELL_VISITED;
                m_nVisitedCells += 1;
            }            
            else {
                m_stack.pop();
            }
            
        }

        // clear screen
        Fill(0,0,m_nScreenHeight, m_nScreenWidth, L' ');
        // draw maze
        for (int x = 0 ; x < m_nMazeWidth ; x++){
            for (int y = 0 ; y < m_nMazeHeight ; y++){
                //  for filling in all the char cells on the console that are in the range
                for (int py = 0; py < m_nPathWidth; py++) {
                    for (int px = 0; px < m_nPathWidth; px++) {
                        /*  the(m_nPathWidth + 1) multiple moves the point m_nPathWidth + 1 cells ahead
                        the filling is only for the range m_nPathWidth and the + 1th column and row
                        is not filled leavind the +1th row or col empty effectively which can be
                        treated as a wall */
                        if (m_maze[y * m_nMazeWidth + x] & CELL_VISITED)
                            Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, PIXEL_SOLID, FG_WHITE);
                        else
                            Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, PIXEL_SOLID, FG_BLUE);
                    }
                }
                // drawing the walls
                for (int p = 0; p < m_nPathWidth; p++) {
                    if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)
                        Draw(x * (m_nPathWidth + 1) + p, y * (m_nPathWidth + 1) + m_nPathWidth);
                    if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)
                        Draw(x * (m_nPathWidth + 1) + m_nPathWidth, y * (m_nPathWidth + 1) + p);
                }
                
            }
        }

        for (int py = 0; py < m_nPathWidth; py++) {
            for (int px = 0; px < m_nPathWidth; px++) {
                Draw(m_stack.top().first * (m_nPathWidth + 1) + px, m_stack.top().second * (m_nPathWidth + 1) + py, 0x2588, FG_GREEN);
            }
        }

        // mark the first and the last cell start and end of the maze
        if (m_nVisitedCells == m_nMazeWidth * m_nMazeHeight) {
            for (int py = 0; py < m_nPathWidth; py++) {
                for (int px = 0; px < m_nPathWidth; px++) {
                    Draw(0 * (m_nPathWidth + 1) + px, 0 * (m_nPathWidth + 1) + py, 0x2588, FG_MAGENTA);
                }
            }
            for (int py = 0; py < m_nPathWidth; py++) {
                for (int px = 0; px < m_nPathWidth; px++) {
                    Draw(((m_nMazeWidth * m_nMazeHeight) -1) * (m_nPathWidth + 1) + px, ((m_nMazeWidth * m_nMazeHeight) - 1) * (m_nPathWidth + 1) + py, 0x2588, FG_MAGENTA);
                }
            }
        }
        return true;
    }

};

int main(){
    Maze maze;
    maze.ConstructConsole(160, 100, 6, 6);
    maze.Start();
    return 0;
}