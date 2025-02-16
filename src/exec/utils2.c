/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klabaune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:38:46 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/16 17:38:49 by klabaune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	ft_swap_str_tab(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_array(char **arr, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], INT_MAX);
			if (diff > 0)
			{
				ft_swap_str_tab(i, j, arr);
				continue ;
			}
			j++;
		}
		i++;
	}
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
