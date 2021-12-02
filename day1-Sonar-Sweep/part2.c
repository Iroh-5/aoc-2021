#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 3000

int main(void)
{
    int newval;
    int ind = 0;
    int cnt = 0;
    int input[MAX_INPUT_SIZE];
    while (scanf("%d", &newval) > 0)
	input[ind++] = newval;	

    for (int i = 0; i < ind - 3; ++i)
    {
	int lsum = input[i] + input[i + 1] + input[i + 2];
	int rsum = input[i + 1] + input[i + 2] + input[i + 3];	
	if (rsum > lsum)
	    ++cnt;
    }

    printf("%d\n", cnt);

    return EXIT_SUCCESS;
}
