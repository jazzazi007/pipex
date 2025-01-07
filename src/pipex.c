/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:57:50 by moaljazz          #+#    #+#             */
/*   Updated: 2025/01/05 19:57:54 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_fork_operate(int infile, char **ag, char **env, int *pd)
{

	close(pd[0]);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pd[1], STDOUT_FILENO);
	close(pd[1]);
	cmd_exec(ag[2], env);
	exit(0);
}

void	second_fork_operate(int outfile, char **ag, char **env, int *pd)
{

	close(pd[1]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pd[0], STDIN_FILENO);
	close(pd[0]);
	cmd_exec(ag[3], env);
	exit(0);
}
int	file_errhandle(int file)
{
	if (file < 0)
	{
		perror("Error opening input file");
		fprintf(stderr, "Error: %s %d\n", strerror(errno), errno);
		return (errno);
	}
	return (0);
}

void	pipex(int infile, int outfile, char **ag, char **env)
{
	pid_t	id;
	pid_t	id2;
	int		pd[2];

	if (pipe(pd) == -1)
	{
		perror("Error creating pipe");
		return ;
	}
	id = fork();
	if (check_fork(id) < 0)
		return ;
	if (id == 0)
	{
		if (file_errhandle(infile) != 13)
			first_fork_operate(infile, ag, env, pd);
		else
			exit(0);
	}
	else
	{
		id2 = fork();
		if (check_fork(id2) < 0)
			return ;
		if (id2 == 0)
		{
			if (file_errhandle(outfile) != 13)
				second_fork_operate(outfile, ag, env, pd);
			else
				exit(0);
		}
		close_pipes(pd, id, id2);
	}
}



int	error_handle(int fd_1, int fd_2)
{
	if (fd_1 < 0)
	{
		perror("Error opening input file");
		fprintf(stderr, "Error: %s %d\n", strerror(errno), errno);
		return (-1);
	}
	if (fd_2 < 0)
	{
		perror("Error opening output file");
		fprintf(stderr, "Error: %s %d\n", strerror(errno), errno);
		close(fd_1);
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	if (ac == 5)
	{
		fd1 = access(av[1], F_OK & R_OK & W_OK & X_OK);
		if (fd1 < 0)
		{
			perror("Error accessing input file");
			//return (-1);
		}
		fd1 = open(av[1], O_RDONLY);

		fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		//if (error_handle(fd1, fd2) < 0)
		//	perror("error of the file");//return (-1);
		pipex(fd1, fd2, av, envp);
	}
	else
	{
		write(1, "Error: invalid number of args\n", 31);
		return (-1);
	}
	return (0);
}
