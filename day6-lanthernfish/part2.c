#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMS 9
#define EPOCH 256 
#define MAX_INPUT_SIZE 1024

void gnumsfstr(char* in, long long* out);

int main(int argc, char** argv)
{
    const char* fname = "input";
    FILE* input = argc > 1 ? fopen(argv[1], "r") : fopen(fname, "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    char line[MAX_INPUT_SIZE];
    fgets(line, MAX_INPUT_SIZE, input);
    
    long long buffer[NUMS] = {0};
    gnumsfstr(line, buffer);

    for (int i = 1; i <= EPOCH; ++i)
    {
	long long zeros = buffer[0];

	for (int k = 0; k < NUMS - 1; ++k)
	    buffer[k] = buffer[k + 1];

	buffer[6] += zeros;
	buffer[8] = zeros;
    }

    long long sum = 0;
    for (int i = 0; i < NUMS; ++i)
	sum += buffer[i];
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}

void gnumsfstr(char* in, long long* out)
{
    int ind = 0;
    in = strtok(in, ",");
    while (in)
    {
	out[atoi(in)]++;
	in = strtok(NULL, ",");
    }
}
