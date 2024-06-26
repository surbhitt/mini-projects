#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "header/stb_image_resize.h"

// hsl table to be generated using the rgb values
int hsl256[256][3];
/*= {
    {0, 0, 0},
    {0, 100, 25},
    {120, 100, 25},
    {60, 100, 25},
    {240, 100, 25},
    {300, 100, 25},
    {180, 100, 25},
    {0, 0, 75},
    {0, 0, 50},
    {0, 100, 50},
    {120, 100, 50},
    {60, 100, 50},
    {240, 100, 50},
    {300, 100, 50},
    {180, 100, 50},
    {0, 0, 100},
    {0, 0, 0},
    {240, 99, 18},
    {240, 100, 26},
    {240, 100, 34},
    {240, 100, 42},
    {240, 100, 50},
    {120, 99, 18},
    {180, 99, 18},
    {197, 100, 26},
    {207, 100, 34},
    {213, 100, 42},
    {217, 100, 50},
    {120, 100, 26},
    {162, 100, 26},
    {180, 100, 26},
    {193, 100, 34},
    {202, 100, 42},
    {208, 100, 50},
    {120, 100, 34},
    {152, 100, 34},
    {166, 100, 34},
    {180, 100, 34},
    {191, 100, 42},
    {198, 100, 50},
    {120, 100, 42},
    {146, 100, 42},
    {157, 100, 42},
    {168, 100, 42},
    {180, 100, 42},
    {189, 100, 50},
    {120, 100, 50},
    {142, 100, 50},
    {151, 100, 50},
    {161, 100, 50},
    {170, 100, 50},
    {180, 100, 50},
    {0, 99, 18},
    {300, 99, 18},
    {282, 100, 26},
    {272, 100, 34},
    {266, 100, 42},
    {262, 100, 50},
    {60, 99, 18},
    {0, 0, 37},
    {240, 17, 45},
    {240, 33, 52},
    {240, 60, 60},
    {240, 100, 68},
    {77, 100, 26},
    {120, 17, 45},
    {180, 17, 45},
    {210, 33, 52},
    {220, 60, 60},
    {225, 100, 68},
    {87, 100, 34},
    {120, 33, 52},
    {150, 33, 52},
    {180, 33, 52},
    {200, 60, 60},
    {210, 100, 68},
    {93, 100, 42},
    {120, 60, 60},
    {140, 60, 60},
    {160, 60, 60},
    {180, 60, 60},
    {195, 100, 68},
    {97, 100, 50},
    {120, 100, 68},
    {135, 100, 68},
    {150, 100, 68},
    {165, 100, 68},
    {180, 100, 68},
    {0, 100, 26},
    {317, 100, 26},
    {300, 100, 26},
    {286, 100, 34},
    {277, 100, 42},
    {271, 100, 50},
    {42, 100, 26},
    {0, 17, 45},
    {300, 17, 45},
    {270, 33, 52},
    {260, 60, 60},
    {255, 100, 68},
    {60, 100, 26},
    {60, 17, 45},
    {0, 0, 52},
    {240, 20, 60},
    {240, 50, 68},
    {240, 100, 76},
    {73, 100, 34},
    {90, 33, 52},
    {120, 20, 60},
    {180, 20, 60},
    {210, 50, 68},
    {220, 100, 76},
    {82, 100, 42},
    {100, 60, 60},
    {120, 50, 68},
    {150, 50, 68},
    {180, 50, 68},
    {200, 100, 76},
    {88, 100, 50},
    {105, 100, 68},
    {120, 100, 76},
    {140, 100, 76},
    {160, 100, 76},
    {180, 100, 76},
    {0, 100, 34},
    {327, 100, 34},
    {313, 100, 34},
    {300, 100, 34},
    {288, 100, 42},
    {281, 100, 50},
    {32, 100, 34},
    {0, 33, 52},
    {330, 33, 52},
    {300, 33, 52},
    {280, 60, 60},
    {270, 100, 68},
    {46, 100, 34},
    {30, 33, 52},
    {0, 20, 60},
    {300, 20, 60},
    {270, 50, 68},
    {260, 100, 76},
    {60, 100, 34},
    {60, 33, 52},
    {60, 20, 60},
    {0, 0, 68},
    {240, 33, 76},
    {240, 100, 84},
    {71, 100, 42},
    {80, 60, 60},
    {90, 50, 68},
    {120, 33, 76},
    {180, 33, 76},
    {210, 100, 84},
    {78, 100, 50},
    {90, 100, 68},
    {100, 100, 76},
    {120, 100, 84},
    {150, 100, 84},
    {180, 100, 84},
    {0, 100, 42},
    {333, 100, 42},
    {322, 100, 42},
    {311, 100, 42},
    {300, 100, 42},
    {290, 100, 50},
    {26, 100, 42},
    {0, 60, 60},
    {340, 60, 60},
    {320, 60, 60},
    {300, 60, 60},
    {285, 100, 68},
    {37, 100, 42},
    {20, 60, 60},
    {0, 50, 68},
    {330, 50, 68},
    {300, 50, 68},
    {280, 100, 76},
    {48, 100, 42},
    {40, 60, 60},
    {30, 50, 68},
    {0, 33, 76},
    {300, 33, 76},
    {270, 100, 84},
    {60, 100, 42},
    {60, 60, 60},
    {60, 50, 68},
    {60, 33, 76},
    {0, 0, 84},
    {240, 100, 92},
    {69, 100, 50},
    {75, 100, 68},
    {80, 100, 76},
    {90, 100, 84},
    {120, 100, 92},
    {180, 100, 92},
    {0, 100, 50},
    {337, 100, 50},
    {328, 100, 50},
    {318, 100, 50},
    {309, 100, 50},
    {300, 100, 50},
    {22, 100, 50},
    {0, 100, 68},
    {345, 100, 68},
    {330, 100, 68},
    {315, 100, 68},
    {300, 100, 68},
    {31, 100, 50},
    {15, 100, 68},
    {0, 100, 76},
    {340, 100, 76},
    {320, 100, 76},
    {300, 100, 76},
    {41, 100, 50},
    {30, 100, 68},
    {20, 100, 76},
    {0, 100, 84},
    {330, 100, 84},
    {300, 100, 84},
    {50, 100, 50},
    {45, 100, 68},
    {40, 100, 76},
    {30, 100, 84},
    {0, 100, 92},
    {300, 100, 92},
    {60, 100, 50},
    {60, 100, 68},
    {60, 100, 76},
    {60, 100, 84},
    {60, 100, 92},
    {0, 0, 100},
    {0, 0, 3},
    {0, 0, 7},
    {0, 0, 10},
    {0, 0, 14},
    {0, 0, 18},
    {0, 0, 22},
    {0, 0, 26},
    {0, 0, 30},
    {0, 0, 34},
    {0, 0, 38},
    {0, 0, 42},
    {0, 0, 46},
    {0, 0, 50},
    {0, 0, 54},
    {0, 0, 58},
    {0, 0, 61},
    {0, 0, 65},
    {0, 0, 69},
    {0, 0, 73},
    {0, 0, 77},
    {0, 0, 81},
    {0, 0, 85},
    {0, 0, 89},
    {0, 0, 93},
};*/

