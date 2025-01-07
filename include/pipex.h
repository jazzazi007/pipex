/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:58:41 by moaljazz          #+#    #+#             */
/*   Updated: 2025/01/05 19:58:43 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
#include <errno.h>

// don't forget to do libft
// don't forget to do ft_printf

void	cmd_exec(char *agv, char **envp);
char	*get_cmd_path(char *cmd, char **env);
char	*ft_getenv(char **env);
void	pipex(int infile, int outfile, char **ag, char **env);
void    free_split(char **cmd);
void close_pipes(int *pd, pid_t id, pid_t id2);
int check_fork(pid_t id);
#endif
