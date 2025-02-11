/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:25:16 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/11 10:56:23 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"
pid_t	signal_pid;

void	free_shlvl(char **env)
{
	if (env)
	{
		if (ft_getenv("SHLVL", env))
			free(ft_getenv("SHLVL", env) - 6);
	}
}

void	free_data(t_data *data)
{
	if (data->env)
	{
		free_shlvl(data->env);
		free(data->env);
	}
	free(data);
}

int	main(int argc, char *argv[], char *env[])
{
	t_data	*data;


	(void)(argc);
	(void)(argv);
	data = malloc(sizeof(t_data));
	data->exit_status = 0;
	data->env = tab_var_env(env);
	set_up_signals();
	prompting(data);
}
