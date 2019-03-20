#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customReg.h"
#include "kann.h"


void main()
{
	int trainSize = 9999;
	int testSize = 15;
	float **xes = (float**)malloc(trainSize * sizeof(float*));
	float *xess = malloc(sizeof(float)*trainSize);
	float **yes = (float**)malloc(trainSize * sizeof(float*));
	float *yess = malloc(sizeof(float)*trainSize);
	float *y = malloc(sizeof(float)*testSize);
	float *x = malloc(sizeof(float)*testSize);
	while (getchar != 'q')
	{
		puts("which algorithm do you want to use?\n0: MLP\n1: linear regression\n2: different implementation");
		char in;
		scanf("%c", &in);

		char algoritm = in;
		

		
		for (int i = 0; i < testSize; i++)
		{
			x[i] = i + 2;
		}

		//float *xes = malloc(sizeof(float)*trainSize);
		//float *yes = malloc(sizeof(float)*trainSize);
		for (int i = 0; i < trainSize; i++)
		{
			xes[i] = (float *)malloc(sizeof(float));
			yes[i] = (float *)malloc(sizeof(float));
			yess[i] = i + 4;
			xess[i] = i;
			xes[i][0] = i;
			yes[i][0] = i * i;
			//printf("x:%f y:%f\n", xes[i][0], yes[i][0]);
		}

		//double xes[] = { 1,2,3,4,5 };
		//double yes[] = { 3,4,5,6,7 };
		lin_reg lr;
		kann_t *ann;
		kad_node_t *t;
		if (algoritm == '0')
		{
			t = kann_layer_input(1); // for MNIST
			t = kad_relu(kann_layer_dense(t, 64)); // a 64-neuron hidden layer with ReLU activation
			t = kann_layer_cost(t, 1, KANN_C_MSE); // softmax output + multi-class cross-entropy cost
			ann = kann_new(t, 0);                   // compile the network and collate variables
			kann_train_fnn1(ann, 0.001f, 64, 100, 10, 0.1f, trainSize, xes, yes);
			y = kann_apply1(ann, x);
			for (int i = 0; i < testSize; i++)
			{
				printf("prediction for %f = %f\n", x[i], y[i]);
			}
		}
		else if (algoritm == '1')
		{
			linReg(xess, yess, trainSize, &lr);
			printf("y = %fx + %f\n", lr.a, lr.b);
			for (int i = 0; i < testSize; i++)
			{
				printf("prediction for %f = %f\n", x[i], lr.a * x[i] + lr.b);
			}
		}
		else if (algoritm == '2')
		{
			float m, b, r;
			linreg(trainSize, xess, yess, &m, &b, &r);
			printf("y = %fx + %f\n", m, b);
			for (int i = 0; i < testSize; i++)
			{
				printf("prediction for %f = %f\n", x[i], m * x[i] + b);
			}
		}
		else
		{
			puts("incorect input");
		}

	}
	free(y);
	free(x);
	for (int i = 0; i < trainSize; i++)
	{
		free(xes[i]);
		free(yes[i]);
	}
	free(xes);
	free(yes);
	free(xess);
	//kann_delete(ann);
}

