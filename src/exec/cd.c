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
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
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
	printf("error malloc");
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

int	do_cd(t_data *data, int nb, char *var)
{
	int	check;
	int	pos;

	pos = if_exist(var, data->env);
	if (pos != -1)
		check = chdir(&data->env[pos][nb]);
	else
	{
		printf("cd: %s is not defined\n", var);
		return (1);
	}
	if (check == -1)
	{
		perror(&data->env[pos][nb]);
		check = 1;
	}
	if (check == 0)
	{
		change_pwd(data, &data->env[pos][nb]);
		if (nb == 7)
			ft_pwd();
	}
	return (check);
}

int	ft_cd(t_data *data, char **arg)
{
	int	check;

	check = 1;
	if (!arg[1] || (ft_strlen(arg[1]) == 1 && arg[1][0] == '~'))
		check = do_cd(data, 5, "HOME");
	else if (arg[1] && !arg[2])
	{
		if (ft_strlen(arg[1]) == 1 && arg[1][0] == '-')
			do_cd(data, 7, "OLDPWD");
		else
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
	}
	return (check);
}
