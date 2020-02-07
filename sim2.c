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
	long curr_pop=1, delta=1, eaten=0, gen=1, len=10, avg=0;
	int *hash_map = (int*)malloc(len*sizeof(int));
	float m;
	long food, initialf;

	scanf("%u", &seed);
	srand(seed);

	printf("Enter initial food: ");
	scanf("%ld", &food);
	initialf = food;
	printf("Enter rate of food replenishment: ");
	scanf("%f", &m);

	while(curr_pop)
	{

		delta=0;
		eaten=0;
		if(curr_pop > len/2)
		{
			len *= 2;
			hash_map = (int*)realloc(hash_map, len*sizeof(int));
		}

		for(int i=0;i<len;i++)
			hash_map[i] = -2;

		for(int i=0;i<curr_pop;i++)
		{
			if(eaten >= food && i>=2*food)
			{
				delta -= curr_pop-i;
				break;
			}

			int t = rand()%food;
			while(hash_map[t%len] == -1)
				t = rand()%food;

			if(hash_map[t%len] == t)
			{
				hash_map[t%len] = -1;
				delta-=3;
			}
			else if(hash_map[t%len] == -2)
			{
				hash_map[t%len] = t;
				delta++;
				eaten++;
			}
			else
			{
				int j=0;
				while(!hash_map[(t+j)%len])
				{
					if(hash_map[(t+j)%len] == t)
					{
						hash_map[(t+j)%len] = -1;
						delta-=3;
						break;
					}
					j++;
				}
				if(!hash_map[(t+j)%len])
				{
					hash_map[(t+j)%len] = t;
					delta++;
					eaten++;
				}
			}
		}

		if(gen > 15)
		{
			if(avg != 0)
				avg = ((avg*gen)+curr_pop+delta)/(gen+1);
			else
				avg = curr_pop;
		}

		if(curr_pop < 10000)
			sleep(1);

		printf("Generation: %ld\n", gen);
		printf("Old Population: %ld\n", curr_pop);
		printf("New Population: %ld\n", curr_pop+delta);
		printf("Average Population: %ld\n", avg);
		gen++;
		curr_pop += delta;
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
