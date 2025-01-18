
#include "../include/pipex.h"

char	*get_cmd_assist(char *cmd, char *dir)
{
	char *full_path;

	full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

void fork1 (int infile, char **ag, char **env, int *pd)
{
		if (file_errhandle(infile) == 0)
			first_fork_operate(infile, ag, env, pd);
		else
			exit(1);
    return ;
}
void fork2 (int outfile, char **ag, char **env, int *pd)
{
    if (file_errhandle(outfile) == 0)
				second_fork_operate(outfile, ag, env, pd);
			else
				exit(1);
    return ;
}
