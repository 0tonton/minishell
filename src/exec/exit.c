/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/11 11:42:12 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	simili_atoi(char *str, int *check)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i])
		*check = -1;
	return ((int)((result * sign) % 256));
}

void	free_and_exit(t_data *data)
{
	int	exit_s;

	exit_s = data->exit_status;
	del_hdfiles();
	free_data(data);
	write(2, "exit...\n", 8);
	exit(exit_s);
}

void	ft_exit(t_data *data, char **arg)
{
	int	check;

	check = 0;
	if (!arg[1])
		free_and_exit(data);
	else if (arg[1] && arg[2])
	{
		printf("exit: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	else if (!arg[2])
	{
		data->exit_status = simili_atoi(arg[1], &check);
		if (check == -1)
		{
			printf("exit: numeric argument required\n");
			data->exit_status = 2;
		}
		free_and_exit(data);
	}
}

