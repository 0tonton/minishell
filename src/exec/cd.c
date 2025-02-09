/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:05:55 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	change_oldpwd(t_data *data)
{
	char	**env;
	char	*path_var;
	int		i;

	env = data->env;
	path_var = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 3) == 0)
			path_var = env[i];
		i++;
	}
	if (!path_var)
		do_export(data, "OLDPWD", data->env);
	else
	{
		path_var = ft_strjoin("OLD", path_var);
		if (!path_var)
			return ;
		do_export(data, path_var, data->env);
		free(path_var);
	}
}

void	error_malloc(void)
{
	printf("ERR_MALLOC");
	return ;
}

void	change_pwd(t_data *data, char *path)
{
	char	actual_path[PATH_MAX];
	char	*var_pwd;

	change_oldpwd(data);
	if (!getcwd(actual_path, PATH_MAX))
	{
		perror(path);
		return ;
	}
	var_pwd = ft_strjoin("PWD=", actual_path);
	if (!var_pwd)
		return ;
	do_export(data, var_pwd, data->env);
	free(var_pwd);
}

int	ft_cd(t_data *data, char **arg)
{
	int	check;

	check = 1;
	if (arg[0] && arg[1] && !arg[2])
	{
		check = chdir(arg[1]);
		if (check == -1)
		{
			perror(arg[1]);
			check = 1;
		}
		if (check == 0)
			change_pwd(data, arg[1]);
	}
	return (check);
}
