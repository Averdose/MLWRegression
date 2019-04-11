#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customReg.h"
#include "kann.h"
#include "Utility.h"
#include "GradientReg.h"
#include "statistics.h"
#include "csvReader.h"

int main(int argc, char **argv)
{
	if (argc == 5 || (argc == 6 && argv[4][0] == '3'))
	{
		float percentage = atof(argv[2]);
		float mse, sse, mae;
		int argNum = 3;
		int trainSize = 1000;
		int testSize = 15;
		int iterations = 1000;
		float **xes = NULL;
		float **yes = NULL;
		float *y = NULL;
		float **x = NULL;
		float *beta = NULL;
		float *recTrainy = NULL;
		float *recTesty = NULL;
		float *xess = malloc(sizeof(float)*trainSize);
		float *yess = malloc(sizeof(float)*trainSize);

		char in;
		if (getsize(argv[1], percentage, &trainSize, &testSize) != -1) {
			xes = (float**)malloc(trainSize * sizeof(float*));
			yes = (float**)malloc(trainSize * sizeof(float*));
			y = malloc(sizeof(float)*testSize);
			x = (float**)malloc(sizeof(float*)*testSize);

			if (readcsv(argv[1], xes, yes, x, y, testSize, trainSize, &argNum) == -1)
			{
				printf("Couldnt open specified file data will be generated automatically instead\n");
				for (int i = 0; i < testSize; i++)
				{
					x[i] = (float *)malloc(argNum * sizeof(float));
					for (int j = 0; j < argNum; j++)
					{
						x[i][j] = (i + 1) * (j + 1);;
					}
					y[i] = i + 4;
				}
				for (int i = 0; i < trainSize; i++)
				{
					xes[i] = (float *)malloc(argNum * sizeof(float));
					yes[i] = (float *)malloc(sizeof(float));
					yess[i] = i + 4;
					xess[i] = i;
					for (int j = 0; j < argNum; j++)
					{
						xes[i][j] = i * (j + 1);
					}
					yes[i][0] = i + 4;
					xes[i][0] = i;
				}
			}
			recTesty = malloc(sizeof(float)*testSize);
			recTrainy = malloc(sizeof(float)*trainSize);
			beta = malloc(sizeof(float)*(argNum + 1));

			float *ty = malloc(sizeof(float)*trainSize);
			lin_reg lr;
			kann_t *ann;
			kad_node_t *t;
			if (argv[3][0] == 'y')
			{
				normalizeData(xes, yes, x, y, trainSize, testSize, argNum);
			}
			if (argv[4][0] == '3')
			{
				iterations = atoi(argv[5]);
				gradRegWrapper(xes, yes, trainSize, argNum, beta, iterations);
				/*
				t = kann_layer_input(argNum); // for MNIST
				t = kad_relu(kann_layer_dense(t, 64)); // a 64-neuron hidden layer with ReLU activation
				t = kann_layer_cost(t, 1, KANN_C_MSE); // softmax output + multi-class cross-entropy cost
				ann = kann_new(t, 0);                   // compile the network and collate variables
				kann_train_fnn1(ann, 0.001f, 64, 10, 10, 0.1f, trainSize, xes, yes);
				//float *pint= ann->v[0][64].x;
				//float value = *pint;
				y = kann_apply1(ann, x);
				for (int i = 0; i < testSize; i++)
				{
					printf("prediction for %f = %f\n", x[i], y[i]);
				}
				kann_delete(ann);
				*/

			}
			else if (argv[4][0] == '1')
			{
				linRegWrapper(xes, yes, trainSize, argNum, beta);
			}
			else if (argv[4][0] == '2')
			{
				linRegWrapper2(xes, yes, trainSize, argNum, beta);
			}
			else
			{
				puts("incorect input");
			}

			if (argv[4][0] == '1' || argv[4][0] == '2' || argv[4][0] == '3')
			{
				computeResult(xes, beta, trainSize, argNum, recTrainy);
				transpose(yes, ty, trainSize, 0);
				getStats(recTrainy, ty, trainSize, &mse, &sse, &mae);
				printf("TRAIN SET\nMSE=%f, SSE=%f, MAE=%f\n", mse, sse, mae);
				computeResult(x, beta, testSize, argNum, recTesty);
				getStats(recTesty, y, testSize, &mse, &sse, &mae);
				printResult(beta, recTesty, argNum, testSize, x);
				printf("TEST SET\nMSE=%f, SSE=%f, MAE=%f\n", mse, sse, mae);
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
		free(yess);
		free(yes);
		free(xess);
		getchar();
	}
else {
	printf("incorrect argumetns");
	getchar();
}
}

