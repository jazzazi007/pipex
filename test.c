#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *ft_getenv(char **env)
{
  int i = 0;
  size_t get = 4;

  while(env[i])
  {
    if (strncmp(env[i], "PWD=", get)==0)
    {
      printf("%s\n", env[i]);
      return (env[i]);
    }else
    {
      i++;
    }
  }
  return (NULL);
}
int main(int ac, char **av, char **env)
{
  char *path = ft_getenv(env);
  return (0);
}