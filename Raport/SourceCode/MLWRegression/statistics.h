#pragma once
void normalizeS(float* arr, int s1, float min, float max);
void normalizeD(float** arr, int s1, int s2, float min, float max);
void minMaxS(float* arr, int s1, float* outmin, float* outmax, int minSet, int maxSet);
void minMaxD(float** arr, int s1, int s2, float* outmin, float* outmax, int minSet, int maxSet);
void normalizeData(float** xes, float** yes, float** x, float* y, int trainSize, int testSize, int argNum);
void getStats(float* x, float* y, int size, float* mse, float* sse, float* mae);