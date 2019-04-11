#include "statistics.h"
#include <stdlib.h>
#include <math.h>

void getStats(float* x, float* y, int size, float* mse, float* sse, float* mae) {
	*mse = 0;
	*sse = 0;
	*mae = 0;
	for (int i = 0; i < size; i++)
	{
		*sse += pow((x[i] - y[i]), 2);
		*mae += abs(x[i] - y[i]);
	}
	*mae = *mae / size;
	*mse = *sse / size;
}

void normalizeData(float** xes, float** yes, float** x, float* y, int trainSize, int testSize, int argNum) {
	float min, max;
	minMaxD(x, testSize, argNum, &min, &max, 0, 0);
	minMaxD(yes, testSize, 1, &min, &max, 1, 1);
	minMaxS(y, testSize, &min, &max, 1, 1);
	minMaxD(xes, trainSize, argNum, &min, &max, 1, 1);
	normalizeD(xes, trainSize, argNum, min, max);
	normalizeD(x, testSize, argNum, min, max);
	normalizeD(yes, trainSize, 1, argNum, min, max);
	normalizeS(y, testSize, argNum, min, max);
}
void normalizeS(float* arr, int s1, float min, float max) {
	for (int i = 0; i < s1; i++)
	{
		arr[i] = (arr[i] - min) / (max - min);
	}
}
void normalizeD(float** arr, int s1, int s2, float min, float max) {
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			arr[i][j] = (arr[i][j] - min) / (max - min);
		}
	}
}
void minMaxS(float* arr, int s1, float* outmin, float* outmax, int minSet, int maxSet) {
	float min, max;
	if (minSet == 1)
	{
		min = *outmin;
	}
	if (maxSet == 1)
	{
		max = *outmax;
	}
	for (int i = 0; i < s1; i++)
	{
		if (minSet == 0)
		{
			min = arr[i];
			minSet = 1;
		}
		else {
			if (arr[i] < min)
			{
				min = arr[i];
			}
		}
		if (maxSet == 0)
		{
			max = arr[i];
			maxSet = 1;
		}
		else {
			if (arr[i] > max)
			{
				max = arr[i];
			}
		}
	}
	*outmax = max;
	*outmin = min;
}
void minMaxD(float** arr, int s1, int s2, float* outmin, float* outmax, int minSet, int maxSet)
{
	float min, max;
	if (minSet == 1)
	{
		min = *outmin;
	}
	if (maxSet == 1)
	{
		max = *outmax;
	}
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			if (minSet == 0)
			{
				min = arr[i][j];
				minSet = 1;
			}
			else {
				if (arr[i][j] < min)
				{
					min = arr[i][j];
				}
			}
			if (maxSet == 0)
			{
				max = arr[i][j];
				maxSet = 1;
			}
			else {
				if (arr[i][j] > max)
				{
					max = arr[i][j];
				}
			}
		}
	}
	*outmax = max;
	*outmin = min;
}