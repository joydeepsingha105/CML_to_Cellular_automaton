#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>

/* 
 *this code finds the transitional probabilities 0 -> 0, 0 -> 1, 1 -> 0, 1 -> 1 
 *given the sum of ones at the initial time are fixed 
 */

void transition(int *t_1, int *t_2, int ***p_sum_trans, int sum_1, int sum_2, int n);
void transition(int *t_1, int *t_2, int ***p_sum_trans, int sum_1, int sum_2, int n)
{
	int i;
	p_sum_trans[sum_1][sum_2][0] = p_sum_trans[sum_1][sum_2][0] + 1;
	
	//group one
	for(i = 0;i < n;i++)
	{
		if(t_1[i] == 0)
		{
			if(t_2[i] == 0)
			{
				p_sum_trans[sum_1][sum_2][1] = p_sum_trans[sum_1][sum_2][1] + 1;
			}
			else if(t_2[i] == 1)
			{
				p_sum_trans[sum_1][sum_2][2] = p_sum_trans[sum_1][sum_2][2] + 1;
			}
		}
		else if(t_1[i] == 1)
		{
			if(t_2[i] == 0)
			{
				p_sum_trans[sum_1][sum_2][3] = p_sum_trans[sum_1][sum_2][3] + 1;
			}
			else if(t_2[i] == 1)
			{
				p_sum_trans[sum_1][sum_2][4] = p_sum_trans[sum_1][sum_2][4] + 1;
			}
		}
	}

	//group two
	for(i = n;i < (2 * n);i++)
	{
		if(t_1[i] == 0)
		{
			if(t_2[i] == 0)
			{
				p_sum_trans[sum_1][sum_2][5] = p_sum_trans[sum_1][sum_2][5] + 1;
			}
			else if(t_2[i] == 1)
			{
				p_sum_trans[sum_1][sum_2][6] = p_sum_trans[sum_1][sum_2][6] + 1;
			}
		}
		else if(t_1[i] == 1)
		{
			if(t_2[i] == 0)
			{
				p_sum_trans[sum_1][sum_2][7] = p_sum_trans[sum_1][sum_2][7] + 1;
			}
			else if(t_2[i] == 1)
			{
				p_sum_trans[sum_1][sum_2][8] = p_sum_trans[sum_1][sum_2][8] + 1;
			}
		}
	}

}


