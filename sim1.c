//Includes 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MILL 1000000

//Prototypes
int getSatisfiedFraction();

//Main Program
int main()
{
	long food = MILL;
	long population = 2;
	long generation = 0;

	int breed_ratio = 0;
	int satisfied_ratio = 0;
	int hungry_ratio = 0;

	char temp;

	while(1)
	{
		satisfied_ratio = getSatisfiedFraction();

		population += (1-satisfied_ratio)*population;

		generation++;
	}

	return 0;
}

//Definitions
int getSatisfiedFraction()
{
	int result = 0;

	return result;
}
