/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:12:32 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/14 18:32:54 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

static size_t	ft_strlenbis(char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

static int	check_word(char *src, char *find)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] == find[i])
		i++;
	if (find[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && ((char *)big)[i] != '\0')
	{
		if (((char *)big)[i] == ((char *)little)[0]
		&& (i + ft_strlenbis((char *)little)) <= len)
		{
			if (check_word(((char *)big + i), (char *)little))
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	char big[] = "bonjourhohoho";
	char little[] = "hi";
	char *result;
	size_t	l = 9;
	
	result = ft_strnstr(big, little, l);
	printf("After. big: %s, little: %s, result: %s\n", big, little, result);
	result = strnstr(big, little, l);
	printf("real. dst: %s, src: %s, result: %s\n", big, little, result);	
}*/