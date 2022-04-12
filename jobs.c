#include "jobs.h"
int comp(const void *a, const void *b)
{
    job_d *job_a = (job_d *)a;
    job_d *job_b = (job_d *)b;
    return strcmp(job_a->name, job_b->name);
}
char *read_file(char *filename, int n)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char *info = malloc(sizeof(char) * 256);
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        i++;
        if (i == n)
            strcpy(info, line);
    }

    fclose(file);
    return info;
}

void job(char *all_args[100], int no_of_args)
{
    job_d pri[100];
    int c = 0;
    int r = 1, s = 1;
    if (no_of_args == 2)
    {
        if (!(strcmp(all_args[1], "-r")))
        {
            r = 1;
            s = 0;
        }
        else if (!(strcmp(all_args[1], "-s")))
        {
            s = 1;
            r = 0;
        }
    }
    char *status = malloc(sizeof(char) * (40));
    for (int i = 0; i < p_no; i++)
    {
        sprintf(status, "/proc/%d/status", processes[i].PID);
        FILE *fp = fopen(status, "r");
        if (fp == 0)
            continue;

        else
        {
            fclose(fp);
            char *status_info = read_file(status, 3);
            char *temp = status_info;
            status_info = strtok(status_info, " :\n\t\r");
            status_info = strtok(NULL, " :\n\t\r");

            if (status_info[0] == 'T')
            {
                if (s == 1)
                {
                    strcpy(status_info, "Stopped");
                    pri[c].num = i + 1;
                    strcpy(pri[c].stat_info, status_info);
                    strcpy(pri[c].name, processes[i].pro_name);
                    pri[c].pid = processes[i].PID;
                    c++;
                
                }
            }

            else
            {
                if (r == 1)
                {
                    strcpy(status_info, "Running");
                    pri[c].num = i + 1;
                    strcpy(pri[c].stat_info, status_info);
                    strcpy(pri[c].name, processes[i].pro_name);
                    pri[c].pid = processes[i].PID;
                    c++;
                }
            }

            free(temp);
        }
    }
    qsort(pri, c, sizeof(job_d), comp);
    for (int i = 0; i < c; i++)
    {
        printf("[%d] %s %s [%d]\n", pri[i].num, pri[i].stat_info, pri[i].name, pri[i].pid);
    }
    free(status);
}