#include "input.h"

char *input()
{
    size_t n = 0;
    int read_from_buffer;
    char *lineptr = NULL;
    read_from_buffer = getline(&lineptr, &n, stdin);
    if (read_from_buffer < 0)
    {
        printf("exit\n");
        exit(0);
    }
    lineptr[read_from_buffer - 1] = '\0';
    return lineptr;
}