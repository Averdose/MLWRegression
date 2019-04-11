#pragma once
#include <stdio.h>
int readcsv(char* path, float testPercent, float** xes, float** yes, float* x, float* y, int* testSize, int* trainSize, int* argNum);