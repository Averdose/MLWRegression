#pragma once
typedef struct lin_reg
{
	double a;
	double b;
} lin_reg;

void print(float** arr, int s1, int s2);
void linReg(double* xes, double* yes, int size, lin_reg* lr);
void linRegWrapper(float** xes, float* yes, int size, int numArgs, float* ans);
void transpose(float** arr, float* ar, int s1, int collumn);
void print2(float* arr, int s1);