#include <stdio.h>
#include <stdlib.h>

char SEP = ',';
int getLength(FILE* f) {
	int i = 0;
	char ch;
	while ((ch = fgetc(f)) != EOF)
	{
		if (ch == '\n')
		{
			i++;
		}
	}
	return i;
}

int getNumArgs(char* line) {

	char* *next, arg;
	int i = 0;
	while ((arg = strtok_s(line, SEP, &next)) != NULL)
	{
		line = NULL;
		i++;
	}
	return (i - 1);
}

void readRow(char* line, float* values, int* noValues)
{
	char* *next, arg;
	int i = 0;
	while ((arg = strtok_s(line, SEP, &next)) != NULL)
	{
		line = NULL;
		values[i] = atof(arg);
		i++;
	}
}
FILE* openFile(char* path) {
	FILE* f = NULL;
	if ((fopen_s(&f, path, "r")) != 0)
	{
		printf("unable to open file\n", path);
		return NULL;
	}
}
int readcsv(char* path, float testPercent, float** xes, float** yes, float* x, float* y, int* testSize, int* trainSize, int* argNum) {
	FILE* f = openFile(path);
	float* lineValues;
	if (f == NULL)
	{
		return -1;
	}
	char line[999];
	int iterator = 0;
	int length = getLength(f);
	int numOfTest = (testPercent * (float)length);
	int numOfTrain = length - numOfTest;
	int numArgs = getNumArgs(f);
	while (fgets(line, 999, f))
	{
		if (iterator = 0) {
			numArgs = getNumArgs(line);
			lineValues = malloc(sizeof(float)*numArgs);
		}
		else {
			readRow(line, lineValues, numArgs);
			for (int i = 0; i < numArgs - 1; i++)
			{
				if (iterator < numOfTrain)
				{
					xes[iterator][i] = lineValues[i];
				}
				else {
					x[iterator - numOfTrain] = lineValues[i];
				}
			}
			if (iterator < numOfTrain)
			{
				yes[iterator][0] = lineValues[numArgs -1];
			}
			else {
				y[iterator - numOfTrain] = lineValues[numArgs - 1];
			}
		}
		iterator++;
	}
	//value y is not countet as argument
	*argNum = numArgs - 1;
	*trainSize = numOfTrain;
	*testSize = numOfTest;
}