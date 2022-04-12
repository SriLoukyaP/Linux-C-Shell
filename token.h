#include "main_header.h"
#ifndef TOKEN_H
#define TOKEN_H

int tokenize1(char *lineptr);
int tokenize2(char command[],char *all_args[100]);
int tokenize3(char str[], char *pipeCommands[32]);
#endif