// rgb table
int rgb256[][3] = {
    {0, 0, 0},       {128, 0, 0},     {0, 128, 0},     {128, 128, 0},
    {0, 0, 128},     {128, 0, 128},   {0, 128, 128},   {192, 192, 192},
    {128, 128, 128}, {255, 0, 0},     {0, 255, 0},     {255, 255, 0},
    {0, 0, 255},     {255, 0, 255},   {0, 255, 255},   {255, 255, 255},
    {0, 0, 0},       {0, 0, 95},      {0, 0, 135},     {0, 0, 175},
    {0, 0, 215},     {0, 0, 255},     {0, 95, 0},      {0, 95, 95},
    {0, 95, 135},    {0, 95, 175},    {0, 95, 215},    {0, 95, 255},
    {0, 135, 0},     {0, 135, 95},    {0, 135, 135},   {0, 135, 175},
    {0, 135, 215},   {0, 135, 255},   {0, 175, 0},     {0, 175, 95},
    {0, 175, 135},   {0, 175, 175},   {0, 175, 215},   {0, 175, 255},
    {0, 215, 0},     {0, 215, 95},    {0, 215, 135},   {0, 215, 175},
    {0, 215, 215},   {0, 215, 255},   {0, 255, 0},     {0, 255, 95},
    {0, 255, 135},   {0, 255, 175},   {0, 255, 215},   {0, 255, 255},
    {95, 0, 0},      {95, 0, 95},     {95, 0, 135},    {95, 0, 175},
    {95, 0, 215},    {95, 0, 255},    {95, 95, 0},     {95, 95, 95},
    {95, 95, 135},   {95, 95, 175},   {95, 95, 215},   {95, 95, 255},
    {95, 135, 0},    {95, 135, 95},   {95, 135, 135},  {95, 135, 175},
    {95, 135, 215},  {95, 135, 255},  {95, 175, 0},    {95, 175, 95},
    {95, 175, 135},  {95, 175, 175},  {95, 175, 215},  {95, 175, 255},
    {95, 215, 0},    {95, 215, 95},   {95, 215, 135},  {95, 215, 175},
    {95, 215, 215},  {95, 215, 255},  {95, 255, 0},    {95, 255, 95},
    {95, 255, 135},  {95, 255, 175},  {95, 255, 215},  {95, 255, 255},
    {135, 0, 0},     {135, 0, 95},    {135, 0, 135},   {135, 0, 175},
    {135, 0, 215},   {135, 0, 255},   {135, 95, 0},    {135, 95, 95},
    {135, 95, 135},  {135, 95, 175},  {135, 95, 215},  {135, 95, 255},
    {135, 135, 0},   {135, 135, 95},  {135, 135, 135}, {135, 135, 175},
    {135, 135, 215}, {135, 135, 255}, {135, 175, 0},   {135, 175, 95},
    {135, 175, 135}, {135, 175, 175}, {135, 175, 215}, {135, 175, 255},
    {135, 215, 0},   {135, 215, 95},  {135, 215, 135}, {135, 215, 175},
    {135, 215, 215}, {135, 215, 255}, {135, 255, 0},   {135, 255, 95},
    {135, 255, 135}, {135, 255, 175}, {135, 255, 215}, {135, 255, 255},
    {175, 0, 0},     {175, 0, 95},    {175, 0, 135},   {175, 0, 175},
    {175, 0, 215},   {175, 0, 255},   {175, 95, 0},    {175, 95, 95},
    {175, 95, 135},  {175, 95, 175},  {175, 95, 215},  {175, 95, 255},
    {175, 135, 0},   {175, 135, 95},  {175, 135, 135}, {175, 135, 175},
    {175, 135, 215}, {175, 135, 255}, {175, 175, 0},   {175, 175, 95},
    {175, 175, 135}, {175, 175, 175}, {175, 175, 215}, {175, 175, 255},
    {175, 215, 0},   {175, 215, 95},  {175, 215, 135}, {175, 215, 175},
    {175, 215, 215}, {175, 215, 255}, {175, 255, 0},   {175, 255, 95},
    {175, 255, 135}, {175, 255, 175}, {175, 255, 215}, {175, 255, 255},
    {215, 0, 0},     {215, 0, 95},    {215, 0, 135},   {215, 0, 175},
    {215, 0, 215},   {215, 0, 255},   {215, 95, 0},    {215, 95, 95},
    {215, 95, 135},  {215, 95, 175},  {215, 95, 215},  {215, 95, 255},
    {215, 135, 0},   {215, 135, 95},  {215, 135, 135}, {215, 135, 175},
    {215, 135, 215}, {215, 135, 255}, {215, 175, 0},   {215, 175, 95},
    {215, 175, 135}, {215, 175, 175}, {215, 175, 215}, {215, 175, 255},
    {215, 215, 0},   {215, 215, 95},  {215, 215, 135}, {215, 215, 175},
    {215, 215, 215}, {215, 215, 255}, {215, 255, 0},   {215, 255, 95},
    {215, 255, 135}, {215, 255, 175}, {215, 255, 215}, {215, 255, 255},
    {255, 0, 0},     {255, 0, 95},    {255, 0, 135},   {255, 0, 175},
    {255, 0, 215},   {255, 0, 255},   {255, 95, 0},    {255, 95, 95},
    {255, 95, 135},  {255, 95, 175},  {255, 95, 215},  {255, 95, 255},
    {255, 135, 0},   {255, 135, 95},  {255, 135, 135}, {255, 135, 175},
    {255, 135, 215}, {255, 135, 255}, {255, 175, 0},   {255, 175, 95},
    {255, 175, 135}, {255, 175, 175}, {255, 175, 215}, {255, 175, 255},
    {255, 215, 0},   {255, 215, 95},  {255, 215, 135}, {255, 215, 175},
    {255, 215, 215}, {255, 215, 255}, {255, 255, 0},   {255, 255, 95},
    {255, 255, 135}, {255, 255, 175}, {255, 255, 215}, {255, 255, 255},
    {8, 8, 8},       {18, 18, 18},    {28, 28, 28},    {38, 38, 38},
    {48, 48, 48},    {58, 58, 58},    {68, 68, 68},    {78, 78, 78},
    {88, 88, 88},    {98, 98, 98},    {108, 108, 108}, {118, 118, 118},
    {128, 128, 128}, {138, 138, 138}, {148, 148, 148}, {158, 158, 158},
    {168, 168, 168}, {178, 178, 178}, {188, 188, 188}, {198, 198, 198},
    {208, 208, 208}, {218, 218, 218}, {228, 228, 228}, {238, 238, 238},
};

