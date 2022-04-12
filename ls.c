#include "ls.h"
int count1 = 0;

int isDirectory(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return -1;
    return S_ISDIR(statbuf.st_mode);
}
int isFile(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return -1;
    return S_ISREG(statbuf.st_mode);
}

void ols(char pres_dir[])
{
    char tempdir[100000];

    if (pres_dir[0] == '~')
    {
        strcpy(tempdir, home_dir);
        strcat(tempdir, &pres_dir[1]);
        strcpy(pres_dir, tempdir);
    }
    DIR *d;
    struct dirent **read;
    int count = scandir(pres_dir, &read, NULL, alphasort);
    if (count < 0)
        perror("Error: no such file or directory exists\n");
    else
    {
        for (int x = 0; x < count; x++)
        {
            if (read[x]->d_name[0] == '.')
            {
                continue;
            }
            else
            {
                printf("%s\n", read[x]->d_name);
            }
        }
    }
}

void print_l(char path[], char *filename)
{
    char date[30], time[6];
    struct stat statbuf = {0};
    stat(path, &statbuf);

    struct stat s = {0};
    stat(path, &s);

    if (S_ISDIR(statbuf.st_mode))
        printf("d");
    else
        printf("-");

    if (statbuf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if (statbuf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if (statbuf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    if (statbuf.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if (statbuf.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (statbuf.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (statbuf.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if (statbuf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if (statbuf.st_mode & S_IXOTH)
        printf("x\t");
    else
        printf("-\t");

    printf("%3ld\t", statbuf.st_nlink);

    time_t t = statbuf.st_mtime;
    struct tm lt;
    localtime_r(&t, &lt);
    char buftime1[90];
    char buftime2[90];
    char var1[10];
    char var2[10];
    struct passwd *pw = getpwuid(statbuf.st_uid);
    struct group *gr = getgrgid(statbuf.st_gid);
    strftime(buftime1, sizeof buftime1, "%b %d %H:%M", &lt);
    strftime(buftime2, sizeof buftime2, "%b %d %Y", &lt);
    strftime(var1, sizeof var1, "%Y", &lt);
    strftime(var2, sizeof var2, "%b", &lt);
    if (!strcmp(var1, "2021"))
    {
        if (!strcmp(var2, "Jan") || !strcmp(var2, "Feb"))
        {
            printf("%10s%10s%11ld %6s%18s\n", pw->pw_name, gr->gr_name, statbuf.st_size, buftime2, filename);
        }
        else
        {
            printf("%10s%10s%11ld %6s%18s\n", pw->pw_name, gr->gr_name, statbuf.st_size, buftime1, filename);
        }
    }
    else
    {
        printf("%s\t%s\t%ld\t%s\t%s\n", pw->pw_name, gr->gr_name, statbuf.st_size, buftime2, filename);
    }
}
void readir(char path[], int flag_l, int flag_a)
{
    int x = isFile(path);
    if (x == -1)
    {
        perror("Error");
        return;
    }
    if (x == 1)
    {
        if (flag_l == 0)
        {
            printf("%s\n", path);
        }
        else
        {
            print_l(path, path);
        }
        return;
    }
    int y = isDirectory(path);
    if (y == -1)
    {
        perror("Error");
        return;
    }
    if (y == 1)
    {

        DIR *d;
        struct dirent **read;
        int count = scandir(path, &read, NULL, alphasort);
        if (flag_l == 1)
        {

            long int total = 0;

            if (count < 0)
                perror("Error");

            else
            {
                if (count1 > 1)
                    printf("%s:\n", path);
                for (int x = 0; x < count; x++)
                {
                    char filepath[2048];
                    strcpy(filepath, path);
                    strcat(filepath, "/");
                    strcat(filepath, read[x]->d_name);

                    struct stat b = {0};
                    if (stat(filepath, &b) == 0)
                        if (flag_a != 1)
                        {
                            if (read[x]->d_name[0] != '.')
                            {
                                total += b.st_blocks;
                            }
                        }
                        else
                            total += b.st_blocks;
                }
                printf("total %ld\n", total / 2);
            }
        }
        for (int x = 0; x < count; x++)
        {
            char filepath[2048];
            strcpy(filepath, path);
            strcat(filepath, "/");
            strcat(filepath, read[x]->d_name);

            if (flag_l && flag_a)
                print_l(filepath, read[x]->d_name);
            else if (flag_l && !flag_a)
            {
                if (read[x]->d_name[0] != '.')
                    print_l(filepath, read[x]->d_name);
            }
            else if (!flag_l && flag_a)
                printf("%s\n", read[x]->d_name);
            else if (!flag_l && !flag_a)
            {
                if (read[x]->d_name[0] != '.')
                    printf("%s\n", read[x]->d_name);
            }
        }
        //printf("\n");
    }
}

void ls_command(char *all_args[100], char pres_dir[], int k)
{
    if (k == 1)
    {
        ols(pres_dir);
    }

    else if (k == 2 && !strcmp(all_args[1], "."))
    {
        ols(pres_dir);
    }
    else if (k == 2 && !strcmp(all_args[1], ".."))
    {
        ols("..");
    }
    else
    {
        int flag_l = 0, flag_a = 0, flag_dir;
        for (int i = 1; i < k; i++)
        {
            if (!strcmp(all_args[i], "-l"))
            {
                flag_l++;
                count1++;
            }
            else if (!strcmp(all_args[i], "-a"))
            {
                flag_a++;
                count1++;
            }
            else if (!strcmp(all_args[i], "-al") || !strcmp(all_args[i], "-la"))
            {
                flag_l++;
                flag_a++;
                count1++;
            }
            else if (strcmp(all_args[i], ""))
            {
                flag_dir = 1;
            }
        }
        count1 = k - count1 - 1;
        if (flag_dir == 1)
        {
            for (int i = 1; i < k; i++)
            {
                if (!strcmp(all_args[i], "-l"))

                {
                    continue;
                }
                else if (!strcmp(all_args[i], "-a"))
                {
                    continue;
                }
                else if (!strcmp(all_args[i], "-al"))
                {
                    continue;
                }
                else if (!strcmp(all_args[i], "-la"))
                {
                    continue;
                }
                else if (!strcmp(all_args[i],""))
                {
                    continue;
                }
                else
                {
                    char path[1024];
                    if (strstr(all_args[i], "~"))
                    {
                        strcpy(path, home_dir);
                        strcat(path, all_args[i] + 1);
                    }
                    else
                        strcpy(path, all_args[i]);

                    readir(path, flag_l, flag_a);
                }
            }
        }
        else
        {
            readir(".", flag_l, flag_a);
        }
    }
}
