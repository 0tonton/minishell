/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klabaune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:29:06 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/15 19:29:15 by klabaune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	check_name(char *name)
{
	int	i;

	i = 1;
	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (-1);
	while (name[i] && name[i] != '=')
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	if_exist(char *arg, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	while (env[j])
	{
		if (!ft_strncmp(env[j], arg, i))
		{
			if (env[j][i] == '=' || env[j][i] == '\0')
				return (j);
		}
		j++;
	}
	return (-1);
}

int	copy_env(char **tmp, char *cpy)
{
	*tmp = ft_strdup(cpy);
	if (!*tmp)
	{
		error_malloc();
		return (1);
	}
	return (0);
}
