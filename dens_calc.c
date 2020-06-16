#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void calc_density(FILE *out_ptr, double *m_1_stable, double *m_2_stable, double *m_1_mean, double *m_2_mean, double *a_1, double *b_1, double *a_2, double *b_2, int n);
void calc_density(FILE *out_ptr, double *m_1_stable, double *m_2_stable, double *m_1_mean, double *m_2_mean, double *a_1, double *b_1, double *a_2, double *b_2, int n)
{
	char line[256];
	double prob_sum, p_1_01, p_1_11, p_2_01, p_2_11, dummy;//to store the values of the conditional probabilities 
	int sum_1, sum_2; //to check the values of x_1 and x_2
	
	double sum_1_1, sum_2_1, sum_3_1, sum_4_1;
	double sum_1_2, sum_2_2, sum_3_2, sum_4_2;
	
	*m_1_stable = 0.0;
	*m_2_stable = 0.0;

	*m_1_mean = 0.0;
	*m_2_mean = 0.0;

	sum_1_1 = 0.0; 
	sum_2_1 = 0.0; 
	sum_3_1 = 0.0; 
	sum_4_1 = 0.0; 

	sum_1_2 = 0.0;
	sum_2_2 = 0.0;
	sum_3_2 = 0.0;
	sum_4_2 = 0.0;


	while(fgets(line, sizeof(line), out_ptr)!= NULL)
	{
		if(line[0] == '#')
		{
			continue;
		}
		sscanf(line,"%d%d%lf%lf%lf%lf%lf%lf%lf%lf%lf",&sum_1, &sum_2, &prob_sum, &dummy, &p_1_01, &dummy, &p_1_11, &dummy, &p_2_01, &dummy, &p_2_11);

		//for group two
		if(sum_2 == 0)
		{
			*m_2_stable = *m_2_stable + (prob_sum * p_2_01);
		
			sum_1_2 = sum_1_2 + (prob_sum * p_2_01);
		}
		else if(sum_2 == n)
		{
			*m_2_stable = *m_2_stable + (prob_sum * p_2_11);

			sum_2_2 = sum_2_2 + (prob_sum * p_2_11);
		}
		else if((sum_2 > 0) && (sum_2 < n))
		{
			*m_2_stable = *m_2_stable + (prob_sum * p_2_01 * ((double)(n - sum_2)/(double)n));
			*m_2_stable = *m_2_stable + (prob_sum * p_2_11 * ((double)sum_2/(double)n));

			sum_3_2 = sum_3_2 + (prob_sum * p_2_01);
			sum_4_2 = sum_4_2 + (prob_sum * p_2_11) - (prob_sum * p_2_01);
			
		}
		
		//for group one
		if(sum_1 == 0)
		{
			*m_1_stable = *m_1_stable + (prob_sum * p_1_01);
	
			sum_1_1 = sum_1_1 + (prob_sum * p_1_01);
		}
		else if(sum_1 == n)
		{
			*m_1_stable = *m_1_stable + (prob_sum * p_1_11);

			sum_2_1 = sum_2_1 + (prob_sum * p_1_11);
		}
		else if((sum_1 > 0) && (sum_1 < n))
		{
			*m_1_stable = *m_1_stable + (prob_sum * p_1_01 * ((double)(n - sum_1)/(double)n));
			*m_1_stable = *m_1_stable + (prob_sum * p_1_11 * ((double)sum_1/(double)n));

			sum_3_1 = sum_3_1 + (prob_sum * p_1_01);
			sum_4_1 = sum_4_1 + (prob_sum * p_1_11) - (prob_sum * p_1_01);
		}
	}
	
	*m_1_mean = (sum_1_1 + sum_2_1 + sum_3_1)/(1.0 - sum_4_1);

	*m_2_mean = (sum_1_2 + sum_2_2 + sum_3_2)/(1.0 - sum_4_2);

	*a_1 = sum_4_1;
	*b_1 = sum_1_1 + sum_2_1 + sum_3_1;

	*a_2 = sum_4_2;
	*b_2 = sum_1_2 + sum_2_2 + sum_3_2;
}

