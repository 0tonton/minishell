/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:48:17 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:12:56 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	fill_path(char *path, char *start, char *cmd)
{
	str_copy(path, start, ft_strlen(start));
	my_strcat(path, "/");
	my_strcat(path, cmd);
}

int	check_access(char *path, char **all_paths)
{
	if (access(path, F_OK) == 0)
	{
		free_tab(all_paths);
		return (1);
	}
	return (-1);
}

int	search_path(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (my_strnstr(env[i], "PATH=", 5) != 0)
			return (i);
		i++;
	}
	return (-1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
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

void	env_copy(char ***copy, char **env)
{
	int	i;

	*copy = malloc(sizeof(char *) * len_tab(env));
	if (!*copy)
		return ;
	i = 0;
	while (env[i])
	{
		*copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
}
