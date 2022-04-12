#include "bg.h"

void bg(char *all_args[100], int no_of_args)
{
    if (no_of_args != 2)
        printf("Incorrect number of arguments.\nFormat is `bg <jobNumber>`.");

    else
    {
        int job_no = atoi(all_args[1]);
        if (job_no > p_no)
            printf("Enter valid job number\n");

        else
        {
            if (kill(processes[job_no - 1].PID, SIGCONT) < 0)
            {
                perror("");
            }
        }
    }
}