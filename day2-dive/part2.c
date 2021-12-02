#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* input = fopen(argv[1], "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    char line[64];
    long long aim = 0;
    long long xdir = 0;
    long long depth = 0;
    while (fgets(line, 64, input))
    {
	if (line[0] == 'f')
	{
	    int delta = atoi(line + 8);
	    xdir += delta;
	    depth += aim * delta;
	}
	if (line[0] == 'd' || line[0] == 'u')
	{
	    aim += line[0] == 'd' ? atoi(line + 5) : -atoi(line + 3);
	}
    }

    printf("%lld\n", xdir * depth);

    return EXIT_SUCCESS;
}
