#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customReg.h"
#include "kann.h"
#include "Utility.h"
#include "GradientReg.h"
#include "statistics.h"
#include "csvReader.h"

void printRandoms(int lower, int upper, int count)
{
	int i;
	for (i = 0; i < count*2; i= i +2) {
		int num1 = (rand() % (upper - lower + 1)) + lower;
		int num2 = (rand() % (upper - lower + 1)) + lower;

		printf("%d.%d", num1,num2);
	}
}

void main()
{
	/*
	int lower = 0, upper = 1000, count = 3;

	// Use current time as  
	// seed for random generator 
	srand(time(0));
	for (int i = 0; i < 100; i++)
	{
		printRandoms(lower, upper, 1);
		printf(",");
		printRandoms(lower, upper, 1);
		printf(",");
		printRandoms(lower, upper, 1);
		printf("\n");
	}

	*/
	float mse, sse, mae;
	int argNum = 3;
	int trainSize = 1000;
	int testSize = 15;
	float **xes = (float**)malloc(trainSize * sizeof(float*));
	float *xess = malloc(sizeof(float)*trainSize);
	float **yes = (float**)malloc(trainSize * sizeof(float*));
	float *yess = malloc(sizeof(float)*trainSize);
	float *ty = malloc(sizeof(float)*trainSize);
	float *y = malloc(sizeof(float)*testSize);
	float *recTesty = malloc(sizeof(float)*testSize);
	float *recTrainy = malloc(sizeof(float)*trainSize);
	float **x = (float**)malloc(sizeof(float*)*testSize);
	float *beta = malloc(sizeof(float)*(argNum + 1));
	
	puts("which algorithm do you want to use?\n1: lin reg sum 1\n2: lin reg sum 2\n3: gradient descent");
	char in;
	scanf("%c", &in);

	char algoritm = in;
	if (readcsv("input.csv", 0.3, xes, yes, x, y, &testSize, &trainSize, &argNum) == -1)
	{
		printf("Couldnt open specified file data will be generated automatically instead");
		for (int i = 0; i < testSize; i++)
		{
			x[i] = (float *)malloc(argNum * sizeof(float));
			for (int j = 0; j < argNum; j++)
			{
				x[i][j] = (i + 1) * (j + 1);;
			}
			y[i] = i + 4;
		}

		//float *xes = malloc(sizeof(float)*trainSize);
		//float *yes = malloc(sizeof(float)*trainSize);
		for (int i = 0; i < trainSize; i++)
		{
			xes[i] = (float *)malloc(argNum * sizeof(float));
			yes[i] = (float *)malloc(sizeof(float));
			yess[i] = i + 4;
			xess[i] = i;
			for (int j = 0; j < argNum; j++)
			{
				xes[i][j] = i * (j + 1);
				//printf("%f ", xes[i][j]);
			}
			//printf("\n");
			yes[i][0] = i + 4;

			xes[i][0] = i;
			//printf("x:%f y:%f\n", xes[i][0], yes[i][0]);
		}
	}
	//double xes[] = { 1,2,3,4,5 };
	//double yes[] = { 3,4,5,6,7 };
	lin_reg lr;
	kann_t *ann;
	kad_node_t *t;
	getchar();
	puts("Normalize data? y/n");
	scanf("%c", &in);
	if (in == 'y')
	{
		normalizeData(xes, yes, x, y, trainSize, testSize, argNum);
	}
	if (algoritm == '3')
	{
		gradRegWrapper(xes, yes, trainSize, argNum, beta, 100000);
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
	else if (algoritm == '1')
	{
		linRegWrapper(xes, yes, trainSize, argNum, beta);
	}
	else if (algoritm == '2')
	{
		linRegWrapper2(xes, yes, trainSize, argNum, beta);
	}
	else
	{
		puts("incorect input");
	}

	if (algoritm == '1' || algoritm == '2' || algoritm == '3')
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
	free(x);
	free(beta);
	free(xes);
	free(yess);
	free(yes);
	free(xess);
	getchar();
	getchar();

}

