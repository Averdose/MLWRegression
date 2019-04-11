#include <stdio.h>
#include <stdlib.h>

void computeResult(float** xes, float* beta, int size, int argNum, float* outy) {
	for (int i = 0; i < size; i++)
	{
		float val = beta[0];
		for (int j = 1; j < (argNum + 1); j++)
		{
			val += beta[j] * xes[i][j - 1];
		}
		outy[i] = val;
	}
}

void printFunction(float* beta, int size)
{
	printf("y = ");
	for (int i = 1; i < size; i++)
	{
		printf("%fx_%d + ", beta[i], i);
	}
	printf("%f\n", beta[0]);
}

void transpose(float** arr, float* ar, int s1, int collumn)
{
	//printf("column=%d\n", collumn);
	for (int i = 0; i < s1; i++)
	{
		ar[i] = arr[i][collumn];
		//printf("%f\n", arr[i][collumn]);
	}
}
void print2(float* arr, int s1)
{
	for (int i = 0; i < s1; i++)
	{
		printf("%f ", arr[i]);
	}
	printf("\n");
}
void printd(float** arr, int s1, int s2)
{
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}
}

void printResult(float* beta, float* prediction, int argNum, int testSize, float** x) {
	printFunction(beta, argNum + 1);
	for (int i = 0; i < testSize; i++)
	{
		printf("prediction for ");
		for (int j = 1; j < (argNum + 1); j++)
		{
			printf("x[%d] = %f ", j - 1, x[i][j - 1]);
		}
		printf(" : %f\n", prediction[i]);
	}
}

