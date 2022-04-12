#include "main_header.h"

int main()
{
    printf("----------------------My shell starts here-----------------------\n");
    gethostname(host_name, 100);
    user_name = getenv("USER");
    getcwd(cwd, sizeof(cwd));
    getcwd(home_dir, sizeof(home_dir));
    strcpy(prev_dir, "");
    signal(SIGCHLD, handler);
    signal(SIGINT, signal_control_c);
    signal(SIGTSTP, signal_control_z);
    InFile = dup(STDIN_FILENO);
    OutFile = dup(STDOUT_FILENO);
    spid = getpid();
    spgid = getpgid(spid);
    while (1)
    {
        display();
        fflush(stdout);
        char *lineptr = input();
        if (lineptr[0] == '\0')
            continue;

        int no_of_commands = tokenize1(lineptr);
        int j = 0;
        while (j < no_of_commands)
        {
            if (strstr(all_commands[j], "|"))
                pipe_comm(all_commands[j]);
            else
                implement(all_commands[j]);
            j++;
        }
    }
}