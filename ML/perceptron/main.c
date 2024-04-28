
// neural net
// there is a grid of neurons representing an img
// every neuron(cell in the grid) represents a pixel 
// every cell has a weight associated with it
// the answer is sumation(neurons*resp_weights)
// if the sumation is more than the bias of the neuron
// it lights up 
// the bias after training enough number of times converges 
/* 
   training:
   initially all the neurons are 0 weighted
   based on the answer if it is wrong
   if we wanted a 1 and it is 0
   we add the cell values to the weight: excite
   if we wanted a 0 and it is 1
   we sub the cell values from the weight: suppress
*/
// 0 for rectangle and 1 for circle


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <float.h>
#define WIDTH 100
#define HEIGHT 100
#define PPM_SCALER 25 
#define SAMPLE_SIZE 500
#define BIAS 10.0 
#define TRAIN_PASSES 100

typedef float Layer[HEIGHT][WIDTH];  // a 2 dimensional array of floats type of size height*width 

static inline int clampi(int x, int low, int high) {
	if (x < low)  x = low;
	if (x > high) x = high;
	return x;
}

void layer_fill_rect(Layer layer, int x, int y, int w, int h, float value) {
	assert(w>0);
	assert(h>0);
	int x0 = clampi(x, 0, WIDTH-1); 
	int y0 = clampi(y, 0, HEIGHT-1); 
	int x1 = clampi(x0 + w-1, 0, WIDTH-1);
	int y1 = clampi(y0 + h-1, 0, HEIGHT-1);

	for (int y=y0; y<=y1; ++y) {
		for (int x=x0; x<=x1; ++x) {
			layer[y][x] = value;
		}
	}
}

void layer_fill_circle(Layer layer, int cx, int cy, int r, float value) {
	assert(r>0);
	int x0 = clampi(cx - r, 0, WIDTH-1);
	int y0 = clampi(cy - r, 0, HEIGHT-1);
	int x1 = clampi(cx + r, 0, WIDTH-1);
	int y1 = clampi(cy + r, 0, HEIGHT-1);
	
	for (int y=y0; y<=y1; ++y) {
		for (int x=x0; x<=x1; ++x) {
			int dx = x-cx;
			int dy = y-cy;
			if (dx*dx + dy*dy <= r*r) {
				layer[y][x] = value;
			}
		}
	}
}

void layer_save_as_ppm(Layer layer, const char* filepath) {
	float min = FLT_MAX;
	float max = FLT_MIN;
	for (int y=0;y<HEIGHT-1;++y) {
		for (int x=0;x<WIDTH-1;++x) {
			if (layer[y][x]<min) min = layer[y][x];
			if (layer[y][x]>max) max = layer[y][x];
		}
	}

	FILE* f = fopen(filepath, "wb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: Invalid file path %s: %m\n", filepath);
		exit(1);
	}
	fprintf(f, "P6\n%d %d 255\n", WIDTH*PPM_SCALER, HEIGHT*PPM_SCALER);
	for (int y=0;y<HEIGHT*PPM_SCALER; ++y) {
		for (int x=0;x<WIDTH*PPM_SCALER; ++x) {
			float s = (layer[y/PPM_SCALER][x/PPM_SCALER]-min)/(max-min);
			
			char pixel[3] = {
				(char)floor(255*(1.0f-s)),(char)floor(255*s), 0
			};
			fwrite(pixel, sizeof(pixel), 1, f);
		}
	}

	fclose(f);
}

void layer_save_as_bin(Layer layer, const char* filepath) {
	FILE* f = fopen(filepath, "wb");
	if (f == NULL) {
		fprintf(stderr, "ERROR: could not open file %s: %m", filepath);
		exit(1);
	}
	fwrite(layer, sizeof(Layer), 1, f);
	fclose(f);
}

#ifdef unimplemnted
void layer_load_as_bin(Layer layer, const char* filepath) {
	assert(0 && "TODO");	
}
#endif

