#include "GradientReg.h"
#include "customReg.h"
#include <stdlib.h>

void gradRegWrapper(float** xes, float** yes, int size, int numArgs, float* ans, int maxIters) {
	float lr = 1.0 /(float) (maxIters*maxIters);
	for (int i = 0; i < numArgs + 1; i++)
	{
		ans[i] = 0;
	}
	for (int i = 0; i < maxIters; i++)
	{
		for (int j = 0; j < numArgs + 1; j++)
		{
			float sum = 0;
			for (int k = 0; k < size; k++)
			{
				float innerSum = ans[0];
				for (int p = 1; p < numArgs + 1; p++)
				{
					innerSum += ans[p] * xes[k][p-1];
				}
				innerSum -= yes[k][0];
				if (j != 0)
				{
					innerSum = innerSum * xes[k][j - 1];
				}
				sum += innerSum;
			}
			float change = (float) lr * (1.0 / (float) size) * sum;
			ans[j] -= change;
		}
	}

}