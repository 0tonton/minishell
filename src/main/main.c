/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:25:16 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/12 17:18:33 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"
pid_t	signal_pid;

void	free_tab_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while ((data->env)[i])
		{
			free((data->env)[i]);
			i++;
		}
		free(data->env);
	}
}

void	free_data(t_data *data)
{
	clear_history();
	free_tab_env(data);
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
