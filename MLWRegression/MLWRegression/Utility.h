#pragma once
void printResult(float* beta, float* prediction, int argNum, int testSize, float** x);
void transpose(float** arr, float* ar, int s1, int collumn);
void print2(float* arr, int s1);
void printd(float** arr, int s1, int s2);
void computeResult(float** xes, float* beta, int size, int argNum, float* outy);
void readConfig(char* path, char** arguments);