float feed_forward(float inputs[HEIGHT][WIDTH], float weights[WIDTH][HEIGHT]) {
	
	float output = 0.0f;
	for (int x=0; x<HEIGHT; ++x) { 
		for (int y=0; y<WIDTH; ++y) {
			output += inputs[y][x] * weights[y][x];
		}
	}
	return output;
}

void suppress(Layer inputs, Layer weights){
	for (int y=0;y<HEIGHT;++y) {
		for (int x=0;x<WIDTH;++x) {
			weights[y][x] -= inputs[y][x];
		}
	}
}

void excite(Layer inputs, Layer weights){
	for (int y=0;y<HEIGHT;++y) {
		for (int x=0;x<WIDTH;++x) {
			weights[y][x] += inputs[y][x];
		}
	}
}

int rand_range(int low, int high) {
	assert(low < high);
	return rand() % (high - low) + low;
}

void layer_random_rect(Layer layer) {
	int x, y, w, h;
	layer_fill_rect(layer, 0, 0, WIDTH, HEIGHT, 0.0f);
	x = rand_range(0, WIDTH); 
	y = rand_range(0, HEIGHT);
	w = WIDTH-x;
	if (w<2) w=2;
	w = rand_range(1, w);
	h = HEIGHT-y;
	if (h<2) h=2;
	h = rand_range(1, h);
	layer_fill_rect(layer, x, y, w, h, 1.0f);
}

void layer_random_circle(Layer layer) {
	int cx, cy, r;
	layer_fill_rect(layer, 0, 0, WIDTH, HEIGHT, 0.0f);
	cx = rand_range(0, WIDTH); 
	cy = rand_range(0, HEIGHT);
	r = INT_MAX;
	if (r>cx) r = cx;
	if (r>cy) r = cy;
	if (r> WIDTH-cx) r = WIDTH-cx;
	if (r> HEIGHT-cy) r = HEIGHT-cy;
	if (r<2) r=2;
	r = rand_range(1, r);
	layer_fill_circle(layer, cx, cy, r, 1.0f);
}


int train_pass(Layer inputs, Layer weights) {
	int adjusted = 0;
	for (int i=0; i<SAMPLE_SIZE; ++i) {
		layer_random_rect(inputs);
		if (feed_forward(inputs, weights) > BIAS) {
			suppress(inputs, weights);
			adjusted++;
		}
		layer_random_circle(inputs);
		if (feed_forward(inputs, weights) < BIAS) {
			excite(inputs, weights);
			adjusted++;
		}
	}
	return adjusted;
}

static Layer inputs;
static Layer weights;
#define PREFIX "rect"

int main() {
	//printf("Hello, subroza!\n");
	char filepath[256];
	for (int i=0;i<TRAIN_PASSES; ++i) {
		srand(60);
		int adj = train_pass(inputs, weights);
		printf("weights adjusted %d\n",adj);
		snprintf(filepath, sizeof(filepath), "assets/gif/weight-%02d.ppm", i);
		layer_save_as_ppm(weights, filepath);
	}	
/*
	do {	
	srand(60);
	} while(train_pass(inputs, weights));
	layer_save_as_ppm(weights, "weights.ppm");
*/
#if 0 
	char filepath[256];
	for (int i=0; i<SAMPLE_SIZE; ++i) {
		printf("[INFO] generating "PREFIX" %d\n", i);
		layer_random_rect(inputs);
		snprintf(filepath, sizeof(filepath), "assets/"PREFIX"-%02d.bin", i);
		layer_save_as_bin(inputs, filepath);
		snprintf(filepath, sizeof(filepath), "assets/"PREFIX"-%02d.ppm", i);
		layer_save_as_ppm(inputs, filepath);
	}
#endif
	// layer_fill_circle(inputs, WIDTH/2, HEIGHT/2, WIDTH/2, 1.0f);
	// layer_save_as_ppm(inputs, "inputs.ppm");
	// float otuput = feed_forward(inputs, weights);
	// printf("output = %f\n", output);
	return 0;
}
