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

    int  ncnt = 0;
    char number[16];
    int  bits[12] = {0};
    while(fgets(number, 16, input))
    {
	ncnt++;
	for (int i = 11; i >= 0; --i)	
	    bits[11 - i] += number[i] == '1';
    }

    unsigned gamma = 0;
    for (int i = 0; i <= 11; ++i)
	gamma |= ((bits[i] > ncnt / 2) << i);

    unsigned epsilon = ~gamma;
    epsilon &= (~0U >> 20);

    printf("%d\n", gamma * epsilon);

    return EXIT_SUCCESS;
}
