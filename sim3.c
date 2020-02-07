//Preprocessors 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Data Types

//Prototypes

//Main Program
int main()
{
	unsigned int seed;
	long curr_pop, doves, delta1, delta2;
	long eaten=0, gen=1, len=10, avg=0;
	int *hash_map = (int*)malloc(len*sizeof(int));
	int *type_map = (int*)malloc(len*sizeof(int));
	float m, ratio;
	long food, initialf;

	scanf("%u", &seed);
	srand(seed);

	printf("Enter initial food: ");
	scanf("%ld", &food);
	initialf = food;
	printf("Enter initial population: ");
	scanf("%ld", &curr_pop);
	printf("Enter initial population ratio: ");
	scanf("%f", &ratio);
	printf("Enter rate of food replenishment: ");
	scanf("%f", &m);

	doves = ratio*curr_pop;

	while(curr_pop)
	{
		delta1=0;
		delta2=0;
		eaten=0;
		int j=doves;

		if(curr_pop > len/2)
		{
			len *= 2;
			hash_map = (int*)realloc(hash_map, len*sizeof(int));
			type_map = (int*)realloc(type_map, len*sizeof(int));
		}
		for(int i=0;i<len;i++)
		{
			type_map[i] = -1;
			hash_map[i] = -2;
		}

		for(int i=0;i<curr_pop;i++)
		{
			int t2;

			if(eaten >= food && i>=2*food)
			{
				delta1 -= j;
				delta2 -= curr_pop-(i+1-doves+j);
				break;
			}

			int t1 = rand()%food;
			while(hash_map[t1%len] == -1)
				t1 = rand()%food;

			if(j > 0 && curr_pop-(i+1-doves+j) > 0)
				t2 = rand()%2;
			else if(j <= 0)
				t2 = 1;
			else
				t2 = 0;

			if(!t2)
				j--;

			if(hash_map[t1%len] == t1)
			{
				hash_map[t1%len] = -1;
				if(type_map[t1%len] == t2)
				{
					if(t2)
						delta2 -= 3;
				}
				else
				{
					if(type_map[t1%len] == 0)
						delta1--;
					else
						delta2--;

					int t3 = rand()%2;
					int t4 = rand()%2;

					if(!t3)
						delta1--;
					if(t4)
						delta2++;
				}
			}
			else if(hash_map[t1%len] == -2)
			{
				hash_map[t1%len] = t1;
				type_map[t1%len] = t2;
				if(!t2)
					delta1++;
				else
					delta2++;
				eaten++;
			}
			else
			{
				int k=0;
				while(!hash_map[(t1+k)%len])
				{
					if(hash_map[(t1+k)%len] == t1)
					{
						hash_map[(t1+k)%len] = -1;
						if(type_map[t1%len] == t2)
						{
							if(t2)
								delta2 -= 3;
						}
						else
						{
							if(type_map[t1%len] == 0)
								delta1--;
							else
								delta2--;

							int t3 = rand()%2;
							int t4 = rand()%2;

							if(!t3)
								delta1--;
							if(t4)
								delta2++;
						}
						break;
					}
					k++;
				}
				if(!hash_map[(t1+k)%len])
				{
					hash_map[(t1+k)%len] = t1;
					type_map[t1%len] = t2;
					if(!t2)
						delta1++;
					else
						delta2++;
					eaten++;
				}
			}
		}

		curr_pop += delta1+delta2;
		if(gen > 15)
		{
			if(avg != 0)
				avg = ((avg*gen)+curr_pop)/(gen+1);
			else
				avg = curr_pop;
		}

		if(curr_pop < 10000)
			sleep(1);

		doves += delta1;
		ratio = (float)doves/(curr_pop);

		printf("Generation: %ld\n", gen);
		printf("Old Population: %ld\n", curr_pop-delta1-delta2);
		printf("New Population: %ld\n", curr_pop);
		printf("Average Population: %ld\n", avg);
		printf("Population ratio: %f\n", ratio);
		gen++;
		if(food >= eaten)
			food -= eaten;
		printf("Food level: %ld\n", food);


		if(m != -1)
			food = m*food+25;
		else
			food = initialf;
	}

	return 0;
}

//Definitions
