/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:47:29 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:12:46 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

static int	ft_alllen(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (((char *)s1)[i])
		i++;
	while (((char *)s2)[j])
		j++;
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(sizeof(char) * (ft_alllen(s1, s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (((char *)s1)[j])
	{
		join[i] = ((char *)s1)[j];
		j++;
		i++;
	}
	j = 0;
	while (((char *)s2)[j])
	{
		join[i] = ((char *)s2)[j];
		j++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_strjoin("le ", "test"));
	return (0);
}
*/
