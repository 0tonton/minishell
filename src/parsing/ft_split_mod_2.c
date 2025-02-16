/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:03:19 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 14:08:24 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	is_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	start_i(char const *s, char *c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (c[j])
	{
		if (((char *)s)[i] == c[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (i);
}

void	end_var(char const *s, char *c, int *end)
{
	int	j;

	j = 0;
	while (c[j])
	{
		if (((char *)s)[*end] == c[j])
		{
			j = 0;
			(*end)--;
		}
		else
			j++;
	}
}
