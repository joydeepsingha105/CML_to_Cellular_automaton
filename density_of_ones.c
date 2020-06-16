#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>

/* 
 * Probability of the occurence of a given sum of ones at a time step is calculated
 *
 * Probability of transitions i.e. 0 -> 0, 0 -> 1, 1 -> 0, 1 -> 1 are calculated such that the sum of ones 
 * at the intiial time have a particular non-zero value
*/

void iterate (double K, double omega, double eps_1, double *x_1, double *x_2, int n); 		/*iterate the CML*/
void modulo_1(double *phase);

void t_inf(double *x_1, double *x_2, double *y_1, double *y_2, int *t_1, int *t_2, double cut_off, int n); 	/*temporal infection*/
void s_inf(double *x_1, double *x_2, int *t, double cut_off, int n); 				/*spatial infection*/

void transition(int *t_1, int *t_2, int ***p_sum_trans, int sum_1, int sum_2, int n);
void calc_density(FILE *out_ptr, double *m_1_stable, double *m_2_stable, double *m_1_mean, double *m_2_mean, double *a_1, double *b_1, double *a_2, double *b_2, int n);

int main (void)
{		
	int n, i, j, k, l, max_iter, per;
	
	double *x_1, *x_2, *y_1, *y_2;
    int *t_1, *t_2, *t_3;
	char line[256];

	int sum_1, sum_2;

	double K, omega, eps_1;

	double cut_off;                                     /*cutoff to find laminer and burst*/
	int ***p_sum_trans;

	double m_1_stable, m_2_stable, m_1_mean, m_2_mean, a_1, b_1, a_2, b_2;
	int zero_gr_1, one_gr_1, zero_gr_2, one_gr_2;

	max_iter = 4100000;
    per = 2000000;
	n = 150;
          
	x_1 = (double *) malloc(n * sizeof(double));		 /*arrays to save the phases of the maps*/
	x_2 = (double *) malloc(n * sizeof(double));
	y_1 = (double *) malloc(n * sizeof(double));		 /*arrays to save the phases of the maps*/
	y_2 = (double *) malloc(n * sizeof(double));
	
	
	t_1 = (int *) malloc((2 * n) * sizeof(int));    /*array to to save the zero and one for the automata*/
	t_2 = (int *) malloc((2 * n) * sizeof(int));
	t_3 = (int *) malloc((2 * n) * sizeof(int));

	p_sum_trans = (int ***) malloc((n + 1) * sizeof(int **));
	for(i = 0;i < (n + 1);i++)
	{
		p_sum_trans[i] = (int **) malloc((n + 1) * sizeof(int*));
		for(j = 0;j < (n + 1);j++)
		{
			p_sum_trans[i][j] = (int *) malloc(9 * sizeof(int));
		}
	}

	if(x_1 == NULL)
	{
		printf("cannot allocate memory for x_1\n");
		exit(1);
	}
	if(x_2 == NULL)
	{
		printf("cannot allocate memroy for x_2\n");
		exit(1);
	}
	if(y_1 == NULL)
	{
		printf("cannot allocate memory for y_1\n");
		exit(1);
	}
	if(y_2 == NULL)
	{
		printf("cannot allocate memroy for y_2\n");
		exit(1);
	}
	if(t_1 == NULL)
	{
		printf("cannot allocate memory for t_1\n");
		exit(1);
	}
	if(t_2 == NULL)
	{
		printf("cannot allocate memory for t_2\n");
	}
	if(t_3 == NULL)
	{
		printf("cannot allocate memory for t_3\n");
	}
	if(p_sum_trans == NULL)
	{
		printf("cannot allocate memory for p_sum_trans\n");
	}
	
	K = pow(10, -5); 
	omega = 0.27;
	eps_1 = 0.93;
	

	FILE *out_ptr;
	FILE *loop_data;
	loop_data = fopen("density_data_time_step_2000000.txt","w");

	out_ptr = fopen("initial_condition_150.txt","r");
	i = 0;
	while(fgets(line, sizeof(line), out_ptr)!= NULL)      /*scanning the initial condition*/
	{
		sscanf(line, "%lf%lf",&x_2[i],&x_1[i]);
		i++;
	}
	fclose(out_ptr);

	cut_off = 0.000001;
	
	for(i = 0;i < (n + 1);i++)
	{		
		for(j = 0;j < (n + 1);j++)
		{
			for(k = 0;k < 9;k++)
			{
				p_sum_trans[i][j][k] = 0;
			}
		}
	}	


	zero_gr_1 = 0; //intialization of the counters 
	one_gr_1 = 0;
	zero_gr_2 = 0;
	one_gr_2 = 0;

	for(i = 0;i < n;i++)
	{
		t_1[i] = 0;
		t_1[i + n] = 0;

		t_2[i] = 0;
		t_2[i + n] = 0;

		t_3[i] = 0;
		t_3[i + n] = 0;
	}

	for(j = 0;j < max_iter;j++)
	{
		iterate(K, omega, eps_1, x_1, x_2, n);          /*iterating the function*/
		if(j == (per - 1))				/*initialising the arrays*/
		{
			for(i = 0;i < n;i++)
			{
				y_1[i] = x_1[i];
				y_2[i] = x_2[i];				
			}			
		}
		if(j == per)
		{  
			t_inf(x_1, x_2, y_1, y_2, t_1, t_2, cut_off, n);
	
			s_inf(x_1, x_2, t_2, cut_off, n);

			for(i = 0;i < n;i++)
			{
				y_1[i] = x_1[i];
				y_2[i] = x_2[i];

				t_1[i] = t_2[i];
				t_1[i + n] = t_2[i + n];
						
				t_2[i] = 0;
				t_2[i + n] = 0; 	
			}
		}
		if(j == (per + 1))
		{
			t_inf(x_1, x_2, y_1, y_2, t_1, t_2, cut_off, n);

			s_inf(x_1, x_2, t_2, cut_off, n);
			for(i = 0;i < n;i++)
			{
				y_1[i] = x_1[i];
				y_2[i] = x_2[i];
			}
		}	

		if(j > (per + 1))
		{
			t_inf(x_1, x_2, y_1, y_2, t_2, t_3, cut_off, n);
			
			s_inf(x_1, x_2, t_3, cut_off, n);

			sum_1 = 0;
			for(i = 0;i < n;i++)
			{
			        sum_1 = sum_1 + t_1[i];
			}
			
			one_gr_1 = one_gr_1 + sum_1;
			zero_gr_1 = zero_gr_1 + (n - sum_1);			

			sum_2 = 0;
			for(i = n;i < (2 * n);i++)
			{
				sum_2 = sum_2 + t_1[i];
			}

			one_gr_2 = one_gr_2 + sum_2;
			zero_gr_2 = zero_gr_2 + (n - sum_2);			

			transition(t_1, t_2, p_sum_trans, sum_1, sum_2, n);
            														            
			for(i = 0;i < n;i++)
			{			
				y_1[i] = x_1[i];
				y_2[i] = x_2[i];
				
				t_1[i] = t_2[i];
				t_1[i + n] = t_2[i + n];

				t_2[i] = t_3[i];
				t_2[i + n] = t_3[i + n];
			
				t_3[i] = 0;
				t_3[i + n] = 0;	
			}					
		}
        printf("\r%d",j);
	}

	sum_1 = 0;
	for(i = 0;i < (n + 1);i++)
	{	
		for(j = 0;j < (n + 1);j++)
		{			
			sum_1 = sum_1 + p_sum_trans[i][j][0];
		}
	}	
	
		//P[sum_gr_1][sum_gr_2][0] = probability of a combination of sums 

		//P[sum_gr_1][sum_gr_2][1] = probability of 0 -> 0 transition in group one given a combination of sums 
		//P[sum_gr_1][sum_gr_2][2] = probability of 0 -> 1 transition in group one given a combination of sums 
		//P[sum_gr_1][sum_gr_2][3] = probability of 1 -> 0 transition in group one given a combination of sums 
		//P[sum_gr_1][sum_gr_2][4] = probability of 1 -> 1 transition in group one given a combination of sums 

		//P[sum_gr_1][sum_gr_2][5] = probability of 0 -> 0 transition in group two given a combination of sums 
		//P[sum_gr_1][sum_gr_2][6] = probability of 0 -> 1 transition in group two given a combination of sums 
		//P[sum_gr_1][sum_gr_2][7] = probability of 1 -> 0 transition in group two given a combination of sums 
		//P[sum_gr_1][sum_gr_2][8] = probability of 1 -> 1 transition in group two given a combination of sums 

	out_ptr = fopen("sum_trans_prob.txt","w");
  	for(i = 0;i < (n + 1);i++)
	{
		for(j = 0;j < (n + 1);j++)
		{		
			//data output for group one 	
			if(p_sum_trans[i][j][0] != 0)
			{	
				fprintf(out_ptr, "%d\t%d\t%e\t", i, j, (double)p_sum_trans[i][j][0]/sum_1);
		
				if((p_sum_trans[i][j][1] + p_sum_trans[i][j][2]) != 0)
				{
					fprintf(out_ptr,"%e\t%e\t",(double)p_sum_trans[i][j][1]/(double)(p_sum_trans[i][j][1] + p_sum_trans[i][j][2]), (double)p_sum_trans[i][j][2]/(double)(p_sum_trans[i][j][1] + p_sum_trans[i][j][2]));
				}
				else if((p_sum_trans[i][j][1] + p_sum_trans[i][j][2]) == 0)
				{
					fprintf(out_ptr,"0.0\t\t0.0\t\t");
				}

				if((p_sum_trans[i][j][3] + p_sum_trans[i][j][4]) != 0)
				{
					fprintf(out_ptr,"%e\t%e\t",(double)p_sum_trans[i][j][3]/(double)(p_sum_trans[i][j][3] + p_sum_trans[i][j][4]), (double)p_sum_trans[i][j][4]/(double)(p_sum_trans[i][j][3] + p_sum_trans[i][j][4]));
				}
				else if((p_sum_trans[i][j][3] + p_sum_trans[i][j][4]) == 0)
				{
					fprintf(out_ptr,"0.0\t\t0.0\t");
				}
			
				if((p_sum_trans[i][j][5] + p_sum_trans[i][j][6]) != 0)
				{
					fprintf(out_ptr,"%e\t%e\t",(double)p_sum_trans[i][j][5]/(double)(p_sum_trans[i][j][5] + p_sum_trans[i][j][6]), (double)p_sum_trans[i][j][6]/(double)(p_sum_trans[i][j][5] + p_sum_trans[i][j][6]));
				}
				else if((p_sum_trans[i][j][5] + p_sum_trans[i][j][6]) == 0)
				{
					fprintf(out_ptr,"0.0\t\t0.0\t\t");
				}
				if((p_sum_trans[i][j][7] + p_sum_trans[i][j][8]) != 0)
				{
					fprintf(out_ptr,"%e\t%e\n",(double)p_sum_trans[i][j][7]/(double)(p_sum_trans[i][j][7] + p_sum_trans[i][j][8]), (double)p_sum_trans[i][j][8]/(double)(p_sum_trans[i][j][7] + p_sum_trans[i][j][8]));
				}
				else if((p_sum_trans[i][j][7] + p_sum_trans[i][j][8]) == 0)
				{	
					fprintf(out_ptr,"0.0\t\t0.0\n");
				}
			}		
		}
	}	
	fclose(out_ptr);
	out_ptr = fopen("sum_trans_prob.txt","r");
	calc_density(out_ptr, &m_1_stable, &m_2_stable, &m_1_mean, &m_2_mean, &a_1, &b_1, &a_2, &b_2, n);
	fclose(out_ptr);

	fprintf(loop_data,"%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n", eps_1, m_1_stable, m_2_stable, m_1_mean, m_2_mean, a_1, b_1, a_2, b_2, (double)one_gr_1/(double)(one_gr_1 + zero_gr_1), (double)one_gr_2/(double)(one_gr_2 + zero_gr_2));
	printf("%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n",eps_1, m_1_stable, m_2_stable, m_1_mean, m_2_mean, a_1, b_1, a_2, b_2, (double)one_gr_1/(double)(one_gr_1 + zero_gr_1), (double)one_gr_2/(double)(one_gr_2 + zero_gr_2));


	fclose(loop_data);

	free(x_1);
	free(x_2);
	free(y_1);
	free(y_2);
    free(t_1);
	free(t_2);
    
	return(0);
}
