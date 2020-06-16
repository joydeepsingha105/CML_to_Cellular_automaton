#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double modulo_1(double *phase);
double modulo_1(double *phase)
{
 	double value;
	int l;	
	value = *phase;
	l = value/1.0;
	if(value > 0)
	{
		value = value - l;
	}					
	else if(value < 0)
	{
		value = value - l + 1.0;
	}
	*phase = value;
	return(0);
}
