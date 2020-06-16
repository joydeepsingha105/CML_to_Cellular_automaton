#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double iterate (double K, double omega, double eps_1, double *x_1, double *x_2, int n);
double modulo_1(double *phase);
double iterate (double K, double omega, double eps_1, double *x_1, double *x_2, int n)
{
		
	int i,j,k;
	double *y_1;
	double *y_2;
	double eps_2;
	double sum_1;
	double sum_2;
	int m;

 	y_1 = (double *) malloc(n * sizeof(double));
	y_2 = (double *) malloc(n * sizeof(double));
	if(y_1 == NULL)
	{
		printf("cannot allocate memory for y_1\n");
	}
	if(y_2 == NULL)
	{
		printf("cannot allocate memory for y_2\n");
	}	
	const double pi = 4. * atan(1.0);
	eps_2 = 1.0 - eps_1;

	sum_1 = 0.0;
	sum_2 = 0.0;
	for(k = 0; k < n; k++)
	{	
		sum_2 = sum_2 + x_2[k] + omega - ((K/(2.0 * pi)) * sin(2.0 * pi * x_2[k]));
		sum_1 = sum_1 + x_1[k] + omega - ((K/(2.0 * pi)) * sin(2.0 * pi * x_1[k]));
	}
	for(i = 0;i < n;i++)
	{	
		y_1[i] = ((2.0 - eps_1 - eps_2) * (x_1[i] + omega - ((K/(2.0 * pi)) * sin(2.0 * pi * x_1[i])))) + ((eps_1/n) * sum_1) + ((eps_2/n) * sum_2);
		modulo_1(&y_1[i]);
		x_1[i] = y_1[i];
		y_2[i] = ((2.0 - eps_1 - eps_2) * (x_2[i] + omega - ((K/(2.0 * pi)) * sin(2.0 * pi * x_2[i])))) + ((eps_2/n) * sum_1) + ((eps_1/n) * sum_2);
		modulo_1(&y_2[i]);
		x_2[i] = y_2[i];
	}
	free(y_1);
	free(y_2);
	return(0);
}
