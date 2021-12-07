#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPOCH 256 
#define MAX_NUMS 512
#define GROWTH_FACTOR 2
#define MAX_INPUT_SIZE 1024

int gnumsfstr(char* in, int* out);

int main(int argc, char** argv)
{
    const char* fname = "tmp";
    FILE* input = argc > 1 ? fopen(argv[1], "r") : fopen(fname, "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    char line[MAX_INPUT_SIZE];
    fgets(line, MAX_INPUT_SIZE, input);
    
    int buffer[MAX_NUMS];
    int bsize = gnumsfstr(line, buffer);

    int* population = malloc(GROWTH_FACTOR * bsize * sizeof(int));
    memcpy(population, buffer, bsize * sizeof(int));

    long long ind = bsize;
    for (int i = 1; i <= EPOCH; ++i)
    {
	int tsize = ind;
	for (int j = 0; j < tsize; ++j)
	{
	    if (population[j] == 0)
	    {
		if (bsize == ind)
		{
		    bsize *= GROWTH_FACTOR;
		    population = realloc(population, bsize * sizeof(int));
		}

		population[ind++] = 8;
	    }
	    
	    if (--population[j] < 0)
		population[j] = 6;
	}
    }

    printf("%lld\n", ind);

    return EXIT_SUCCESS;
}

int gnumsfstr(char* in, int* out)
{
    int ind = 0;
    in = strtok(in, ",");
    while (in)
    {
	out[ind++] = atoi(in);
	in = strtok(NULL, ",");
    }

    return ind;
}
