
#include <stdio.h>
#include <stdlib.h>
#define TRAIN_COUNT (sizeof(data) / sizeof(data[0]))

// the model is y = x*w

int data[][2] = {
	{0,0},
	{1,2},
	{2,4},
	{3,6},
	{4,8}
};

float rand_float () {
	return (float) rand() / (float) RAND_MAX;
}


float cost_function (float w) {
	float cost = 0.0f;
	for (int i=0; i < TRAIN_COUNT; ++i) {
		float x = data[i][0];
		float y = x * w;
		float d = y - data[i][1];
		cost += d * d;
	}
	cost /= TRAIN_COUNT;
	return cost;
}

int main () {
	// printf("hello subroza\n");
	srand(10);
	// *10.0f to make the number lie between 0 and 10
	float w = rand_float() * 10.0f;
	float eps = 1e-3;
	// finite difference
	float rate = 1e-3;
	for (int i=0; i < 500; ++i) {		
		float dcost = (cost_function(w + eps) - cost_function(w))/eps;
		w -= rate * dcost;
		printf("%f\n", cost_function(w));
	}
	printf("-----------------\n");
	printf("%f\n", w);
	return 0;
}
