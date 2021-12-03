#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { OXYGEN, CO2 };

char* get_rating(int type, char data[][16], int size) {
    unsigned indbuffer[size];
    for (int i = 0; i < size; ++i)
	indbuffer[i] = i;
    
    int bitn = 0;
    while (size > 1)
    {
	int onecnt  = 0;
	int zerocnt = 0;
	for (int i = 0; i < size; ++i)
	{
	    if (data[indbuffer[i]][bitn] == '1') 
		onecnt++;
	    else
		zerocnt++;
	}

	char mode;
	if (type == OXYGEN)
	    mode = onecnt >= zerocnt ? '1' : '0';
	else
	    mode = onecnt >= zerocnt ? '0' : '1';

	int ind = 0;
	for (int i = 0; i < size; ++i)
	    if (data[indbuffer[i]][bitn] == mode) 
		indbuffer[ind++] = indbuffer[i];

	size = ind;
	bitn++;
    }

    return data[indbuffer[0]];
}

unsigned long long btodec(char* n)
{
    int size = strlen(n) - 1;
    unsigned long long res = 0;
    for (int i = 0; i < size; ++i)
	res += (n[size - 1 - i] == '1' ? 1 : 0) * (1 << i);
    return res;
}

int main(int argc, char** argv)
{
    FILE* input = fopen("input", "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    int ind = 0;
    char arr[1048][16]; 
    while (fgets(arr[ind], 16, input))
	ind++;

    printf("%llu ", btodec(get_rating(OXYGEN, arr, ind)) * btodec(get_rating(CO2, arr, ind)));

    return EXIT_SUCCESS;
}
