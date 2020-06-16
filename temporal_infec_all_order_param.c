//
//  ca_calc.c
//  
//
//  Created by Joydeep on 25/05/17.
//
//

#include<stdio.h>
#include<math.h>
#include<complex.h>

void t_inf(double *x_1, double *x_2, double *y_1, double *y_2, int *t_1, int *t_2, double cut_off, int n);
void t_inf(double *x_1, double *x_2, double *y_1, double *y_2, int *t_1, int *t_2, double cut_off, int n)
{
        int i, j;
	double complex R;
	const double pi = 4.0 * atan(1.0);
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			if(t_2[j] == 0)
			{
				R = cexp(I * 2.0 * pi * x_1[j]) + cexp(I * 2.0 * pi * y_1[i]);

				if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
				{
					t_2[j] = 1;

					if(t_1[i] == 0)
					{
						t_1[i] = 1;
					}					
				}

				R = cexp(I * 2.0 * pi * x_1[j]) + cexp(I * 2.0 * pi * y_2[i]);

				if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
				{
					t_2[j] = 1;
					
					if(t_1[i + n] == 0)
					{
						t_1[i + n] = 1;
					}	
				}

			}
			if(t_2[j + n] == 0)
			{
				R = cexp(I * 2.0 * pi * x_2[j]) + cexp(I * 2.0 * pi * y_2[i]);

				if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
				{
					t_2[j + n] = 1;
						
					if(t_1[i + n] == 0)
					{
						t_1[i + n] = 1;
					}					
				}

				R = cexp(I * 2.0 * pi * x_2[j]) + cexp(I * 2.0 * pi * y_1[i]);

				if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
				{
					t_2[j + n] = 1;

					if(t_1[i] == 0)
					{
						t_1[i] = 1;
					}
				}

			}
		}
	}
}
