#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE* input = fopen("input", "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    int xdir = 0;
    int zdir = 0;
    int cnt = 0;
    char command[64];
    while (fgets(command, 64, input))
    {
	cnt++;
	if (command[0] == 'f')
	    xdir += atoi(command + 8);
	if (command[0] == 'd' || command[0] == 'u')
	    zdir += command[0] == 'd' ? atoi(command + 5) : -atoi(command + 3);
    }

    printf("%d\n", xdir * zdir);

    return EXIT_SUCCESS;
}
