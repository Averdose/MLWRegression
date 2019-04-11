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

int getNumArgs(char* line, char sep) {
	char* *next, arg;
	int i = 0;
	while ((arg = strtok_s(line, ",", &next)) != NULL)
	{
		line = NULL;
		i++;
	}
	return i;
}

void readRow(char* line, float* values, int noValues, char sep)
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
int readcsv(char* path, float testPercent, float** xes, float** yes, float** x, float* y, int* testSize, int* trainSize, int* argNum) {
	char* sep = ",";
	FILE* f = openFile(path);
	float* lineValues;
	int numArgs;
	if (f == NULL)
	{
		return -1;
	}
	rewind(f);
	char line[999];
	int iterator = 0;
	int first = 1;
	int length = getLength(f) - 1;
	rewind(f);
	int numOfTest = (testPercent * (float)length);
	int numOfTrain = length - numOfTest;
	while (fgets(line, 999, f))
	{
		if (first == 1) {
			numArgs = getNumArgs(line, sep);
			lineValues = malloc(sizeof(float)*numArgs);
			for (int i = 0; i < numOfTrain; i++)
			{
				xes[i] = (float *)malloc((numArgs-1) * sizeof(float));
				yes[i] = (float *)malloc(sizeof(float));
			}
			for (int i = 0; i < numOfTest; i++)
			{
				x[i] = (float *)malloc((numArgs -1) * sizeof(float));
			}
			first = 0;
		}
		else {
			readRow(line, lineValues, numArgs, sep);
			for (int i = 0; i < numArgs - 1; i++)
			{
				if (iterator < numOfTrain)
				{
					float scsc = lineValues[i];
					xes[iterator][i] = lineValues[i];
				}
				else {
					x[iterator - numOfTrain][i] = lineValues[i];
				}
			}
			if (iterator < numOfTrain)
			{
				yes[iterator][0] = lineValues[numArgs -1];
			}
			else {
				y[iterator - numOfTrain] = lineValues[numArgs - 1];
			}
			iterator++;

		}
	}
	//value y is not countet as argument
	*argNum = numArgs - 1;
	*trainSize = numOfTrain;
	*testSize = numOfTest;
}