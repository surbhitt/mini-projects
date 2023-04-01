#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"

/****************
1) Load the image
2) Scale down the pixelchunk loaded:
		[.] take chunks of size sdf*sdf
		[.] average out the pixels 
		[.] store value in new array 
3) Convert the new array values to char
4)  .,*:o#@
5) putc

****************/

uint32_t *scaled_down(uint32_t *pixels) {
	return pixels;	
}


char table[] = ".,*:o#@";
size_t n = sizeof(table) - 1;
char color_to_char(uint32_t pixel) {
	int r = (pixel >> 8*0) & 0xff;	
	int g = (pixel >> 8*1) & 0xff;	
	int b = (pixel >> 8*2) & 0xff;
	
	size_t bright = r;
	if (bright < g) bright = g;
	if (bright < b) bright = b;
	// calculation : each ascii char corresponds to a range
	// if the brightness lies in that range the ascii char will be printed
	// there are int = 256/n intervals
	// the brightness will lie in brightness/int interval
	return table[bright*n/256];
}

int main(int argc, char** argv) {
	//printf("hello, subroza\n");
	
	if (argc < 2) {
		fprintf(stderr, "[ERROR] no input provided\n");
		exit(1);
	}
	const char *file_path = argv[1];
	int width, height;
	uint32_t *pixels = (uint32_t*)stbi_load(file_path, &width, &height, NULL, 4);
	if (pixels == NULL) {
		fprintf(stderr, "[ERROR] file not able to load\n");
		exit(1);
	}
	
	uint32_t *pixels_tr = scaled_down(pixels);
	for (int y=0 ; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			putc(color_to_char(pixels_tr[y*width + x]), stdout);
		}
		putc("\n", stdout);
	}

	return 0;
}
