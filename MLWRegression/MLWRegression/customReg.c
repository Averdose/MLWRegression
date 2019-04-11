#include "customReg.h"
#include <stdlib.h>
#include <math.h>
#include "linreg2.h"
#include "Utility.h"


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


void linRegWrapper2(float** xes, float** yes, int size, int numArgs, float* ans)
{
	ans[0] = 0;
	float m, b, r;
	float *ty = malloc(sizeof(float)*size);
	transpose(yes, ty, size, 0);
	for (int i = 1; i < numArgs + 1; i++)
	{
		float *tx = malloc(sizeof(float)*size);
		transpose(xes, tx, size, i - 1);
		linreg(size, tx, ty, &m, &b, &r);
		ans[0] += b;
		ans[i] = m;
	}
}
void linRegWrapper(float** xes, float** yes, int size, int numArgs, float* ans)
{
	//print(xes, size, numArgs);
	//print(yes, size,1);
	lin_reg lr;
	ans[0] = 0;
	float *ty = (float*) malloc(sizeof(float)*size);
	transpose(yes, ty, size, 0);
	for (int i = 1; i < numArgs+1; i++)
	{
		float *tx = malloc(sizeof(float)*size);
		transpose(xes, tx, size, i -1);
		linReg(tx, ty, size, &lr);
		ans[0] += lr.b;
		ans[i] = lr.a;
	}
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

