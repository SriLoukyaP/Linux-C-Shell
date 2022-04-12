#include "display.h"
void display()
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        char *x = strstr(cwd, home_dir);
        if (x)
        {
            printf("<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m~%s\x1B[0m>", user_name, host_name, strstr(cwd, home_dir) + strlen(home_dir));
        }
        else
            printf("<\x1B[1;32m%s@%s\x1B[0m:\x1B[1;34m%s\x1B[0m>", user_name, host_name, cwd);
    }
    else
    {
        perror("Error getting current directory");
    }
}