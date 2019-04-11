#pragma once
typedef struct lin_reg
{
	double a;
	double b;
} lin_reg;

void linRegWrapper(float** xes, float** yes, int size, int numArgs, float* ans);
void linReg(float* xes, float* yes, int size, lin_reg* lr);