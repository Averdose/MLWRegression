#pragma once
#include <stdio.h>
int getsize(char* path, float testPercent, int* trainSize, int* testSize);
int readcsv(char* path, float** xes, float** yes, float** x, float* y, int testSize, int trainSize, int* argNum);