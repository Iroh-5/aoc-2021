#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_SIZE 32
#define MAX_INPUT_SIZE 512

typedef struct
{
    int x1, y1;
    int x2, y2;
} line;

void swap(int* a, int* b);

int main(int argc, char** argv)
{
    const char* fname = "tmp";
    FILE* input = argc > 1 ? fopen(argv[1], "r") : fopen(fname, "r");
    if (!input)
    {
	fprintf(stderr, "Couldn't open a file");
	exit(EXIT_FAILURE);
    }

    int mxx = 0;
    int mxy = 0;
    int bsize = 0;
    char ln[MAX_LINE_SIZE];
    line buffer[MAX_INPUT_SIZE]; 
    while (fgets(ln, MAX_LINE_SIZE, input))
    {
	for (int i = 0; i < MAX_LINE_SIZE && ln[i] != '\0'; ++i)
	    if (!isdigit(ln[i]))
		ln[i] = ' ';

	sscanf(ln, "%d %d %d %d", &buffer[bsize].x1, &buffer[bsize].y1, &buffer[bsize].x2, &buffer[bsize].y2);

	if (buffer[bsize].x1 > mxx)
	    mxx = buffer[bsize].x1;
	if (buffer[bsize].x2 > mxx)
	    mxx = buffer[bsize].x2;
	if (buffer[bsize].y1 > mxy)
	    mxy = buffer[bsize].y1;
	if (buffer[bsize].y2 > mxy)
	    mxy = buffer[bsize].y2;

	bsize++;
    }

    int map[mxy + 1][mxx + 1];
    for (int y = 0; y <= mxy; ++y)
	for (int x = 0; x <= mxx; ++x)
	    map[y][x] = 0;

    for (int i = 0; i < bsize; ++i)
    {
	while (buffer[i].x1 != buffer[i].x2 || buffer[i].y1 != buffer[i].y2)
	{
	    map[buffer[i].y1][buffer[i].x1]++;

	    buffer[i].x1 += (buffer[i].x1 < buffer[i].x2) ? 1 : (buffer[i].x1 > buffer[i].x2) ? -1 : 0;
	    buffer[i].y1 += (buffer[i].y1 < buffer[i].y2) ? 1 : (buffer[i].y1 > buffer[i].y2) ? -1 : 0;
	}
	map[buffer[i].y1][buffer[i].x1]++;
    }

    int cnt = 0;
    for (int y = 0; y <= mxy; ++y)
	for (int x = 0; x <= mxx; ++x)
	    if (map[y][x] >= 2)
		cnt++;

    printf("%d\n", cnt);

    return EXIT_SUCCESS;
}
