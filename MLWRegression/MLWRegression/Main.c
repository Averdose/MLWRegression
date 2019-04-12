#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customReg.h"
#include "Utility.h"
#include "GradientReg.h"
#include "statistics.h"
#include "csvReader.h"

int main(int argc, char **argv)
{
	int testNum;
	int maxTests = 200;
	int consolargs = 6;
	char*** parameters = (char***)malloc(sizeof(char**)*maxTests);
	for (int i = 0; i < maxTests; i++)
	{
		parameters[i] = (char**)malloc(sizeof(char*) * consolargs);

		for (int j = 0; j < consolargs; j++)
		{
			parameters[i][j] = malloc(sizeof(char) * 99);
		}
	}
	readConfig(argv[1], parameters, &testNum, consolargs);
	
	float mse, sse, mae;
	int argNum;
	int trainSize;
	int testSize;
	int iterations;
	float **xes = NULL;
	float **yes = NULL;
	float *y = NULL;
	float **x = NULL;
	float *beta = NULL;
	float *recTrainy = NULL;
	float *recTesty = NULL;
	for (int h = 0; h < testNum; h++)
	{
		float percentage = atof(parameters[h][1]);
		char in;
		if (getsize(parameters[h][0], percentage, &trainSize, &testSize) != -1) {
			xes = (float**)realloc(xes, trainSize * sizeof(float*));
			yes = (float**)realloc(yes, trainSize * sizeof(float*));
			y = realloc(y, sizeof(float)*testSize);
			x = (float**)realloc(x, sizeof(float*)*testSize);
			if (readcsv(parameters[h][0], xes, yes, x, y, testSize, trainSize, &argNum) != -1)
			{
				recTesty = realloc(recTesty, sizeof(float)*testSize);
				recTrainy = realloc(recTrainy, sizeof(float)*trainSize);
				beta = realloc(beta, sizeof(float)*(argNum + 1));
				float *ty = NULL;
				ty = realloc(ty, sizeof(float)*trainSize);
				if (parameters[h][2][0] == 'y')
				{
					normalizeData(xes, yes, x, y, trainSize, testSize, argNum);
				}
				if (parameters[h][3][0] == '3')
				{
					iterations = atoi(parameters[h][5]);
					gradRegWrapper(xes, yes, trainSize, argNum, beta, iterations);
				}
				else if (parameters[h][3][0] == '1')
				{
					linRegWrapper(xes, yes, trainSize, argNum, beta);
				}
				else if (parameters[h][3][0] == '2')
				{
					linRegWrapper2(xes, yes, trainSize, argNum, beta);
				}
				if (parameters[h][3][0] == '1' || parameters[h][3][0] == '2' || parameters[h][3][0] == '3')
				{
					computeResult(xes, beta, trainSize, argNum, recTrainy);
					transpose(yes, ty, trainSize, 0);
					getStats(recTrainy, ty, trainSize, &mse, &sse, &mae);
					printf("TRAIN SET\nMSE=%f, SSE=%f, MAE=%f\n", mse, sse, mae);
					computeResult(x, beta, testSize, argNum, recTesty);
					getStats(recTesty, y, testSize, &mse, &sse, &mae);
					printResult(beta, recTesty, argNum, testSize, x);
					printf("TEST SET\nMSE=%f, SSE=%f, MAE=%f\n", mse, sse, mae);
					writeToFile(parameters[h][4], y, recTrainy, testSize, mse, sse, mae);
				}
			}
		}
	}
	free(y);
	for (int i = 0; i < trainSize; i++)
	{
		free(xes[i]);
		free(yes[i]);
		if (i < testSize)
		{
			free(x[i]);
		}
	}
	free(recTesty);
	free(recTrainy);
	free(x);
	free(beta);
	free(xes);
	free(yes);
	getchar();
	
}

