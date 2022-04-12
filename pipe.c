#include "pipe.h"

void pipe_comm(char comm[])
{
    int num = 0;
    for (int i = 0; i < strlen(comm); i++)
    {
        if (comm[i] == '|')
            num++;
    }
    char *pipes[32];
    int no_pipe_commands = tokenize3(comm, pipes);
    if (no_pipe_commands != num + 1)
    {
        fprintf(stderr, "Invalid Syntax\n");
        return;
    }
    int pipefd[no_pipe_commands - 1][2];

    if (pipe(pipefd[0]) < 0)
    {
        perror("");
    }
    int outFile = dup(STDOUT_FILENO);
    dup2(pipefd[0][1], STDOUT_FILENO);
    close(pipefd[0][1]);
    implement(pipes[0]);
    dup2(outFile, STDOUT_FILENO);
    close(outFile);

    for (int i = 1; i < no_pipe_commands - 1; i++)
    {
        if (pipe(pipefd[i]) < 0)
        {
            perror("");
        }
        int inFile = dup(STDIN_FILENO);
        int outFile = dup(STDOUT_FILENO);
        dup2(pipefd[i][1], STDOUT_FILENO);
        dup2(pipefd[i - 1][0], STDIN_FILENO);
        close(pipefd[i][1]);
        close(pipefd[i - 1][0]);
        implement(pipes[i]);
        dup2(inFile, STDIN_FILENO);
        dup2(outFile, STDOUT_FILENO);
        close(inFile);
        close(outFile);
    }
    int inFile = dup(STDIN_FILENO);
    dup2(pipefd[no_pipe_commands - 2][0], STDIN_FILENO);
    close(pipefd[no_pipe_commands - 2][0]);
    implement(pipes[no_pipe_commands - 1]);
    dup2(inFile, STDIN_FILENO);
    close(inFile);
}
