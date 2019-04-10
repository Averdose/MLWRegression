#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customReg.h"
#include "kann.h"



void main()
{
	int argNum = 3;
	int trainSize = 80;
	int testSize = 15;
	float **xes = (float**)malloc(trainSize * sizeof(float*));
	float *xess = malloc(sizeof(float)*trainSize);
	float **yes = (float**)malloc(trainSize * sizeof(float*));
	float *yess = malloc(sizeof(float)*trainSize);
	float *y = malloc(sizeof(float)*testSize);
	float **x = malloc(sizeof(float)*testSize);
	float *beta = malloc(sizeof(float)*(argNum + 1));
	
	puts("which algorithm do you want to use?\n0: MLP\n1: linear regression\n2: different implementation");
	char in;
	scanf("%c", &in);

	char algoritm = in;
		

		
	for (int i = 0; i < testSize; i++)
	{
		x[i] = (float *)malloc(argNum * sizeof(float));
		for (int j = 0; j < argNum; j++)
		{
			x[i][j] = (i +1) * (j + 1);;
		}
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
			xes[i][j] = i*(j+1);
			//printf("%f ", xes[i][j]);
		}
		//printf("\n");
		yes[i][0] = i + 4;

		xes[i][0] = i;
		//printf("x:%f y:%f\n", xes[i][0], yes[i][0]);
	}

	//double xes[] = { 1,2,3,4,5 };
	//double yes[] = { 3,4,5,6,7 };
	lin_reg lr;
	kann_t *ann;
	kad_node_t *t;
	if (algoritm == '0')
	{
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
	}
	else if (algoritm == '1')
	{
		linRegWrapper(xes, yes, trainSize, argNum, beta);
		linReg(xess, yess, trainSize, &lr);
		//printf("y = %fx + %f\n", lr.a, lr.b);
		print2(beta, argNum + 1);
		for (int i = 0; i < testSize; i++)
		{
			float val = beta[0];
			printf("prediction for ");
			for(int j = 1; j < (argNum + 1); j++)
			{
				printf("x[%d] = %f ", j - 1, x[i][j - 1]);
				val += beta[j] * x[i][j - 1];
			}
			printf(" = %f\n", val);
		}
	}
	else if (algoritm == '2')
	{
		float m, b, r;
		linreg(trainSize, xess, yess, &m, &b, &r);
		printf("y = %fx + %f\n", m, b);
		for (int i = 0; i < testSize; i++)
		{
			//printf("prediction for %f = %f\n", x[i], m * x[i] + b);
		}
	}
	else
	{
		puts("incorect input");
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
}

