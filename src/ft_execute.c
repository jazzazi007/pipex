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

int	check_fork(pid_t id)
{
	if (id < 0)
	{
		perror("creating fork");
		return (-1);
	}
	return (0);
}

int	close_pipes(int *pd, pid_t id, pid_t id2)
{
	int	status;

	close(pd[0]);
	close(pd[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
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
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		full_path = get_cmd_assist(cmd, dir);
		if (access(full_path, X_OK) == 0)
			return (free(path_copy), full_path);
		free(full_path);
		dir = ft_strtok(NULL, ":");
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

int	cmd_exec(char *agv, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd_path = NULL;
	cmd = ft_split(agv, ' ');
	if (!cmd || !cmd[0])
		return (free_split(cmd), 0);
	if (access(cmd[0], X_OK) == 0)
		cmd_path = ft_strdup(cmd[0]);
	else
	{
		cmd_path = get_cmd_path(cmd[0], envp);
		if (!cmd_path)
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": command not found\n", 20);
			return (free(cmd_path), free_split(cmd), 127);
		}
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		free(cmd_path);
		return (free_split(cmd), errno = ENOKEY, perror("Error"), 126);
	}
	return (free(cmd_path), free_split(cmd), 0);
}
