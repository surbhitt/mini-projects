#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"

#define SCALE_DOWN_FAC 10 
#define PIXEL_R(color) (((color)&0x000000ff)>>(8*0))
#define PIXEL_G(color) (((color)&0x0000ff00)>>(8*1))
#define PIXEL_B(color) (((color)&0x00ff0000)>>(8*2))
#define PIXEL_A(color) (((color)&0xff000000)>>(8*3))
#define RECOMP_RGBA(r, g, b, a) ((((r)&0xff)<<(8*0)) | (((g)&0xff)<<(8*1)) | (((b)&0xff)<<(8*2)) | (((a)&0xff)<<(8*3))) 


/****************
1) Load the image
2) Scale down the pixelchunk loaded:
		[.] take chunks of size 
		[.] average out the pixels 
		[.] store value in new array 
3) Convert the new array values to char
4) putc

****************/

uint32_t *scaled_down(uint32_t *pixels, int height, int width) {
	 
	uint32_t *pixels_tr = malloc((height*width/SCALE_DOWN_FAC*SCALE_DOWN_FAC)*sizeof(uint32_t));
	memset(pixels_tr,0x00000000,(height*width/SCALE_DOWN_FAC*SCALE_DOWN_FAC)*sizeof(uint32_t));

	
	int i=0,j=0,cnt=0;
	uint32_t pixel;
	for (;;) {
		uint32_t tmpr=0x00, tmpg=0x00, tmpb=0x00, tmpa=0x00;
		for (int x=0;x<SCALE_DOWN_FAC;++x) {
			for (int y=0; y<SCALE_DOWN_FAC; ++y) {
				pixel = pixels[(i*width + j) + (x*width + y)];
				tmpr += PIXEL_R(pixel);
				tmpg += PIXEL_G(pixel);
				tmpb += PIXEL_B(pixel);
				tmpa += PIXEL_A(pixel);
			}
		}

		uint32_t tr_r = tmpr/(SCALE_DOWN_FAC*SCALE_DOWN_FAC); 
		uint32_t tr_g = tmpg/(SCALE_DOWN_FAC*SCALE_DOWN_FAC);
		uint32_t tr_b = tmpb/(SCALE_DOWN_FAC*SCALE_DOWN_FAC);  
		uint32_t tr_a = tmpa/(SCALE_DOWN_FAC*SCALE_DOWN_FAC);
		
		*(pixels_tr+cnt) = RECOMP_RGBA(tr_r, tr_g, tr_b, tr_a);
		cnt++;
		j += SCALE_DOWN_FAC;
		if (j>=width) { 
			i += SCALE_DOWN_FAC;
			if (i>=height) {
				break;
			}
			else {
				j=0;
			}
		}
	}
	return pixels_tr;
}

char table[] = " .':o*#@";
size_t n = sizeof(table) - 1;

// changes the pixel to ascii char
char color_to_char(uint32_t pixel) {
	int r = PIXEL_R(pixel);	
	int g = PIXEL_G(pixel); 	
	int b = PIXEL_B(pixel);
	
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

	uint32_t *pixels_tr = scaled_down(pixels, height, width);
	int tr_height = height/SCALE_DOWN_FAC;
	int tr_width = width/SCALE_DOWN_FAC;
	for (int y=0 ; y<tr_height; ++y) {
		for (int x=0; x<tr_width; ++x) {
			putc(color_to_char(pixels_tr[y*tr_width + x]), stdout);
			putc(color_to_char(pixels_tr[y*tr_width + x]), stdout);
			putc(color_to_char(pixels_tr[y*tr_width + x]), stdout);
		}
		putc('\n',stdout);
	}	

	return 0;
}
