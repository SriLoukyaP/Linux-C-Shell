#include "pinfo.h"
void pinfo_command(char*all_args[100])
{

    char path[1024], pid[100];
    // pid_t pid;
    unsigned long mem;
    int str_size;
    char exe[1024], status[100];
    if (all_args[1]&&(strcmp(all_args[1],"")))
    {
        strcpy(pid, all_args[1]);
    }
    else
    {
        int x = getpid();
        sprintf(pid, "%d", x);
    }
    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/stat");
    FILE *file_point = fopen(path, "r");
    int flag = 0;
    if (file_point == NULL)
    {
        printf("Error opening %s file\n", path);
        return;
    }
    else
    {
        long long pgrp, tpgid;
        char str[1024];
        int i = 1;
        while (fscanf(file_point, "%s", str) == 1)
        {
            if (i == 3)
            {
                strcpy(status, str);
            }
            if (i == 5)
                pgrp = atoi(str);
            if (i == 8)
            {
                tpgid = atoi(str);
            }
            if (i == 23)
            {
                mem = atoi(str);
                break;
            }
            i++;
        }
        flag = (pgrp == tpgid);
        fclose(file_point);
    }

    printf("pid -- %s\n", pid);
    printf("Process Status -- {%s", status);
    if (flag)
        printf("+");
    printf("}\n");
    printf("Memory -- %ld bytes {​Virtual Memory​}\n", mem);

    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/exe");
    str_size = readlink(path, exe, sizeof(exe));
    exe[str_size] = '\0';

    printf("Executable Path -- %s\n", exe);
}

void pinfo_command_r(char **all_args_r)
{

    char path[1024], pid[100];
    // pid_t pid;
    unsigned long mem;
    int str_size;
    char exe[1024], status[100];
    if (all_args_r[1])
    {
        strcpy(pid, all_args_r[1]);
    }
    else
    {
        int x = getpid();
        sprintf(pid, "%d", x);
    }
    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/stat");
    FILE *file_point = fopen(path, "r");
    int flag = 0;
    if (file_point == NULL)
    {
        printf("Error opening %s file\n", path);
        exit(1);
    }
    else
    {
        long long pgrp, tpgid;
        char str[1024];
        int i = 1;
        while (fscanf(file_point, "%s", str) == 1)
        {
            if (i == 3)
            {
                strcpy(status, str);
            }
            if (i == 5)
                pgrp = atoi(str);
            if (i == 8)
            {
                tpgid = atoi(str);
            }
            if (i == 23)
            {
                mem = atoi(str);
                break;
            }
            i++;
        }
        flag = (pgrp == tpgid);
        fclose(file_point);
    }

    printf("pid -- %s\n", pid);
    printf("Process Status -- {%s", status);
    if (flag)
        printf("+");
    printf("}\n");
    printf("Memory -- %ld bytes {​Virtual Memory​}\n", mem);

    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/exe");
    str_size = readlink(path, exe, sizeof(exe));
    exe[str_size] = '\0';

    printf("Executable Path -- %s\n", exe);
}
