#include "main_header.h"

void part(char *all_args[100], int no_of_args, char new_command[])
{
    int bg1 = 0;
    for (int i = 0; i < no_of_args; i++)
    {
        if (!strcmp(all_args[i], "&"))
        {
            bg1 = 1;
            all_args[i] = "";
            break;
        }
    }
    if (strstr(new_command, "<") || strstr(new_command, ">"))
    {
        int x = redirect(new_command, all_args, no_of_args);
        if (x == 1)
            return;
        for (int i = 0; i < no_of_args; i++)
        {
            if (!strcmp(all_args[i], ">") || !strcmp(all_args[i], ">>") || !strcmp(all_args[i], "<"))
            {
                fprintf(stderr, "Invalid Syntax\n");
                return;
            }
        }
    }
    // if(strstr(new_command,"|"))
    // {
       
    //    piping(new_command);
    // }
    if (!strcmp(all_args[0], "quit"))
    {

        exit(0);
    }
    // else if (!strcmp(all_args[no_of_args - 1], "&"))
    // {
    //     all_args[no_of_args - 1] = NULL;

    //     fbbg(all_args, 1, no_of_args);
    // }

    // else if (all_args[no_of_args - 1][strlen(all_args[no_of_args - 1]) - 1] == '&')
    // {
    //     all_args[no_of_args - 1][strlen(all_args[no_of_args - 1]) - 1] = '\0';

    //     fbbg(all_args, 1, no_of_args);
    // }
    else if (bg1)
    {
        fbbg(all_args, 1, no_of_args);
    }
    else if (!strcmp(all_args[0], "cd"))
    {
        cd_command(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "pwd"))
    {
        pwd_command();
    }
    else if (!strcmp(all_args[0], "echo"))
    {
        echo_command(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "ls"))
    {
        ls_command(all_args, cwd, no_of_args);
    }
    else if (!strcmp(all_args[0], "pinfo"))
    {
        pinfo_command(all_args);
    }
    else if (!strcmp(all_args[0], "jobs"))
    {
        job(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "fg"))
    {
        fg(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "bg"))
    {
        bg(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "sig"))
    {
        sig_comm(all_args, no_of_args);
    }
    else
    {
        fbbg(all_args, 0, no_of_args);
    }
    dup2(InFile, STDIN_FILENO);
    dup2(OutFile, STDOUT_FILENO);
}