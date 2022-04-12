#include "fbbg.h"
void fbbg(char *all_args[100], int bg, int no_of_args)
{
    
    int j = 0;
    for (int i = 0; i < no_of_args; i++)
    {
        if (strcmp(all_args[i], ""))
        {
            all_args[j++] = all_args[i];
        }
    }
    all_args[j] = 0;
    
    
    int status;
    pid_t pid = fork(), wpid;
    all_args[no_of_args] = NULL;

    if (pid < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(all_args[0], all_args) < 0)
        {
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (bg == 0)
        {
            char CURR[1024];
            strcpy(CURR, all_args[0]);

            for (int i = 1; i < j ; i++)
            {
                strcat(CURR, " ");
                strcat(CURR, all_args[i]);
            }

            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, pid);
            wpid = waitpid(pid, &status, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            if (WIFSTOPPED(status))
            {
                printf("%s with PID %d suspended\n", CURR, pid);
                strcpy(processes[p_no].pro_name, CURR);
                processes[p_no].PID = pid;
                p_no++;
            }
        }

        else
        {
            strcpy(processes[p_no].pro_name, all_args[0]);

            for (int i = 1; i < no_of_args - 1; i++)
            {
                strcat(processes[p_no].pro_name, " ");
                strcat(processes[p_no].pro_name, all_args[i]);
            }

            processes[p_no].PID = pid;
            p_no++;
            printf("%d\n", pid);
        }
    }

    return;
}
