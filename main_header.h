#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include <grp.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include "input.h"
#include "display.h"
#include "cd.h"
#include "echo.h"
#include "implement.h"
#include "ls.h"
#include "pwd.h"
#include "token.h"
#include "pinfo.h"
#include "sig.h"
#include "fbbg.h"
#include "part.h"
#include "jobs.h"
#include "fg.h"
#include "bg.h"
#include "sig_comm.h"
#include "redirect.h"
#include "pipe.h"
void handler(int sig);
void run(int bg, int no_of_args);
char host_name[1000];
char *user_name;
char cwd[1000];
char home_dir[1000];
char *all_commands[100];
char prev_dir[1000];
struct Node
{
    char pro_name[100];
    pid_t PID;  
};

typedef struct Node node;
node processes[100];
int p_no;
//pid_t SHELL_ID, CHILD_ID = -1;
pid_t spid;
pid_t spgid;
int InFile, OutFile;
//ListNode *head;

struct job_d
{
    int num;
    char stat_info[20];
    char name[100];
    int pid;

};
typedef struct job_d job_d;
#endif