#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	while ((arg = strtok_s(line, ",", &next)) != NULL)
	{
		line = NULL;
		i++;
	}
	return i;
}

void readRow(char* line, float* values, int noValues)
{
	char* *next;
	char* arg = strtok(line, ",");
	int i = 0;
	while (arg != NULL)
	{
		values[i] = atof(arg);
		arg = strtok(NULL, ",");
		i++;
	}
	line = NULL;
	/*
	while ((arg = strtok_s(line, ",", &next)) != NULL)
	{
		values[i] = atof(line);
		line = NULL;
		i++;
	}*/
}
FILE* openFile(char* path) {
	FILE* f = NULL;
	if ((fopen_s(&f, path, "r")) != 0)
	{
		printf("unable to open file\n", path);
		return NULL;
	}
	return f;
}

int getsize(char* path, float testPercent, int* trainSize, int* testSize) {
	FILE* f = openFile(path);
	if (f == NULL)
	{
		return -1;
	}
	int length = getLength(f);
	rewind(f);
	*testSize = (testPercent * (float)length);
	*trainSize = length - *testSize;
	fclose(f);
}

int readcsv(char* path, float** xes, float** yes, float** x, float* y, int testSize, int trainSize, int* argNum) {
	FILE* f = openFile(path);
	float* lineValues = (float*)malloc(sizeof(float));

	int numArgs;
	if (f == NULL)
	{
		return -1;
	}
	rewind(f);
	char* line = (char*)malloc(sizeof(char) * 9999);
	int iterator = 0;
	int first = 1;
	while (fgets(line, 9999, f))
	{
		if (first == 1) {
			numArgs = getNumArgs(line);
			lineValues = malloc(sizeof(float)*numArgs);
			for (int i = 0; i < trainSize; i++)
			{
				xes[i] = (float *)malloc((numArgs-1) * sizeof(float));
				yes[i] = (float *)malloc(sizeof(float));
			}
			for (int i = 0; i < testSize; i++)
			{
				x[i] = (float *)malloc((numArgs -1) * sizeof(float));
			}
			first = 0;
		}
		else {
			readRow(line, lineValues, numArgs);
			for (int i = 0; i < numArgs - 1; i++)
			{
				if (iterator < trainSize)
				{
					float scsc = lineValues[i];
					xes[iterator][i] = lineValues[i];
				}
				else {
					x[iterator - trainSize][i] = lineValues[i];
				}
			}
			if (iterator < trainSize)
			{
				yes[iterator][0] = lineValues[numArgs -1];
			}
			else {
				y[iterator - trainSize] = lineValues[numArgs - 1];
			}
			iterator++;

		}
	}
	//value y is not countet as argument
	*argNum = numArgs - 1;
	fclose(f);
}