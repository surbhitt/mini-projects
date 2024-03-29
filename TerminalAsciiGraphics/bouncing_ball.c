
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define WIDTH 80
#define HEIGHT 40
#define FPS 20
#define RADIUS WIDTH/8.0f
#define GRAVITY 200.0f
// have to scale time too acc to the fps
#define DT 1.0f/FPS
#define DAMPER 0.70f

typedef struct {
    float x, y;
} vec;

vec vec_add(vec vec1, vec vec2) {
    vec tmp;
    tmp.x = vec1.x+vec2.x;
    tmp.y = vec1.y+vec2.y;
    return tmp;
}

vec vec_mul(vec vec1, vec vec2) {
    vec tmp;
    tmp.x = vec1.x*vec2.x;
    tmp.y = vec1.y*vec2.y;
    return tmp;
}

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
    vec pos = {-RADIUS, -RADIUS};
    vec vel = {0.0f, 50.0f}; // due to the inversion of the widht and height
    vec gravity = {GRAVITY, 0.0f}; 
    vec dt = {DT,DT};
    while (true) {
        reset_buffer();
        draw_circle(pos.x, pos.y, RADIUS);
        draw_buffer();
        vel = vec_add(vel, vec_mul(gravity, dt));
        pos = vec_add(pos, vec_mul(vel, dt));
        if (pos.x > HEIGHT - RADIUS) { 
            pos.x = HEIGHT - RADIUS;
            vel.x *= -DAMPER; 
        }
        if (pos.y >= WIDTH + RADIUS + RADIUS*0.5f) {
            pos.x=-RADIUS; pos.y=-RADIUS;
            vel.x=0.0f; vel.y=50.0f; 
        }
        usleep(1000*1000 / FPS); 
        reset_cursor();
    }
    return 0;
}
