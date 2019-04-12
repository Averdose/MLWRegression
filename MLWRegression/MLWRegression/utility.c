#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINELEN 99
void computeResult(float** xes, float* beta, int size, int argNum, float* outy) {
	for (int i = 0; i < size; i++)
	{
		float val = beta[0];
		for (int j = 1; j < (argNum + 1); j++)
		{
			val += beta[j] * xes[i][j - 1];
		}
		outy[i] = val;
	}
}

void printFunction(float* beta, int size)
{
	printf("y = ");
	for (int i = 1; i < size; i++)
	{
		printf("%fx_%d + ", beta[i], i);
	}
	printf("%f\n", beta[0]);
}

void transpose(float** arr, float* ar, int s1, int collumn)
{
	for (int i = 0; i < s1; i++)
	{
		ar[i] = arr[i][collumn];
	}
}
void print2(float* arr, int s1)
{
	for (int i = 0; i < s1; i++)
	{
		printf("%f ", arr[i]);
	}
	printf("\n");
}
void printd(float** arr, int s1, int s2)
{
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}
}

void printResult(float* beta, float* prediction, int argNum, int testSize, float** x) {
	printFunction(beta, argNum + 1);
	for (int i = 0; i < testSize; i++)
	{
		printf("prediction for ");
		for (int j = 1; j < (argNum + 1); j++)
		{
			printf("x[%d] = %f ", j - 1, x[i][j - 1]);
		}
		printf(" : %f\n", prediction[i]);
	}
}

void removeNL(char* line)
{
	for (int i = 0; i < LINELEN; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = 0;
		}
	}
}

void readLine(char* line, char*** arguments, int iterator)
{
	char* arg = strtok(line, " ");
	int i = 0;
	while (arg != NULL)
	{
		strcpy(arguments[iterator][i], arg);
		removeNL(arguments[iterator][i]);
		arg = strtok(NULL, " ");
		i++;
		
	}
	if (i == 5)
	{
		arguments[iterator][5] = "10000";
	}
	//line2 = NULL;
}

void readConfig(char* path, char*** arguments, int* testNum, int consoleArgs)
{
	FILE *f;
	char line[LINELEN];
	int iterator = 0;
	f = fopen(path, "r");
	if (f == NULL)
	{
		return -1;
	}
	while (fgets(line,9999,f)!=NULL) {
		printf("%s", line);
		readLine(line, arguments, iterator);
		iterator++;
	}
	printf("\n");
	fclose(f);
	*testNum = iterator;
}

int openFileW(FILE* f, char* path)
{
	
	if (f == NULL)
	{
		return -1;
	}
	return 1;
}

void writeToFile(char* path, float* yTrue, float* yPredict, int size, float mse, float sse, float mae) {
	char* pathStats = malloc(sizeof(char) * LINELEN);
	char* pathCompare = malloc(sizeof(char) * LINELEN);
	strcpy(pathStats, path);
	strcpy(pathCompare, path);
	strcat(pathStats, "Statistics.txt");
	strcat(pathCompare, "Comparision.txt");
	int k = 0;
	FILE *f;
	f = fopen(pathStats, "w");
	if (f == NULL)
	{
		return -1;
	}
	FILE *fComp = fopen(pathCompare, "w");
	if (fComp == NULL)
	{
		return -1;
	}
	fprintf(f, "MSE=%f, SSE=%f, MAE=%f", mse, sse, mae);
	fprintf(fComp, "YTRUE,YPREDICT\n");
	for (int i = 0; i < size; i++)
	{
		fprintf(fComp, "%f,%f\n", yTrue[i], yPredict[i]);
	}
	fclose(fComp);
	fclose(f);

}