/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:21:19 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:12:43 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (((unsigned char *)s)[i])
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (&((char *)s)[i]);
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strchr("le test", 't'));
	printf("%s\n", ft_strchr("le test", 'l'));
	printf("%s\n", ft_strchr("le test", 'u'));
	printf("%s\n", ft_strchr("le test", 0));
	return (0);
}
*/
