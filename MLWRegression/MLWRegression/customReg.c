#include "customReg.h"
#include <stdlib.h>
#include <math.h>

static float meanFc(float* nums, int n);
static float variance(float* nums, int n);


static float meanFc(float* nums, int n)
{
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += nums[i];
	}
	return sum / n;
}

static float variance(float* nums, int n)
{
	float sum = 0;
	//float *sq = malloc(sizeof(float)*n);
	for (int i = 0; i < n; i++)
	{
		float temp = nums[i];
		temp = pow(temp, 2);
		sum += pow(nums[i], 2);
		//sq[i] = pow(nums[i], 2);
	}
	float mean = meanFc(nums, n);
	
	//free(sq);
	float variance = (sum / n - pow(mean, 2));
	return variance;
}

void linReg(float* xes, float* yes, int size, lin_reg* lr)
{
	float *prod = malloc(sizeof(float)*size);
	float xMean = meanFc(xes, size);
	float yMean = meanFc(yes, size);
	for (int i = 0; i < size; i++)
	{
		prod[i] = xes[i] * yes[i];
	}

	int temp = yes[1];
	temp = xes[1];
	temp = prod[1];
	float productMean = meanFc(prod, size);
	float xVar = variance(xes, size);
	lr->a = (productMean - (xMean * yMean)) / xVar;

	lr->b = yMean - (lr->a * xMean);
	free(prod);
}

