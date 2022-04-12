#include "main_header.h"

void del_pro(int i)
{
    for (int j = i; j < p_no - 1; j++)
    {
        strcpy(processes[i].pro_name, processes[i + 1].pro_name);
        processes[i].PID = processes[i + 1].PID;
    }

    p_no--;
}

void handler(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0)
    {
        char str[1000];
        bool flag = false;

        for (int i = 0; i < p_no; i++)
        {
            if (processes[i].PID == pid)
            {
                strcpy(str, processes[i].pro_name);
                //del_pro(i);
                flag = true;
                break;
            }
        }
        if (flag)
        {
            if (WEXITSTATUS(status) == 0 && WIFEXITED(status))
                fprintf(stderr, "\n%s with PID %d exited normally\n", str, pid);

            else
                fprintf(stderr, "\n%s with PID %d failed to exit normally\n", str, pid);

            display();
            fflush(stdout);
        }

        return;
    }
}
void signal_control_c(int sig)
{

    printf("\n");
    display();
    fflush(stdout);
}

void signal_control_z(int sig)
{

    printf("\n");
    display();
    fflush(stdout);
    
}

