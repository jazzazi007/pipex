#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

//don't forget to do libft
//don't forget to do ft_printf

void cmd_exec(char *path, char **cmd, char **envp);
char *ft_getenv(char **env);
void pipex(int infile, int outfile, char **ag, char **env);
#endif