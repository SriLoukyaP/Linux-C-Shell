#include "sig_comm.h"

void sig_comm(char *all_args[100], int no_of_args)
{
    if (no_of_args != 3)
    {
        printf("Incorrect number of arguments.\n");
        return;
    }
    int job_num = atoi(all_args[1]);
    int sig_num = atoi(all_args[2]);
    if (job_num > p_no)
    {
        printf("Enter valid job number.\n");
        return;
    }
    int pid = processes[job_num - 1].PID;

    if (kill(pid, sig_num) < 0)
    {
        perror("");
    }
}