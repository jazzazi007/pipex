void exec_cmd(char *cmd, char **envi, int file)
{

}
void pipex(int infile, int outfile, char **ag, char **env)
{
    int id;
    int pd[2];

    if (pipe(pd) == -1)
        return;
    id = fork();
    if (id < 0)
        return;
    if (id == 0)
    {
        close (pd[0]);
        dup2(infile, 0);
        close(infile);
        dup2(pd[1], 1);
        close(pd[1]);
        exec_cmd(cmd, env, infile);
    }
    else 
    {
        close(pd[1]);
        dup2(outfile, 1);
        close(outfile);
        dup2(pd[0], 0);
        close(pd[0]);
        exec_cmd(cmd2, env, outfile);
    }

}

int main(int ac, char **av, char **envp)
{
    int fd1;
    int fd2;
    if (ac == 5)
    {
        fd1 = open(av[1], O_RDONLY);
        fd2 = open(av[4], O_RDWR | O_CREAT| O_TRUNC | 0644);
        if(fd1 < 0 || fd2 < 0)
            return(-1);
        pipex(fd1, fd2, av, envp);
    }
    return(0);
}