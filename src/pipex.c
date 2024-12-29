#include "../include/pipex.h"

void pipex(int infile, int outfile, char **ag, char **env)
{
    pid_t id;
    int pd[2];

    if (pipe(pd) == -1)
    {
        perror("Error creating pipe");
        return;
    }
    id = fork();
    if (id < 0)
    {
        perror("creating fork");
        return;
    }
    if (id == 0) // child
    {
        close (pd[0]);
        dup2(infile, STDIN_FILENO);
        close(infile);
        dup2(pd[1], STDOUT_FILENO);
        close(pd[1]);
        cmd_exec(ag[2], env);
    }
    else //parent
    {
        close(pd[1]);
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
        dup2(pd[0], STDIN_FILENO);
        close(pd[0]);
        cmd_exec(ag[3], env);
        waitpid(id, NULL, 0);
        //cmd_exec(ft_getenv(env), ag[3], env);
    }

}

int main(int ac, char **av, char **envp)
{
    int fd1;
    int fd2;
    if (ac == 5)
    {
        fd1 = open(av[1], O_RDONLY);
        fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (fd1 < 0)
        {
            perror("Error opening input file");
            return (-1);
        }
        if (fd2 < 0)
        {
            perror("Error opening output file");
            close(fd1);
            return (-1);
        }
        pipex(fd1, fd2, av, envp);
    }
    else
    {
        perror("Error: invalid number of args");
        return (-1);
    }
    return(0);
}
