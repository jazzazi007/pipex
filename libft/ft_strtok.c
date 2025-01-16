/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:03:41 by moaljazz          #+#    #+#             */
/*   Updated: 2025/01/16 18:03:42 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>


char	*ft_strtok(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
	{
		if (stock != NULL)
			free(stock); // Free previously allocated memory
		stock = ft_strdup(str);
		if (stock == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
			return (NULL); // Return NULL if memory allocation fails
        }
	}

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
    fprintf(stderr, "stock: %s\n", stock);
    fprintf(stderr, "ptr: %s\n", ptr);
	return (ptr);
}
