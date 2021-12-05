#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

size_t rnumsfstr(char* buffer, int* out, size_t osize)
{
    int offset;
    size_t ind = 0;
    while (ind < osize && sscanf(buffer, "%d %n", &out[ind], &offset) > 0)
    {
	ind++;
	buffer += offset;
    }

    return ind;
}

void add(int* arr, int val)
{
    for (int i = 0; i < 5; ++i)
    {
	if (arr[i] == -1)
	{
	    arr[i] = val;
	    return;
	}
    }
}

void rmifex(int* arr, int val)
{
    for (int i = 0; i < 5; ++i)
	if (arr[i] == val)
	    arr[i] = -1;
}

bool issolved(int* arr)
{
    bool res = true;
    for (int i = 0; i < 5; ++i)
	if (arr[i] != -1)
	    res = false;
    return res;
}

int getgrsum(int* rows, int gridn)
{
    int sum = 0;
    for (int i = 5 * gridn; i < 5 * (gridn + 1); ++i)
	for (int r = 0; r < 5; ++r)
	    sum += rows[r];
    return sum;
}

int main(int argc, char** argv)
{
    FILE* input = fopen("input", "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    // Reding numbers
    char buffer[1024];
    fgets(buffer, 1024, input);

    for (int i = 0; buffer[i] != '\0'; ++i)
	if (buffer[i] ==',')
	    buffer[i] = ' ';

    int numbers[256];
    size_t nsize = rnumsfstr(buffer, numbers, 256);

    int col = 0;
    int row = 0;
    int gridn = 0;
    int rcsize = 0;
    int rows[625][5] = {{-1}};
    int cols[625][5] = {{-1}};

    for (int i = 0; i < 625; ++i)
	for (int j = 0; j < 5; ++j)
	    rows[i][j] = cols[i][j] = -1;

    // Fill boards
    while (!feof(input))
    {
	rcsize += 5;
	for (int r = 0; r < 5; r++)
	{
	    for (int c = 0; c < 5; c++)
	    {
		int tmp;
		fscanf(input, "%d ", &tmp);
		add(rows[row + r], tmp);
		add(cols[col + c], tmp);
	    }
	}

	row += 5;
	col += 5;
	gridn++;
    }

    bool boards[gridn];
    for (int i = 0; i < gridn; ++i)
	boards[i] = false;

    // Mark each number and check for a win
    int winners = 0;
    int lastboard, winnum;
    for (int i = 0; i < nsize; ++i)
    {
	for (int j = 0; j < rcsize; ++j)
	{
	    rmifex(cols[j], numbers[i]);
	    rmifex(rows[j], numbers[i]);

	    if (issolved(cols[j]) || issolved(rows[j]))
	    {
		if (boards[j / 5])
		    continue;

		boards[j / 5] = true;
		lastboard = j / 5;
		winnum = numbers[i];

		if (++winners == gridn)
		    goto end;
	    }
	}
    }

end:;
    int sum = 0;
    for (int l = 5 * lastboard; l < 5 * (lastboard + 1); ++l)
	for (int m = 0; m < 5; ++m)
	    if (rows[l][m] != -1)
		sum += rows[l][m];

    printf("%d\n", sum * winnum);

    return EXIT_SUCCESS;
}