void rgb_to_hsl(int r, int g, int b, int *h, int *s, int *l) {
    // normalization; 0-255 => 0-1
    float r01 = r / 255.0f;
    float g01 = g / 255.0f;
    float b01 = b / 255.0f;
    // calculations
    float cmax = r01;
    cmax = g01 > cmax ? g01 : cmax;
    cmax = b01 > cmax ? b01 : cmax;
    float cmin = r01;
    cmin = g01 < cmin ? g01 : cmin;
    cmin = b01 < cmin ? b01 : cmin;
    float delta = cmax - cmin;
    float epsilon = 1e-6;
    float hf = 0;
    if (delta < epsilon)
        hf = 0;
    else if (cmax == r01)
        hf = 60.0f * fmod((g01 - b01) / delta, 6.0f);
    else if (cmax == g01)
        hf = 60.0f * ((b01 - r01) / delta + 2);
    else if (cmax == b01)
        hf = 60.0f * ((r01 - g01) / delta + 4);
    else
        assert(0 && "unreachable");

    float lf = (cmax + cmin) / 2;

    float sf = 0;
    if (delta < epsilon)
        sf = 0;
    else
        sf = delta / (1 - fabsf(2 * lf - 1));

    // converted int values from intermediate floats
    *h = fmodf(fmodf(hf, 360.0f) + 360.0f, 360.0f);
    *s = sf * 100.0f;
    *l = lf * 100.0f;
}

