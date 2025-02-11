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
	int					save;
	int					sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	i++;
	save = i;
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - save > 20 || ((sign == -1 && (result - 1) > LONG_MAX) || \
		(sign == 1 && (result > LONG_MAX))))
		*check = -1;
	return ((int)(result * sign));
}

void	free_and_exit(t_data *data)
{
	del_hdfiles();
	free_data(data);
	write(2, "exit...\n", 8);
	exit(0);
}

void	ft_exit(t_data *data, char **arg)
{
	int	exit_code;
	int	check;

	exit_code = 0;
	check = 0;
	if (!arg[1])
		free_and_exit(data);
	else if (arg[1] && arg[2])
	{
		printf("exit have too many arguments\n");
		data->exit_status = 128;
		return ;
	}
	else if (!arg[2])
	{
		exit_code = simili_atoi(arg[1], &check);
		if (check == -1)
		{
			printf("exit need numeric only argument %d\n", exit_code);
			data->exit_status = 128;
			return ;
		}
		if (exit_code > 254)
			data->exit_status = 255;
		free_and_exit(data);
	}
}

