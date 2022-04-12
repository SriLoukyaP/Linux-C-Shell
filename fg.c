#include "fg.h"

void fg(char *all_args[100], int no_of_args)
{
    char CURR[100];
    if (no_of_args != 2)
    {
        printf("Incorrect number of arguments.\nFormat is `fg <jobNumber>`.\n");
        return;
    }
    int pid, job_no = atoi(all_args[1]), status;
    if (job_no > p_no)
    {
        printf("Enter valid job number.");
        return;
    }
    pid = processes[job_no - 1].PID;
    strcpy(CURR, processes[job_no - 1].pro_name);
    //del_pro(job_no - 1);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pid);
    kill(pid, SIGCONT);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if (WIFSTOPPED(status))
    {
        printf("%s with PID %d suspended\n", CURR, pid);
        // strcpy(processes[p_no].pro_name, CURR);
        // processes[p_no].PID = pid;
        // p_no++;
    }

    return;
}