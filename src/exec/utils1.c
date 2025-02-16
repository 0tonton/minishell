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

char	**clean(char **tab)
{
	free_tab(tab);
	error_malloc();
	return (NULL);
}
