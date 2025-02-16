/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:13:21 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	really_do_unset(char ***tmp, char **env, int pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != pos)
		{
			(*tmp)[j] = ft_strdup(env[i]);
			if (!(*tmp)[j])
			{
				error_malloc();
				return (1);
			}
			j++;
		}
		i++;
	}
	(*tmp)[j] = NULL;
	return (0);
}

int	do_unset(t_data *data, char *arg, char **env)
{
	int		pos;
	char	**tmp;

	pos = if_exist(arg, env);
	if (pos == -1)
		return (0);
	tmp = malloc(sizeof(char *) * (len_tab(env)));
	if (!tmp)
	{
		error_malloc();
		return (1);
	}
	if (really_do_unset(&tmp, env, pos) == 1)
		return (1);
	free_tab(env);
	data->env = tmp;
	return (0);
}

int	ft_unset(t_data *data, char **arg)
{
	int		exit_code;
	int		i;
	char	**env;

	i = 0;
	exit_code = 0;
	while (arg[i])
	{
		env = data->env;
		if (do_unset(data, arg[i], env) == 1)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
