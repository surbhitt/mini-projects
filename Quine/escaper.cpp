/*
 * Helper for the q.cpp
 * Outputs the source code of q.cpp with all escaped literals
 * Usage: ./escaper 
 *
 */

#include <fstream>
#include <iostream>
using namespace std;

int main() {
    fstream f;
    f.open("q.cpp", ios::in);
    char c;
    while (f.get(c)) {
        switch (c) {
        case '\n':
            cout << "\\n";
            break;
        case '\"':
            cout << "\\\"";
            break;
        case '\\':
            cout << "\\\\";
            break;
        default:
            cout << c;
        }
    }
}
