/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:58:20 by moaljazz          #+#    #+#             */
/*   Updated: 2025/01/05 19:58:22 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

int	check_fork(pid_t id)
{
	if (id < 0)
	{
		perror("creating fork");
		return (-1);
	}
	return (0);
}

void	close_pipes(int *pd, pid_t id, pid_t id2)
{
	close(pd[0]);
	close(pd[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path_copy;
	char	*dir;
	char	*full_path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path_copy = ft_strdup(env[i] + 5);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	cmd_exec(char *agv, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(agv, ' ');
	if (!cmd)
	{
		perror("CMD at start: Command not found");
		return ;
	}
	cmd_path = get_cmd_path(cmd[0], envp);
	if (!cmd_path)
	{
		perror("CMD: Command not found");
		free(cmd_path);
		free_split(cmd);
		return ;
	}
	if (execve(cmd_path, cmd, envp) == -1)
		perror("Error EXECVE");
	free(cmd_path);
	free_split(cmd);
	return ;
}
