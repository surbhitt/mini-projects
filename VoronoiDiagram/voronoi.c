/*
 * I'm walking alone, the streets are empty
 * The only thing I can see is my own silhouette
*/

//-------------------------------------- headers
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

//-------------------------------------- consts
#define WIDTH 800
#define HEIGHT 600
#define SEED_COUNT 10
#define OUT_FILE_NAME "out_voronoi.ppm"
#define DISPLAY_SEED true
#define BACKGROUND_COLOR COLOR_GREY
#define SEED_MARKER_RAD 5
#define SEED_MARKER_COL COLOR_WHITE

//-------------------------------------- colors
#define PALETTE_SIZE (sizeof(color_palette)/sizeof(color_palette[0]))
#define EXTRACT_R(pixel) ((pixel & 0x0000ff) >> 8*0)
#define EXTRACT_G(pixel) ((pixel & 0x00ff00) >> 8*1)
#define EXTRACT_B(pixel) ((pixel & 0xff0000) >> 8*2)

//-------------------------------------- colors
#define COLOR_WHITE     0xffffffff 
#define COLOR_BLACK     0xff000000 
#define COLOR_GREY      0xff181818 
#define COLOR_RED       0xff0000ff   
#define COLOR_GREEN     0xff00ff00 
#define COLOR_BLUE      0xffff0000  
#define BRIGHT_RED      0xff3449fb
#define BRIGHT_GREEN    0xff26bbb8
#define BRIGHT_YELLOW   0xff2fbdfa
#define BRIGHT_BLUE     0xff98a583
#define BRIGHT_PURPLE   0xff9b86d3
#define BRIGHT_AQUA     0xff7cc08e
#define BRIGHT_ORANGE   0xff1980fe
#define NEUTRAL_BLUE    0xff888545
#define NEUTRAL_PURPLE  0xff8662b1
#define NEUTRAL_AQUA    0xff6a9d68
 
//-------------------------------------- datatypes
typedef uint32_t color32; 
typedef struct{
    int x, y;
} point;

//-------------------------------------- statics
static color32 image[HEIGHT][WIDTH];
static point seeds[SEED_COUNT];
static color32 color_palette[] = {
    BRIGHT_RED, 
    BRIGHT_GREEN, 
    BRIGHT_YELLOW, 
    BRIGHT_BLUE, 
    NEUTRAL_BLUE, 
    BRIGHT_PURPLE, 
    NEUTRAL_PURPLE, 
    BRIGHT_AQUA, 
    NEUTRAL_AQUA,
    BRIGHT_ORANGE
}; 

//--------------------------------------- functions
// fill backgound color
void fill_color(color32 color){
    printf("[-] Filling background color to the image\n");
    for(size_t j=0; j<HEIGHT; ++j){
        for(size_t i=0; i<WIDTH; ++i)
           image[j][i] = color;                        
    }
}

// save image buffer to ppm  
void save_image_to_ppm(const char* filepath) {
    printf("[-] Saving image to file\n");
    FILE* image_file = fopen(filepath, "wb");
    // check: file opened successfully for write
    if (image_file==NULL) {
        fprintf(stderr, "ERROR: could not open %s: %s", filepath, strerror(errno));
        exit(1);
    }
    fprintf(image_file, "P6\n%d %d 255\n", WIDTH, HEIGHT); 
    for(size_t j=0; j< 600; ++j){
        for(size_t i=0; i< 800; ++i){
            color32 pixel = image[j][i];                        
            uint8_t bytes[3]={
                EXTRACT_R(pixel),
                EXTRACT_G(pixel),
                EXTRACT_B(pixel),
            };
            fwrite(bytes, sizeof(bytes), 1, image_file);
            // check: data written to fil without err
            assert(!ferror(image_file));

        }
    }
    // check: file closed successfully
    int ret_code = fclose(image_file);
    assert(ret_code == 0);
}

// generate random seeds
void seed_generation() {
    printf("[-] Generating seeds\n");
    for (int i=0; i<SEED_COUNT; ++i){
        seeds[i].x = rand()%WIDTH;
        seeds[i].y = rand()%HEIGHT;
    }
}

// fill circles on image buffer
void fill_circle(int cx, int cy, int rad, color32 color) {
    int x0=cx-rad;
    int x1=cx+rad;
    int y0=cy-rad;
    int y1=cy+rad;
    for (int i=x0; i<=x1; ++i) {
        if (0<=i && WIDTH>i) {
            for (int j=y0; j<=y1; ++j) {    
                if (0<=j && HEIGHT>j) {
                    int dx = cx-i; 
                    int dy = cy-j;
                    if ((dx*dx + dy*dy) <= rad*rad)
                        image[j][i]=color;
            
                }
            }
        }
    }
}

// euclidean norm
int euclidean_norm(int pi, int pj, int sx, int sy){
    /* printf("\t(using euclidean norm)\n"); */
    int dx = pi-sx;
    int dy = pj-sy;
    return dx*dx+dy*dy;
}

// manhattan norm
int manhattan_norm(int pi, int pj, int sx, int sy){
    return abs(pi-sx)+abs(pj-sy);
}
void assign_color() {
    printf("- assigning color\n");
    for (size_t j=0; j<HEIGHT; ++j) {
        for (size_t i=0; i<WIDTH; ++i) {
            int cur_seed = 0;
            /* int cur_min_dist = euclidean_norm(i, j, seeds[cur_seed].x, seeds[cur_seed].y); */ 
            int cur_min_dist = manhattan_norm(i, j, seeds[cur_seed].x, seeds[cur_seed].y); 
            for (int k=1; k<SEED_COUNT; ++k) {
                /* int min_dist = euclidean_norm(i, j, seeds[k].x, seeds[k].y); */  
                int min_dist = manhattan_norm(i, j, seeds[k].x, seeds[k].y);  
                if (min_dist < cur_min_dist) {
                    cur_seed = k;
                    cur_min_dist = min_dist;
                } 
            }
            image[j][i] = color_palette[cur_seed%PALETTE_SIZE];
        }
    }
}

int main(void) {
    srand(time(0));
    /* fill_color(BACKGROUND_COLOR); */
    seed_generation();
    assign_color();
    for(int i=0;i<SEED_COUNT;++i) {
        printf("seed.x %d seed.y %d\n", seeds[i].x, seeds[i].y);
        /* fill_circle(seeds[i].x, seeds[i].y, SEED_MARKER_RAD, SEED_MARKER_COL); */
    }
    save_image_to_ppm(OUT_FILE_NAME);
    return 0;
}
