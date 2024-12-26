#include "../include/pipex.h"


void cmd_exec(char *path, char **cmd, char **envp)
{
    if (execve(path, cmd, envp) == -1)
        perror("Error executing function and command EXECVE");
    return;
}