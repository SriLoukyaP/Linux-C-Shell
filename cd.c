#include "cd.h"
void cd_command(char *all_args[100], int no_of_args)
{
    char curr_dir[1000];

    // if (all_args[2]!=NULL||*all_args[2]!='')
    // {
    //     fprintf(stderr, "myshell:cd:too many arguments\n");
    //     return;
    // }
    if (all_args[2] != NULL)
    {
        if (strcmp(all_args[2], ""))
        {
            fprintf(stderr, "myshell:cd:too many arguments\n");
            return;
        }
    }
    if (all_args[1] == NULL)
    {
        getcwd(curr_dir, sizeof(curr_dir));
        if (chdir(home_dir) == -1)
        {
            perror("Error changing directory");
        }
        else
        {
            strcpy(prev_dir, curr_dir);
        }
    }
    else if (all_args[1][0] == '~')
    {
        strcpy(curr_dir, home_dir);
        strcat(curr_dir, all_args[1] + 1);
        if (chdir(curr_dir) == -1)
        {
            perror("Error changing directory");
        }
        else
        {
            getcwd(curr_dir, sizeof(curr_dir));
            strcpy(prev_dir, curr_dir);
        }
    }

    else if (strstr(all_args[1], "-"))
    {
        if (!strcmp(prev_dir, ""))
        {
            fprintf(stderr, "myshell: cd: OLDPWD not set\n");
        }
        else
        {
            getcwd(curr_dir, sizeof(curr_dir));
            printf("%s\n", prev_dir);
            if (chdir(prev_dir) == -1)
            {
                perror("Error changing directory");
            }
            else
            {
                strcpy(prev_dir, curr_dir);
            }
        }
    }
    else
    {
        getcwd(curr_dir, sizeof(curr_dir));
        if (chdir(all_args[1]) == -1)
        {
            perror("Error changing directory");
        }
        else
        {
            strcpy(prev_dir, curr_dir);
        }
    }
}
