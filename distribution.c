#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
	FILE *int_ptr;
//	FILE *out_ptr;

//	out_ptr = fopen("distribution_150_probability_p00.txt","w");
	int_ptr = fopen("probability_distribution_of_sum_of_ones.txt","r");

//	int tot_box, i; 
//	double box_size;
//	double **dist;
	char line[256];
	double dummy, value, avg;

//	tot_box = 100;
//	box_size = 1.0/100.0;

//	int count_1 = 0, count_2 = 0;


//	dist = (double **) malloc(tot_box * sizeof(double *));
//	for(i = 0;i < tot_box;i++)
//	{
//		dist[i] = (double *) malloc(2 * sizeof(double));
//		dist[i][0] = (i * box_size) + (box_size/2.0);
//		dist[i][1] = 0.0;
//	}

	avg = 0.0;
	while(fgets(line, sizeof(line), int_ptr)!= NULL)
	{
		if(line[0] == '#')
		{
			continue;
		}
		sscanf(line,"%lf%lf%lf", &dummy, &value, &value);
		avg = avg + value;
//		for(i = 0;i < tot_box;i++)
//		{
//			if(value != 0.0)
//			{
//				if((value >= (dist[i][0] - (box_size/2.0))) && (value < (dist[i][0] + (box_size/2.0))))
//				{
//					dist[i][1] = dist[i][1] + 1.0;
//					break;
//				}
//			}
//		}
//		if(value != 0.0)
//		{
//			count_1 = count_1 + 1;
//		}
//		printf("%e\n",value);
	}
	
//	sum = 0.0;
//	for(i = 0;i < tot_box;i++)
//	{
//		sum = sum + dist[i][1];
//	}
//	for(i = 0;i < tot_box;i++)
//	{
//		fprintf(out_ptr, "%e\t%e\n", dist[i][0], dist[i][1]/sum);
//		count_2 = count_2 + dist[i][1];	  
//	}

	printf("%e\n", avg);
		
	return(0);
}		
