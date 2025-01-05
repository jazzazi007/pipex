/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:58:02 by moaljazz          #+#    #+#             */
/*   Updated: 2025/01/05 19:58:04 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


char *ft_getenv(char **env)
{
  int i = 0;
  size_t get = 4;

  while(env[i])
  {
    if (ft_strncmp(env[i], "PWD=", get)==0)
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
