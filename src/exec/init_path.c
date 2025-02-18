/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klabaune <klabaune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/18 17:07:35 by klabaune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	str_copy(char *dest, char *src, int end)
{
	int	i;

	i = 0;
	while (i != end)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	good_path(char **path, char *check)
{
	(*path) = ft_strdup(check);
	if (!(*path))
		error_malloc();
}

void	set_path(char *cmd, char **path, char **env)
{
	int		i;
	char	**all_paths;
	char	check[PATH_MAX];

	i = search_path(env);
	if (i == -1)
	{
		printf("PATH is not defined\n");
		return ;
	}
	all_paths = my_split(&env[i][5], ':');
	if (!all_paths)
		return ;
	i = 0;
	while (all_paths[i])
	{
		fill_path(check, all_paths[i], cmd);
		if (check_access(check, all_paths) == 1)
		{
			good_path(path, check);
			return ;
		}
		i++;
	}
	free_tab(all_paths);
}

void	simple_path(char *cmd, char **path)
{
	*path = ft_strdup(cmd);
	if (!(*path))
	{
		error_malloc();
		return ;
	}
	if (access((*path), F_OK) != 0)
	{
		free(*path);
		*path = NULL;
	}
}

void	init_path(t_data *data, char *cmd, char **path)
{
	if (cmd[my_strchr(cmd, '/')] == '/')
		simple_path(cmd, path);
	else
		set_path(cmd, path, data->env);
	if (!(*path))
	{
		printf("%s : command not found\n", cmd);
		data->exit_status = 127;
		return ;
	}
	if (access((*path), X_OK) != 0)
	{
		perror(*path);
		data->exit_status = 126;
		free((*path));
		(*path) = NULL;
	}
}
