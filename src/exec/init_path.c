/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:12:51 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

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

void	set_path(t_data *data, char *cmd, char **path, char **env)
{
	int		i;
	char	**all_paths;
	char	check[PATH_MAX];

	i = search_path(env);
	if (i == -1)
	{
		printf("%s : command not found\n", cmd);
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
			(*path) = ft_strdup(check);
			if (!(*path))
			{
				printf("ERR_MALLOC\n");
				data->exit_status = -1;
			}
			return ;
		}
		i++;
	}
	free_tab(all_paths);
}

void	simple_path(t_data *data, char *cmd, char **path)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		return ;
	if (access((*path), F_OK) != 0 && data)			//data sert a rien
	{
		printf("%s : command not found\n", cmd);
		free(*path);
		*path = NULL;
	}
}

void	init_path(t_data *data, char *cmd, char **path)
{
	if (cmd[my_strchr(cmd, '/')] == '/')
		simple_path(data, cmd, path);
	else
		set_path(data, cmd, path, data->env);
	if (!(*path))
	{
		if (data->exit_status == -1)
			return ;
		else
		{
			data->exit_status = 127;
			return ;
		}
	}
	if (access((*path), X_OK) != 0)
	{
		perror(*path);
		data->exit_status = 126;
		free((*path));
		(*path) = NULL;
	}
}

