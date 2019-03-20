#pragma once
typedef struct lin_reg
{
	double a;
	double b;
} lin_reg;

void linReg(double* xes, double* yes, int size, lin_reg* lr);