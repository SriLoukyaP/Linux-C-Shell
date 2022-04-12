#include "redirect.h"

int redirect(char new_command[], char *all_args[100], int no_of_args)
{
    if (strstr(new_command, "<"))
    {
        int input;
        for (int i = 0; i < no_of_args - 1; i++)
        {
            if (!strcmp(all_args[i], "<"))
            {
                input = open(all_args[i + 1], O_RDONLY);

                if (input < 0)
                {
                    perror("Error opening input file");
                    return 1;
                }
                else
                {
                    dup2(input, STDIN_FILENO);
                    close(input);
                }
                all_args[i] = "";
                all_args[i + 1] = "";
                break;
            }
        }
    }
    if (strstr(new_command, ">"))
    {
        int output;
        for (int i = 0; i < no_of_args - 1; i++)
        {
            if (!strcmp(all_args[i], ">") || !strcmp(all_args[i], ">>"))
            {
                if (!strcmp(all_args[i], ">>"))
                {
                    output = open(all_args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    output = open(all_args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }

                if (output < 0)
                {

                    perror("Error opening output file");
                }
                else
                {
                    dup2(output, STDOUT_FILENO);
                    close(output);
                }
                all_args[i] = "";
                all_args[i + 1] = "";
                break;
            }
        }
    }
    return 0;
}