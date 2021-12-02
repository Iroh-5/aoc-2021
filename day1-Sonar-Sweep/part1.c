#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int cnt = 0;
    int prev, curr;
    scanf("%d", &prev);

    while (scanf("%d", &curr) > 0)
    {
	if (curr > prev)
	    ++cnt;
	prev = curr;
    }

    printf("%d\n", cnt);

    return EXIT_SUCCESS;
}
