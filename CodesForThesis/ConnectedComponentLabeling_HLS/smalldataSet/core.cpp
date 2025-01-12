//#include <stdio.h>
//#include <iostream>
#include <hls_math.h>

#define IMG_HEIGHT 512
#define IMG_WIDTH 512

#define THRESHOLD 70
#define MAX 999
#define MAX_STAR_DATA_SIZE 40
#define MAX_SET_SIZE 40
#define MAX_CENTROID_DATA 40

unsigned lbImage[IMG_HEIGHT * IMG_WIDTH];
unsigned set[MAX_SET_SIZE];

bool status[MAX_STAR_DATA_SIZE];
unsigned totalIntensity[MAX_STAR_DATA_SIZE];
unsigned x[MAX_STAR_DATA_SIZE];
unsigned y[MAX_STAR_DATA_SIZE];

void preProcess(unsigned Image[IMG_HEIGHT*IMG_WIDTH]) {
	unsigned i = 0,j = 0;
	for (i = 0; i < IMG_HEIGHT; ++i) {
#pragma HLS PIPELINE
		for (j = 0; j < IMG_WIDTH; ++j) {
#pragma HLS PIPELINE
			if (Image[i*IMG_HEIGHT + j] < THRESHOLD)
				lbImage[i*IMG_HEIGHT + j] = 0;
			else
				lbImage[i*IMG_HEIGHT + j] = 1;
		}
	}
}

unsigned find(unsigned id) {
	unsigned temp = id;
	while (temp != set[temp]) {
#pragma HLS PIPELINE
		temp = set[temp];
	}
	return temp;
}

unsigned firstPass(unsigned Image[IMG_HEIGHT*IMG_WIDTH]) {
	unsigned i = 0, j = 0;
	unsigned label = 0;
	unsigned prevAbove = 0;
	unsigned prevLeft = 0;
	unsigned setCount = 1;
	unsigned min = 0;
	unsigned max = MAX;
	for (i = 0; i < IMG_HEIGHT; ++i) {
		for (j = 0; j < IMG_WIDTH; ++j) {
#pragma HLS PIPELINE
			if (lbImage[i*IMG_HEIGHT + j] != 0) {
				if(i != 0 && lbImage[(i - 1)*IMG_HEIGHT + j] != 0) {
					prevAbove = lbImage[(i - 1)*IMG_HEIGHT + j];
				}
				else {
					prevAbove = MAX;
				}
				if(j != 0 && lbImage[i*IMG_HEIGHT + j - 1] != 0) {
					prevLeft = lbImage[i*IMG_HEIGHT + j - 1];
				}
				else {
					prevLeft = MAX;
				}

				if (prevAbove == MAX && prevLeft == MAX) {
					lbImage[i*IMG_HEIGHT + j] = ++label;
					set[setCount] = label;

					//
					status[setCount] = true;
					totalIntensity[setCount] = Image[i*IMG_HEIGHT + j];
					x[setCount] = i * Image[i*IMG_HEIGHT + j];
					y[setCount] = j * Image[i*IMG_HEIGHT + j];

					++setCount;
				}
				else {
					//Joint Set
					if(prevAbove < prevLeft) {
						min = prevAbove;
					}
					else {
						min = prevLeft;
					}
					if(prevAbove > prevLeft) {
						max = prevAbove;
					}
					else {
						max = prevLeft;
					}

					if (max != MAX) {
						set[max] = find(min);
					}
					else {
						set[min] = find(min);
					}
					lbImage[i*IMG_HEIGHT + j] = min;

					//Update data
					totalIntensity[min] += Image[i*IMG_HEIGHT + j];
					x[min] += i * Image[i*IMG_HEIGHT + j];
					y[min] += j * Image[i*IMG_HEIGHT + j];
				}
			}
		}
	}
	return setCount;
}

unsigned calCentroid(unsigned setCount, unsigned X[MAX_CENTROID_DATA], unsigned Y[MAX_CENTROID_DATA]) {
	unsigned i = 0;
	unsigned root = 0;
	unsigned centroidDataCount = 0;

	for (i = 1; i < setCount; ++i) {
#pragma HLS PIPELINE
		if (set[i] != i) {
			root = find(i);
			totalIntensity[root] += totalIntensity[i];
			x[root] += x[i];
			y[root] += y[i];
			status[i] = false;
		}
	}

	//cal
	for (i = 1; i < setCount; ++i) {
#pragma HLS PIPELINE
		if (status[i] == true) {
			X[centroidDataCount] = round((float)x[i] / totalIntensity[i]);
			Y[centroidDataCount] = round((float)y[i] / totalIntensity[i]);

			++centroidDataCount;
		}
	}
	return centroidDataCount;
}

void secondPass() {
	unsigned i = 0, j = 0;
	//unsigned root = 0;
	for (i = 0; i < IMG_HEIGHT; ++i) {
#pragma HLS PIPELINE
		for (j = 0; j < IMG_WIDTH; ++j) {
#pragma HLS PIPELINE
			if (lbImage[i*IMG_HEIGHT + j] != 0) {
				//root = find(lbImage[i*IMG_HEIGHT + j]);
				lbImage[i*IMG_HEIGHT + j] = find(lbImage[i*IMG_HEIGHT + j]);
			}
		}
	}
}

unsigned CCLabel(unsigned Image[IMG_HEIGHT * IMG_WIDTH], unsigned X[MAX_CENTROID_DATA], unsigned Y[MAX_CENTROID_DATA]) {
#pragma HLS INTERFACE s_axilite port=return bundle=CRTLS
#pragma HLS INTERFACE bram port=Image bundle=CRTLS
#pragma HLS INTERFACE bram port=X bundle=CRTLS
#pragma HLS INTERFACE bram port=Y bundle=CRTLS

#pragma HLS RESOURCE variable=Image core=RAM_1P_BRAM

	preProcess(Image);
	unsigned setCount = firstPass(Image);
	unsigned centroidDataCount = calCentroid(setCount, X, Y);

	return centroidDataCount;
}
