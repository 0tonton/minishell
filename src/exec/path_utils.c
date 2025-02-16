/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:51:31 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:13:11 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

char	*my_strnstr(char *big, char *little, int len)
{
	int	i;
	int	j;

	if (little[0] == '\0')
		return (big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] != little[j])
			i++;
		else
		{
			while (big[i] == little[j] && i < len && big[i])
			{
				i++;
				j++;
			}
			i = i - j + 1;
		}
		if (little[j] == '\0')
			return (&big[i - 1]);
	}
	return (NULL);
}

int	my_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	count_words(char *str, char c)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	**my_split(char *envp, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		limit;

	tab = malloc(sizeof(char *) * (count_words(envp, c) + 1));
	if (!tab)
	{
		error_malloc();
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < count_words(envp, c))
	{
		limit = my_strchr(&envp[j], ':');
		tab[i] = malloc(sizeof(char) * (limit + 1));
		if (!tab[i])
			return (clean(tab));
		str_copy(tab[i], &envp[j], limit);
		j = j + limit + 1;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	my_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
}
