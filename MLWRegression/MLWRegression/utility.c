#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	//printf("column=%d\n", collumn);
	for (int i = 0; i < s1; i++)
	{
		ar[i] = arr[i][collumn];
		//printf("%f\n", arr[i][collumn]);
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

void readLine2(char* line2, char*** arguments2, int iterator)
{
	char* *next;
	char* arg = strtok(line2, " ");
	int i = 0;
	while (arg != NULL)
	{
		arguments2[iterator][i] = arg;
		arg = strtok(NULL, " ");
		i++;
		
	}
	if (i == 5)
	{
		arguments2[iterator][5] = "10000";
	}
	//line2 = NULL;
}

void readConfig(char* path, char*** arguments, int* testNum)
{
	FILE* f = openFile(path);
	if (f == NULL)
	{
		return -1;
	}
	int iterator = 0;
	char* line = (char*)malloc(sizeof(char) * 9999);
	char c = 's';
	while (c != NULL)
	{
		c = fgets(line, 9999, f);
		readLine2(line, arguments, iterator);
		iterator++;
	}
	fclose(f);
	*testNum = iterator;
}

void writeToFile(char* path, float* yTrue, float* yPredict, int size, float mse, float sse, float mae) {

	char* pathStats = malloc(sizeof(char) * 999);
	char* pathCompare = malloc(sizeof(char) * 999);
	strcpy(pathStats, path);
	strcpy(pathCompare, path);
	strcat(pathStats, "Statistics.txt");
	strcat(pathCompare, "Comparision.txt");
	FILE * fStats = fopen(pathStats, 'w');
	if (fStats == NULL)
	{
		return -1;
	}
	FILE * fComp = fopen(pathCompare, 'w');
	if (fComp == NULL)
	{
		return -1;
	}
	fprintf(fStats, "MSE=%f, SSE=%f, MAE=%f", mse, sse, mae);
	fprintf(fComp, "YTRUE,YPREDICT");
	for (int i = 0; i < size; i++)
	{
		fprintf(fComp, "%f,%f\n", yTrue[i], yPredict[i]);
	}
	fclose(fComp);
	fclose(fStats);

}