#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
#include <sys/wait.h>
#include "../libft/libft.h"

//don't forget to do libft
//don't forget to do ft_printf

void cmd_exec(char *agv, char **envp);
char *get_cmd_path(char *cmd, char **env);
char *ft_getenv(char **env);
void pipex(int infile, int outfile, char **ag, char **env);
#endif