#ifndef MICROSHELL_H
#define MICROSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include <errno.h>

int ft_strlen(char *a);
int ft_strlen2(char **a);
char *ft_strdup(char *a);
void ft_fatal_error();

void launch_cmd(char ***cmds, int i, char **env);

#endif
