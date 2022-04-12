#include "pwd.h"

void pwd_command()
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("Error getting current working directory");
    }
}