/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:58:02 by moaljazz          #+#    #+#             */
/*   Updated: 2025/01/05 19:58:04 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
char	*ft_strtok(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			ptr = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (ptr);
}

char	*ft_strcpy(char *destination, const char *source)
{
	int	i;
	int	lenght;

	if (destination == NULL || source == NULL)
		return (destination);
	lenght = ft_strlen(source);
	i = 0;
	while (i < lenght)
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

char	*ft_strcat(char *dest, const char *src)
{
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}