#include "../include/pipex.h"

void pipex(int infile, int outfile, char **ag, char **env)
{
    pid_t id;
    pid_t id2;
    int pd[2];

    if (pipe(pd) == -1)
    {
        perror("Error creating pipe");
        return;
    }
    id = fork();
    if (id < 0)
    {
        perror("creating fork 1");
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
        exit(0);
    }
    else //parent
    {
        id2 = fork();
        if (id2 < 0)
        {
            perror("creating fork 2");
            return;
        }
        if (id2 ==0)
        {
            close(pd[1]);
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
            dup2(pd[0], STDIN_FILENO);
            close(pd[0]);
            cmd_exec(ag[3], env);
            exit(0);
        }
        close(pd[0]);
        close(pd[1]);
        waitpid(id, NULL, 0);
        waitpid(id2, NULL, 0);
    }
}

int main(int ac, char **av, char **envp)
{
    int fd1;
    int fd2;
    if (ac == 5)
    {
        fd1 = access(av[1], F_OK & R_OK & W_OK & X_OK);
        if (fd1 < 0)
        {
            perror("Error accessing input file");
            return (-1);
        }
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
        write(1,"Error: invalid number of args\n", 31);
        return (-1);
    }
    return(0);
}
/*
enhance the acesss fucntion to be related to infile or outfile and excutability of the command 
complete the memory allocation handling: Done but double check
*/