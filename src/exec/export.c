/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/11 14:58:03 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

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

int	do_export(t_data *data, char *arg, char **env)
{
	int		i;
	int		pos;
	char	**tmp;

	pos = if_exist(arg, env);
	if (pos == -1)
	{
		tmp = malloc(sizeof(char *) * (len_tab(env) + 2));
		if (!tmp)
		{
			error_malloc();
			return (-1);
		}
		i = 0;
		while (env[i])
		{
			tmp[i] = ft_strdup(env[i]);
			if (!tmp[i])
			{
				error_malloc();
				return (-1);
			}
			i++;
		}
		tmp[i] = ft_strdup(arg);
		if (!tmp[i])
		{
			error_malloc();
			return (-1);
		}
		tmp[i+1] = NULL;
		free_tab(env);
		data->env = tmp;
	}
	else
	{
		tmp = malloc(sizeof(char *) * (len_tab(env) + 1));
		if (!tmp)
		{
			error_malloc();
			return (-1);
		}
		i = 0;
		while (i != pos)
		{
			tmp[i] = ft_strdup(env[i]);
			if (!tmp[i])
			{
				error_malloc();
				return (-1);
			}
			i++;
		}
		tmp[i] = ft_strdup(arg);
		if (!tmp[i])
		{
			error_malloc();
			return (-1);
		}
		i++;
		while (env[i])
		{
			tmp[i] = ft_strdup(env[i]);
			if (!tmp[i])
			{
				error_malloc();
				return (-1);
			}
			i++;
		}
		tmp[i] = NULL;
		free_tab(env);
		data->env = tmp;
	}
	return (0);
}

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

void	print_env(char **env)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	sort_array(env, len_tab(env));
	while (env[i])
	{
		printf("declare -x ");
		val = ft_strchr(env[i], '=');
		if (!val)
			printf("%s\n", env[i]);
		else
		{
			j = 0;
			while (env[i][j] != val[0])
			{
				printf("%c", env[i][j]);
				j++;
			}
			printf("\"%s\"\n", val);
		}
		i++;
	}
}

int	ft_export(t_data *data, char **arg, char **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (!arg[1])
	{
		print_env(env);
		return (0);
	}
	while (arg[i])
	{
		if (check_name(arg[i]) == -1)
		{
			printf("export: invalid name\n");
			exit_code = 1;
		}
		else if (do_export(data, arg[i], env) == -1)
			return (1);
		i++;
	}
	return (exit_code);
}
