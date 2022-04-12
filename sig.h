#include "main_header.h"

#ifndef _SIG_H
#define _SIG_H

void signal_handler(int signal);
void del_pro(int i);
void signal_control_c(int sig);
void signal_control_z(int sig);
void signal_control_d(int sig);
#endif