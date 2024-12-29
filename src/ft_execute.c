#include "../include/pipex.h"

char *get_cmd_path(char *cmd, char **env)
{
   // char *path = NULL;
    char *path_copy;
    char *dir;
    char *full_path;
    int i = 0;

    // Find PATH in environment
    while (env[i] && strncmp(env[i], "PATH=", 5))
        i++;
    if (!env[i])
        return (NULL);
    
    path_copy = strdup(env[i] + 5);
    dir = strtok(path_copy, ":");
    
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        sprintf(full_path, "%s/%s", dir, cmd);
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
void cmd_exec(char *agv, char **envp)
{
    char **cmd = ft_split(agv, ' ');
    char *cmd_path = get_cmd_path(agv, envp);
    if (!cmd_path)
    {
        perror("Command not found");
        return;
    }
    if (execve(cmd_path, cmd, envp) == -1)
        perror("Error EXECVE");
    return;
}