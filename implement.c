#include "implement.h"

void implement(char command[])
{
    char new_command[1000];
    strcpy(new_command, command);
    char *all_args[100];
    memset(all_args, 0, sizeof(all_args));
    int bg = 0;
    int no_of_args = tokenize2(command, all_args);
    if (!strcmp(all_args[0], "repeat"))
    {
        int x = atoi(all_args[1]);
        for (int i = 0; i < x; i++)
        {
            part(all_args + 2, no_of_args - 2,new_command);
        }
    }
    else
        part(all_args, no_of_args,new_command);
}
