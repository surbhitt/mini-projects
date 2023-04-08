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
		[.] take chunks of size sdf*sdf
		[.] average out the pixels 
		[.] store value in new array 
3) Convert the new array values to char
4)  .,*:o#@
5) putc

****************/

uint32_t *scaled_down(uint32_t *pixels, int height, int width) {
	 
	uint32_t *pixels_tr = malloc((height*width/SCALE_DOWN_FAC*SCALE_DOWN_FAC)*sizeof(uint32_t));
	memset(pixels_tr,0x00000000,(height*width/SCALE_DOWN_FAC*SCALE_DOWN_FAC)*sizeof(uint32_t));

	#if 0
	// printing the memory 
	int width_sc = width/SCALE_DOWN_FAC;
	int height_sc = height/SCALE_DOWN_FAC;
	printf("this is the fresh pixeltr created\n");
	for (int i=0;i<height_sc;++i) {
		for (int j=0;i<width_sc;++j) {
			printf("i=%d j=%d val=%d || ", i, j, pixels_tr[i*width_sc + j]);
		
		}
		printf("\n");
	}
	#endif

	int i=0,j=0,cnt=0;
	uint32_t pixel;
	for (;;) {
		uint32_t tmpr=0x00, tmpg=0x00, tmpb=0x00, tmpa=0x00;
		// printf("\n\nchunk %d \n\n", cnt);
		for (int x=0;x<SCALE_DOWN_FAC;++x) {
			for (int y=0; y<SCALE_DOWN_FAC; ++y) {
				pixel = pixels[(i*width + j) + (x*width + y)];
				// printf("%d || ",(i*width + j) + (x*width + y));
				tmpr += PIXEL_R(pixel);
				tmpg += PIXEL_G(pixel);
				tmpb += PIXEL_B(pixel);
				tmpa += PIXEL_A(pixel);
			}
			// printf("\n");
		}
		// printf("transformed tmpr=%d, tmpg=%d, tmpb=%d ", tmpr, tmpg, tmpb);

		uint32_t tr_r = tmpr/(SCALE_DOWN_FAC*SCALE_DOWN_FAC); 
		uint32_t tr_g = tmpg/(SCALE_DOWN_FAC*SCALE_DOWN_FAC);
		uint32_t tr_b = tmpb/(SCALE_DOWN_FAC*SCALE_DOWN_FAC);  
		uint32_t tr_a = tmpa/(SCALE_DOWN_FAC*SCALE_DOWN_FAC);
		
		// printf("normalized tr_r=%d, tr_g=%d, tr_b=%d\n\n", tr_r, tr_g, tr_b);
		*(pixels_tr+cnt) = RECOMP_RGBA(tr_r, tr_g, tr_b, tr_a);
		// printf("recomposed=%d  and cnt=%d\n",pixels_tr[cnt], cnt);
		// printf("decomposed r=%d, g=%d , b=%d , a=%d\n",PIXEL_R(pixels_tr[cnt]),PIXEL_G(pixels_tr[cnt]),PIXEL_B(pixels_tr[cnt]),PIXEL_A(pixels_tr[cnt]));
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
	// return pixels;
}


char table[] = " .,*:o#@";
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

void usage() {
	printf("Provide the absolute path for the image");
}

int main(int argc, char** argv) {
	//printf("hello, subroza\n");
	
	if (argc < 2) {
		usage();
		// fprintf(stderr, "[ERROR] no input provided\n");
		exit(1);
	}

	const char *file_path = argv[1];
	
	int width, height;
	uint32_t *pixels = (uint32_t*)stbi_load(file_path, &width, &height, NULL, 4);
	
	if (pixels == NULL) {
		fprintf(stderr, "[ERROR] file not able to load\n");
		exit(1);
	}
	/*if (width%SCALE_DOWN_FAC != 0 && height%SCALE_DOWN_FAC != 0) {
		fprintf(stderr, "[ERROR] width and height unscalable");
	}*/
	// printf("---------the image dimensions are h=%d w=%d\n\n", height, width);
	
	uint32_t *pixels_tr = scaled_down(pixels, height, width);

	int tr_height = height/SCALE_DOWN_FAC;
	int tr_width = width/SCALE_DOWN_FAC;
	for (int y=0 ; y<tr_height; ++y) {
		for (int x=0; x<tr_width; ++x) {
			// printf("%dpixel=%d   ",(y*tr_width + x),pixels_tr[y*tr_width + x]);
			putc(color_to_char(pixels_tr[y*width + x]), stdout);
		}
		// printf("\n----------------\n");
		putc('\n',stdout);
	}	

	return 0;
}
