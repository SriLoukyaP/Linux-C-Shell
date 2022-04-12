#include "echo.h"

void echo_command(char*all_args[100],int no_of_args)
{
    for(int i=1;i<no_of_args;i++)
    {
        printf("%s ",all_args[i]);
    }
    printf("\n");
}
