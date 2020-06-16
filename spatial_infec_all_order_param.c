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

void s_inf(double *x_1, double *x_2, int *t, double cut_off, int n);
void s_inf(double *x_1, double *x_2, int *t, double cut_off, int n)
{
    int i, j;
	double complex R;
	const double pi = 4.0 * atan(1.0);
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			if(j != i)
			{
				if(t[j] == 0)
				{
					R = cexp(I * 2.0 * pi * x_1[j]) + cexp(I * 2.0 * pi * x_1[i]);

					if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
					{
						t[j] = 1;
					}
				}
				if(t[j + n] == 0)
				{
					R = cexp(I * 2.0 * pi * x_2[j]) + cexp(I * 2.0 * pi * x_2[i]);
				
					if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
					{
						t[j + n] = 1;
					}
				} 
			}
			if(t[j] == 0)
			{
				R = cexp(I * 2.0 * pi * x_1[j]) + cexp(I * 2.0 * pi * x_2[i]);
				
				if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
				{
					t[j] = 1;
				}
			}
			if(t[j + n] == 0)
			{
				R = cexp(I * 2.0 * pi * x_2[j]) + cexp(I * 2.0 * pi * x_1[i]);
			
				if(fabs(cabs(R/2.0) - 1.0) <= cut_off)
				{
					t[j + n] = 1;
				}
			}
		}
	}
}
