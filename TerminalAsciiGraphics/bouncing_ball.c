
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 40
#define FPS 20
#define RADIUS WIDTH/8

int buffer[HEIGHT][WIDTH];

void reset_buffer() {
    for (int i=0; i<HEIGHT; ++i) {
        for (int j=0; j<WIDTH; ++j) {
            buffer[i][j]=0;
        }
    }
} 

void draw_circle(int x, int y, int rad) {
    int x_beg = x-rad < 0 ? 0 : x-rad;
    int y_beg = y-rad < 0 ? 0 : y-rad;
    int x_end = x+rad > HEIGHT ? HEIGHT - 1 : x+rad;
    int y_end = y+rad > WIDTH ? WIDTH - 1 : y+rad;
    for (int i=x_beg; i<x_end+1; i++) {
        for (int j=y_beg; j<y_end+1; ++j) {
            if ((x-i)*(x-i) + (y-j)*(y-j) <= rad*rad) {
                buffer[i][j] = 1;
            }
        }
    }
}

void draw_buffer() {
    // reset to the top of the screen
    for (int i=0; i<HEIGHT; i+=2) {
        for (int j=0; j<WIDTH; ++j) {
            if (buffer[i][j] == 0 && buffer[i+1][j] == 0) printf(" ");
            else if (buffer[i][j] == 0 && buffer[i+1][j] == 1) printf(".");
            else if (buffer[i][j] == 1 && buffer[i+1][j] == 1) printf("@");
            else if (buffer[i][j] == 1 && buffer[i+1][j] == 0) printf("`");
        }
        printf("\n");
    }
}

void reset_cursor(void) {
        printf("\x1b[%dA", HEIGHT/2);
        printf("\x1b[%dD", WIDTH);
}

int main(void){
    for (int i=-RADIUS/2; i<HEIGHT+RADIUS/2+10;++i) {
        reset_buffer();
        draw_circle(i, WIDTH / 2, RADIUS);
        draw_buffer();
        usleep(1000*1000 / FPS); 
        reset_cursor();
    }
    return 0;
}
