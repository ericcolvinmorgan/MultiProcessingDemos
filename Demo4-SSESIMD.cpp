#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include "simd.p4.h"

// setting the number of nodes for the calculation:
#ifndef ARRAYSIZE
#define ARRAYSIZE	128
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	25
#endif

float a[ARRAYSIZE];
float b[ARRAYSIZE];
float c[ARRAYSIZE];

float Ranf(float, float);

void loadRandomValues(float* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = Ranf(-1, 1);
	}
}

int main(int argc, char* argv[])
{
#ifndef _OPENMP
	fprintf(stderr, "No OpenMP support!\n");
	return 1;
#endif

	// fill the random-value arrays:
	loadRandomValues(a, ARRAYSIZE);
	loadRandomValues(b, ARRAYSIZE);
	loadRandomValues(c, ARRAYSIZE);

	for (int t = 0; t < NUMTRIES; t++)
	{
		double time0 = omp_get_wtime();

		float sum = SimdMulSum(a, b, ARRAYSIZE);
		double time1 = omp_get_wtime();
		//double megaHeightsPerSecond = (double)(NUMNODES * NUMNODES) / (time1 - time0) / 1000000.;
		printf("%d,%lf\n", ARRAYSIZE, sum);
	}

	return 0;
}

float Ranf(float low, float high)
{
	float r = (float)rand();               // 0 - RAND_MAX
	float t = r / (float)RAND_MAX;       // 0. - 1.

	return   low + t * (high - low);
}