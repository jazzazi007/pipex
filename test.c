#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char *get_cmd_path(char *cmd, char **env)
{
    char *path = NULL;
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

int main(int ac, char **av, char **env)
{
    if (ac < 2)
    {
        printf("Usage: %s <command>\n", av[0]);
        return (1);
    }

    char **argv = ft_split(av[1], ' ');
    if (!argv)
    {
        perror("ft_split failed");
        return (1);
    }

    char *cmd_path = get_cmd_path(argv[0], env);
    if (!cmd_path)
    {
        perror("Command not found");
        return (1);
    }

    if (execve(cmd_path, argv, env) == -1)
    {
        free(cmd_path);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    free(cmd_path);
    return (0);
}