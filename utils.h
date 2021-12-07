#ifndef UTILS
#define UTILS

int gnumsfstr(char* in, int* out, const char* delim)
{
    int ind = 0;
    in = strtok(in, delim);
    while (in)
    {
	out[ind++] = atoi(in);
	in = strtok(NULL, delim);
    }

    return ind;
}

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
	printf("%d ", arr[i]);
    putchar('\n');
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

long long lmin(long long a, long long b)
{
    return (a < b) ? a : b;
}

#endif