int distance_rgb256(int i, int r, int g, int b) {
    int dr = r - rgb256[i][0];
    int dg = g - rgb256[i][1];
    int db = b - rgb256[i][2];

    return dr * dr + dg * dg + db * db;
}

int find_ansi_index_by_rgb(int r, int g, int b) {
    int index = 0;
    int Dist = distance_rgb256(0, r, g, b);
    for (int i = 0; i < 256; i++) {
        int dist = distance_rgb256(i, r, g, b);
        if (dist < Dist) {
            index = i;
            Dist = dist;
        }
    }
    return index;
}

int distance_hsl256(int i, int h, int s, int l) {
    int dh = h - hsl256[i][0];
    int ds = s - hsl256[i][1];
    int dl = l - hsl256[i][2];

    return dh * dh + ds * ds + dl * dl;
}

int find_ansi_index_by_hsl(int h, int s, int l) {
    int index = 0;
    int Dist = distance_hsl256(0, h, s, l);
    for (int i = 0; i < 256; ++i) {
        int dist = distance_hsl256(i, h, s, l);
        if (dist < Dist) {
            index = i;
            Dist = dist;
        }
    }
    return index;
}

// truecolor supported by terminal; 16 million colors
// covering the entire 24-bit jpeg scope
// usage ::
// escape sequence creation : \e[${bg};2;{$r};${g};${b}m
// here ${bg} = 38
// \e () or \0x1b (hex) or \033 (oct) or 27 (dec)
// reset \e[0m
// printf("\0x1b")
// TODO: use the truecolors
// TODO: add option to render with rbg or hsl

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "[ERROR] no input provided\n");
        exit(1);
    }
    const char *file_path = argv[1];
    int width, height;
    uint32_t *pixels =
        (uint32_t *)stbi_load(file_path, &width, &height, NULL, 4);
    if (pixels == NULL) {
        fprintf(stderr, "[ERROR] file not able to load\n");
        exit(1);
    }

    int resized_width = 50;
    int resized_height = height * resized_width / width;

    uint32_t *resized_pixels =
        malloc(sizeof(uint32_t) * resized_width * resized_height);
    assert(resized_pixels != NULL);

    stbir_resize_uint8((const unsigned char *)pixels, width, height,
                       sizeof(uint32_t) * width,
                       (unsigned char *)resized_pixels, resized_width,
                       resized_height, sizeof(uint32_t) * resized_width, 4);

    for (int i = 0; i < 256; ++i) {
        rgb_to_hsl(rgb256[i][0], rgb256[i][1], rgb256[i][2], &hsl256[i][0],
                   &hsl256[i][1], &hsl256[i][2]);
    }

    for (int y = 0; y < resized_height; ++y) {
        for (int x = 0; x < resized_width; ++x) {
            uint32_t pixel = resized_pixels[y * resized_width + x];
            int r = (pixel >> 8 * 0) & 0xff;
            int g = (pixel >> 8 * 1) & 0xff;
            int b = (pixel >> 8 * 2) & 0xff;
            int a = (pixel >> 8 * 3) & 0xff;
            // some pixels have zero alpha but garbage rbg
            r = a * r / 255;
            g = a * g / 255;
            b = a * b / 255;
            int h, s, l;
            rgb_to_hsl(r, g, b, &h, &s, &l);
            printf("\e[48;5;%dm  ", find_ansi_index_by_hsl(h, s, l));
        }
        printf("\e[0m\n");
    }

#if 0
	for (int r=0;r<5;r++) {
		for (int g=0;g<5;g++) {	
			for (int b=0;b<5;b++) {
				printf("\e[48;5;%dm ", find_ansi_index_by_rgb(255*r/5, 255*g/5, 255*b/5));
			}
			printf("\e[0m\n");
		}
	}
#endif

    return 0;
}
