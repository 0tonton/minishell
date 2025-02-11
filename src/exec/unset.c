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

int	do_unset(t_data *data, char *arg, char **env)
{
	int		i;
	int		j;
	int		pos;
	char	**tmp;

	if (check_name(arg) == -1)
	{
		printf("unset arg have invalid name\n");
		return (-1);
	}
	pos = if_exist(arg, env);
	if (pos == -1)
		return (0);
	tmp = malloc(sizeof(char *) * (len_tab(env)));
	if (!tmp)
		return (-1);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != pos)
		{
			tmp[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	free_tab(env);
	data->env = tmp;
	return (0);
}

int	ft_unset(t_data *data, char **arg, char **env)
{
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (arg[i])
	{
		if (do_unset(data, arg[i], env) == -1)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

